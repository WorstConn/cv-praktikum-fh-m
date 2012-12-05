/*
 * CamHandler.cpp
 *
 *  Created on: 04.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#include "header.h"
using namespace std;
using namespace cv;

CamHandler::CamHandler() {

    currentImage = Mat();

}

CamHandler::CamHandler(const char* camURL) :
ACamHandler(camURL) {

    currentImage = Mat();

}

CamHandler::~CamHandler() {

}

IplImage CamHandler::currentIplImage() {
    IplImage img = currentImage;
    return img;
}

Mat CamHandler::currentMatImage() {
    return currentImage;
}

bool CamHandler::open() {
    if (!ipCam) {
        try {
            if (openDefWebCam()) {
                cout << "WebCam gefunden!" << endl;

                return true;
            }

        } catch (Exception& ex) {
            cerr << "Keine WebCam gefunden!" << endl;
        }
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

bool CamHandler::releaseCapture() {
    if (!connected) {
        return false;
    }
    if (!cap.isOpened()) {
        return false;
    }
    cap.release();

    return true;
}

bool CamHandler::close() {
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

bool CamHandler::releaseCurrentImage() {
    if (currentImage.data == NULL) {
        return true;
    }
    currentImage.release();

    return true;
}

bool CamHandler::openDefIpCam() {
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

bool CamHandler::openDefWebCam() {
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

void CamHandler::dispose() {
    releaseCapture();
    releaseCurrentImage();
}

bool CamHandler::grabNext() {

    if (!cap.isOpened()) {
        cout << "VideoCaptue ist NULL!" << endl;
        return false;
    }
    releaseCurrentImage();
    cap >> currentImage;


    return true;

}

void CamHandler::next() {

    if (!grabNext())throw Exception();
}

Mat CamHandler::getImage() {
    return currentImage;
}

void CamHandler::releaseAll() {
    releaseCapture();
    releaseCurrentImage();
}

bool CamHandler::opened() {



    return isOpen();
}

int CamHandler::inputWidth() {
    if (!cap.isOpened()) {
        DBG("Capture is not open -> Width is 0");
        return 0;
    }
    return static_cast<int> (cap.get(CV_CAP_PROP_FRAME_WIDTH));
}

int CamHandler::inputHeight() {
    if (!cap.isOpened()) {
        DBG("Capture is not open -> Height is 0");
        return 0;
    }
    return static_cast<int> (cap.get(CV_CAP_PROP_FRAME_HEIGHT));
}

int CamHandler::inputFps() {
    if (!cap.isOpened()) {
        DBG("Capture is not open");
        return 0;
    }
    return static_cast<int> (cap.get(CV_CAP_PROP_FPS));
}

bool CamHandler::shouldConvertToRGB() {
    if (!cap.isOpened()) {
        DBG("Capture is not open");
        return 0;
    }
    return static_cast<bool> (cap.get(CV_CAP_PROP_CONVERT_RGB));
}



