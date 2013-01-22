/*
 * CamHandler.cpp
 *
 *  Created on: 04.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#include "../header.h"
using namespace std;
using namespace cv;

InputHandler::InputHandler() {

    currentImage = Mat();
    last = Mat();
    helper = CvHelper::getInstance();
}

InputHandler::InputHandler(const char* camURL) :
AInputHandler(camURL) {
    helper = CvHelper::getInstance();
    currentImage = Mat();
    last = Mat();

}

InputHandler::~InputHandler() {
}

IplImage InputHandler::currentIplImage() {
    IplImage img = currentImage;
    return img;
}

Mat InputHandler::currentMatImage() {
    return currentImage;
}

bool InputHandler::open() {
    switch (sourceType) {
        case INPUT_IP_CAM:
            try {
                connected = openDefIpCam();
                DBG("IPCam found");

                return connected;

            } catch (Exception& ex) {
                DBG("No Cam found");
            }
            return false;

        case INPUT_CAM:
            try {
                connected = openDefWebCam();
                DBG("WebCam gefunden!");
                return connected;
            } catch (Exception& ex) {
                DBG("Keine WebCam gefunden!");
            }
            return false;

        case INPUT_NONE:
            DBG("Keine Eingabe");
            break;
        case INPUT_VIDEO:
            try {
                connected = openVideo();
#ifdef DEBUG
                if (connected) {
                    DBG("Video gefunden!");
                }
#endif
            } catch (Exception& ex) {
                DBG("%s", ex.what());
            }
            break;
        case INPUT_FOLDER:
            try {
                connected = openFolder();
#ifdef DEBUG
                if (connected) {
                    DBG("Bilder gefunden!");
                }
#endif
            } catch (Exception& ex) {
                DBG("%s", ex.what());
            }
            break;
        default:
            break;
            //NONE, VIDEO_FILE, CAM, IP_CAM, IMAGE_FOLDER
    }
    return connected;

}

bool InputHandler::releaseCapture() {
    if (!connected) {
        return false;
    }
    if (cap.isOpened()) {
        cap.release();
        return true;
    }




    return true;
}

bool InputHandler::close() {
    if (connected) {
        if (cap.isOpened()) {
            cap.release();

            return true;
        } else {
            return false;
        }
    } else {
        cout << "No connection available" << endl;

        return false;
    }
}

bool InputHandler::releaseCurrentImage() {
    if (!last.empty()) {
        last.release();
    }
    return true;
}

bool InputHandler::openDefIpCam() {
    if (!cap.isOpened()) {
        cap = VideoCapture();
    }
    if (cap.isOpened()) {
        releaseCapture();
        cap = VideoCapture();
    }
    bool result = cap.open((defaultIpCamURL));
    if (!result) {
        return false;
    } else {
        connected = true;

        return true;
    }

}

bool InputHandler::openDefWebCam() {
    if (!cap.isOpened()) {
        cap = VideoCapture();
    }
    if (cap.isOpened()) {
        releaseCapture();
        cap = VideoCapture();
    }

    bool result = cap.open(0);


    if (!result) {
        return false;
    } else {
        connected = true;

        return true;
    }

}

void InputHandler::dispose() {

    releaseCapture();
    releaseCurrentImage();
}

bool InputHandler::grabNext() {

    switch (sourceType) {
        case INPUT_FOLDER:
            if (imageFiles.empty()) {
                if (!imageFolders.empty()) {
                    releaseCurrentImage();
                    openFolder();
                } else {
                    DBG("Keine Bilder");
                    connected = false;
                    return false;
                }
            } else {
                releaseCurrentImage();
                nextFromFolder();
            }
            break;
        case INPUT_VIDEO:

            if (!currentImage.empty()) {
                last = Mat(currentImage.size(), CV_8UC3);
                currentImage.copyTo(last);


            }
            releaseCurrentImage();
            if (!cap.grab()) {
                DBG("Kein Bild bekommen.");
                connected = false;
                reachesEnd = true;
                return false;
            }

            currentImage = Mat::zeros(Size(1280, 720), CV_8UC3);
            if (!cap.read(currentImage)) {

                if (videoFiles.empty()) {
                    DBG("Kein Bild bekommen.");
                    connected = false;
                    reachesEnd = true;
                    return false;
                } else {
                    cap.release();
                    if (!openVideo()) {
                        DBG("Kein Bild bekommen.");
                        connected = false;
                        reachesEnd = true;
                        return false;
                    } else {
                        break;
                    }
                }
            }

            break;
        default:
            releaseCurrentImage();
            if (!cap.grab()) {
                DBG("Kein Bild bekommen.");
                connected = false;
                reachesEnd = true;
                return false;
            }

            currentImage = Mat::zeros(Size(1280, 720), CV_8UC3);

            if (!cap.read(currentImage)) {
                DBG("Kein Bild bekommen.");
                connected = false;
                reachesEnd = true;
                return false;
            }
    };

    if (!last.empty()){
        DBG("Strukturelle Gleichheit der letzten Bilder: %f", helper->checkEquality(last, currentImage));
    }else{
        DBG("Letztes bild ist leer...");
    }

    return true;

}

void InputHandler::next() {

    if (!grabNext()) {
        DBG("Konnte naechstes Bild nicht von der Eingabequelle lesen.");
    }
}

Mat InputHandler::getImage() {

    return currentImage;
}

void InputHandler::releaseAll() {

    releaseCapture();
    releaseCurrentImage();
}

bool InputHandler::opened() {

    return isOpen();
}

int InputHandler::inputWidth() {
    if (!connected) {
        DBG("Capture is not open -> Width is 0");

        return 0;
    }
    int i = static_cast<int> (cap.get(CV_CAP_PROP_FRAME_WIDTH));
    if (currentImage.data != NULL) {
        i = currentImage.cols;
    }
    return i;

}

int InputHandler::inputHeight() {
    if (!connected) {
        DBG("Capture is not open -> Width is 0");

        return 0;
    }
    int i = static_cast<int> (cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    if (currentImage.data != NULL) {
        i = currentImage.rows;
    }
    return i;
}

int InputHandler::inputFps() {
    if (!connected) {
        DBG("Capture is not open");

        return 0;
    }
    return static_cast<int> (cap.get(CV_CAP_PROP_FPS));
}

bool InputHandler::shouldConvertToRGB() {
    if (!connected) {
        DBG("Capture is not open");

        return 0;
    }
    return static_cast<bool> (cap.get(CV_CAP_PROP_CONVERT_RGB));
}

/**
 * Versucht eine Andere Bildgr&ouml;&szlig;e von der Kamera anzufordern.
 * @param newResolution Die Aufl&ouml;sung, die von der Kamera angefordert wird.
 * @return <code>true</code>, wenn die &Auml;nderung angenommen wurden, sonst <code>false</code>.
 */
