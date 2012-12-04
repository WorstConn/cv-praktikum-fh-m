/*
 * NewCamHandler.cpp
 *
 *  Created on: 04.11.2012
 *      Author: Nils Frenking
 */

#include "header.h"
using namespace std;
using namespace cv;

NewCamHandler::NewCamHandler() {

    currentImage = Mat();

}

NewCamHandler::NewCamHandler(const char* camURL) :
CamHandler(camURL) {

    currentImage = Mat();

}

NewCamHandler::~NewCamHandler() {

}

IplImage NewCamHandler::currentIplImage() {
    IplImage img = currentImage;
    return img;
}

Mat NewCamHandler::currentMatImage() {
    return currentImage;
}

bool NewCamHandler::open() {
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

bool NewCamHandler::releaseCapture() {
    if (!connected) {
        return false;
    }
    if (!cap.isOpened()) {
        return false;
    }
    cap.release();

    return true;
}

bool NewCamHandler::close() {
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

bool NewCamHandler::releaseCurrentImage() {
    if (currentImage.data == NULL) {
        return true;
    }
    currentImage.release();

    return true;
}

bool NewCamHandler::openDefIpCam() {
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

bool NewCamHandler::openDefWebCam() {
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

void NewCamHandler::dispose() {
    releaseCapture();
    releaseCurrentImage();
}

bool NewCamHandler::grabNext() {

    if (!cap.isOpened()) {
        cout << "VideoCaptue ist NULL!" << endl;
        return false;
    }
    releaseCurrentImage();
    cap >> currentImage;


    return true;

}

void NewCamHandler::next() {

    if (!grabNext())throw Exception();
}

Mat NewCamHandler::getImage() {
    return currentImage;
}

void NewCamHandler::releaseAll() {
    releaseCapture();
    releaseCurrentImage();
}

bool NewCamHandler::opened() {
    return isOpen();
}
