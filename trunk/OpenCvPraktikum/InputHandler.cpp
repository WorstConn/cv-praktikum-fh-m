/*
 * CamHandler.cpp
 *
 *  Created on: 04.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#include "header.h"
using namespace std;
using namespace cv;

InputHandler::InputHandler() {

    currentImage = Mat();

}

InputHandler::InputHandler(const char* camURL) :
AInputHandler(camURL) {

    currentImage = Mat();

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
        case IP_CAM:
            try {
                if (openDefIpCam()) {
                    cout << "IPCam found" << endl;
                    return true;
                }
            } catch (Exception& ex) {
                cerr << "No Cam found" << endl;
            }
            return false;

        case CAM:
            try {
                if (openDefWebCam()) {
                    cout << "WebCam gefunden!" << endl;

                    return true;
                }

            } catch (Exception& ex) {
                cerr << "Keine WebCam gefunden!" << endl;
            }
            return false;

        case NONE:
            DBG("Keine Eingabe");
            break;
        case VIDEO_FILE:
            try {
                openVideo();
            } catch (Exception& ex) {
                DBG("%s", ex.what());
            }
            break;
        case IMAGE_FOLDER:
            try {
                openFolder();
            } catch (Exception& ex) {
                DBG("%s", ex.what());
            }
            break;
        default:
            break;
            //NONE, VIDEO_FILE, CAM, IP_CAM, IMAGE_FOLDER
    }

    if (!(sourceType == IP_CAM)) {

        return false;
    } else {
        try {
            if (openDefIpCam()) {
                cout << "IPCam found" << endl;
                return true;
            }
        } catch (Exception& ex) {

            cerr << "No Cam found" << endl;
        }

        return false;
    }
}

bool InputHandler::releaseCapture() {
    if (!connected) {
        return false;
    }
    if (!cap.isOpened()) {
        return false;
    }
    cap.release();

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
    if (currentImage.data == NULL) {
        return true;
    }
    currentImage.release();

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
    bool result = cap.open(String(defaultIpCamURL));
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
        case IMAGE_FOLDER:
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
        default:
            releaseCurrentImage();
            cap >> currentImage;
            if (currentImage.empty()) {
                connected = false;
                
                return false;
            }
            break;
    }
    if (!cap.isOpened()) {
        cout << "VideoCaptue ist NULL!" << endl;
        connected = false;
        return false;
    }

    return true;

}

void InputHandler::next() {

    if (!grabNext())throw Exception();
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
    if (!cap.isOpened()) {
        DBG("Capture is not open -> Width is 0");

        return 0;
    }
    return static_cast<int> (cap.get(CV_CAP_PROP_FRAME_WIDTH));
}

int InputHandler::inputHeight() {
    if (!cap.isOpened()) {
        DBG("Capture is not open -> Height is 0");

        return 0;
    }
    return static_cast<int> (cap.get(CV_CAP_PROP_FRAME_HEIGHT));
}

int InputHandler::inputFps() {
    if (!cap.isOpened()) {
        DBG("Capture is not open");

        return 0;
    }
    return static_cast<int> (cap.get(CV_CAP_PROP_FPS));
}

bool InputHandler::shouldConvertToRGB() {
    if (!cap.isOpened()) {
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
    }
    cap = VideoCapture(videoFiles[0]);
    videoFiles.erase(videoFiles.begin());
    DBG("Setze Quelle auf IMAGE_FOLDER");
    sourceType = VIDEO_FILE;
    return cap.isOpened();
}

bool InputHandler::openFolder() {
    if (!imageFiles.empty()) {
        DBG("Verwende bestehende Dateiliste");
        connected = true;
        vector<String>::iterator iter = imageFiles.begin();
        String filename = (*iter);

        currentImage = imread(filename);
        imageFiles.erase(iter);
        DBG("Setze Quelle auf IMAGE_FOLDER");
        sourceType = IMAGE_FOLDER;
        return true;
    } else {
        DBG("Erstelle neue Dateiliste");
        set<String> searchStrings = set<String > ();
        searchStrings.insert("jpg");
        searchStrings.insert("jpeg");
        searchStrings.insert("png");
        searchStrings.insert("bmp");
        FileManager* man = FileManager::getInstance();
        man->setSearchPath(((String) (*imageFolders.begin())));
        man->setSearchStrings(searchStrings);
        imageFiles = man->getFoundList();
        DBG("Setze Quelle auf IMAGE_FOLDER");
        sourceType = IMAGE_FOLDER;
        return !imageFiles.empty();
    }


}

void InputHandler::nextFromFolder() {
    if (imageFiles.empty()) {
        DBG("Keine Bilder");
        return;
    }
    String img = imageFiles[0];
    currentImage = imread(img);
    if (imageFiles.size() > 1) {
        vector<String>::iterator iter = imageFiles.begin();
        imageFiles.erase(iter);
    }

}