bool InputHandler::requestFormat(INPUT_FORMAT fmt) {
    if (sourceType != INPUT_TYPE::INPUT_CAM) {
        DBG("Eine neue Bildgroesse kann nur bei Webcams angefordert werden");
        return false;
    }
    Point2i res = formatToDimension(fmt);
    if (res.x == 0 || res.y == 0) {
        DBG("Ungueltige Aufloesung");

        return false;
    }
    if (!cap.isOpened()) {
        DBG("Keine Verbindung");
        return false;
    }
    try {
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, static_cast<double> (res.y));
        cap.set(CV_CAP_PROP_FRAME_WIDTH, static_cast<double> (res.x));

        int chkx, chky;
        chkx = static_cast<int> (cap.get(CV_CAP_PROP_FRAME_WIDTH));
        chky = static_cast<int> (cap.get(CV_CAP_PROP_FRAME_HEIGHT));

        if (chkx != res.x || chky != res.y) {
            return false;
        } else {
            return true;
        }

    } catch (Exception& ex) {

        DBG("%s", ex.what());

    }
    return false;
}

/**
 * Gibt die aktuelle <code>RESOLUTION</code> des Kamerabildes zur&uuml;ck.
 * @return die aktuelle <code>RESOLUTION</code>.
 */
INPUT_FORMAT InputHandler::currentCamInputFormat() {
    int w, h;
    w = inputWidth();
    h = inputHeight();
    if (h <= 0 || w <= 0) {
        return rNULL;
    }
    if (h == 480 && w == 640) {
        return r480p;
    }
    if (w == 1280 && h == 720) {
        return r720p;
    }
    if (w == 1920 && h == 1080) {

        return r1080p;
    }

    return rUnknown;
}

Point2i InputHandler::formatToDimension(INPUT_FORMAT fmt) {
    switch (fmt) {
        case rNULL:
            return Point2i(0, 0);
        case rUnknown:
            return Point2i(currentImage.cols, currentImage.rows);
        case r480p:
            return Point2i(640, 480);
        case r720p:
            return Point2i(1280, 720);
        case r1080p:
            return Point2i(1920, 1080);
        default:
            return Point2i(0, 0);
    }
}

bool InputHandler::openVideo() {
    if (videoFiles.empty()) {
        DBG("Keine Videos verfuegbar");
        return false;
    } else {
        DBG("%d Videos in Warteschlange", (int) videoFiles.size());
    }
    cap = VideoCapture(videoFiles[0]);
    videoFiles.erase(videoFiles.begin());
    DBG("Setze Quelle auf INPUT_VIDEO");
    sourceType = INPUT_VIDEO;
    return cap.isOpened();
}

bool InputHandler::openFolder() {
    if (!imageFiles.empty()) {
        DBG("Verwende bestehende Dateiliste");
        connected = true;
        StringArray::iterator iter = imageFiles.begin();
        String filename = (*iter);

        currentImage = imread(filename);
        imageFiles.erase(iter);
        DBG("Setze Quelle auf IMAGE_FOLDER");
        sourceType = INPUT_FOLDER;
        return true;
    } else {
        DBG("Erstelle neue Dateiliste");
        StringSet searchStrings = StringSet();
        searchStrings.insert("jpg");
        searchStrings.insert("jpeg");
        searchStrings.insert("png");
        searchStrings.insert("bmp");
        FileManager* man = FileManager::getInstance();
        man->setSearchPath(((String) (*imageFolders.begin())));
        man->setSearchStrings(searchStrings);
        imageFiles = man->getFoundList();
        DBG("Setze Quelle auf IMAGE_FOLDER");
        sourceType = INPUT_FOLDER;
        if (!imageFiles.empty()) {
            currentImage = imread(imageFiles[0]);
            imageFiles.erase(imageFiles.begin());
        } else return true;
        return !currentImage.empty();
    }


}

void InputHandler::nextFromFolder() {
    if (imageFiles.empty()) {
        DBG("Keine Bilder");
        reachesEnd = true;
        return;
    }
    String img = imageFiles[0];
    releaseCurrentImage();
    last = Mat(currentImage.size(), CV_8UC3);
    currentImage.copyTo(last);
    currentImage = Mat();
    currentImage = imread(img);

    if (imageFiles.size() > 1) {
        StringArray::iterator iter = imageFiles.begin();
        imageFiles.erase(iter);
    } else {
        reachesEnd = true;
    }

}

bool InputHandler::reachesEndOfInput() {
    return reachesEnd;
}


