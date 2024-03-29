/* 
 * File:   RecorderCtl.cpp
 * Author: Nils Frenking, Julian Cordes
 * 
 * Created on 14. Dezember 2012, 17:01
 */


#include "../header.h"
using namespace std;
using namespace cv;

RecorderCtl::RecorderCtl(String ctl) {
    name = (ctl.empty()) ? "Default" : ctl;
    capture = NULL;
    wnd = WindowManager::getInstance();
    wnd->createWindow(name, 0, 0);
    state = INIT;
    ctlThread = NULL;
    lastImgUpdate = -1;
}

RecorderCtl::RecorderCtl(const RecorderCtl& orig) {
    name = orig.name;
    capture = orig.capture;
    wnd = orig.wnd;
    state = orig.state;
    ctlThread = NULL;
    lastImgUpdate = orig.lastImgUpdate;
}

RecorderCtl::~RecorderCtl() {
    if (capture != NULL) {
        DBG("Lösche Rekorder");
        capture->release();
        capture = NULL;
    }
}

bool RecorderCtl::refreshWindowImage(Mat img) {
    if (wnd != NULL) {
        wnd->updateWindowImage(name, &img);
        return true;
    }
    return false;
}

void RecorderCtl::dispose() {
    state = DELETED;
    if (ctlThread != NULL && ctlThread->joinable()) {
        ctlThread->join();

    }
    if (wnd != NULL) {
        wnd->closeWindow(name);
        wnd = NULL;
    }
    if (capture != NULL) {
        capture->release();
        capture = NULL;
    }

}

void RecorderCtl::setCapture(CvVideoCapture *capture) {
    this->capture = capture;
}

CvWindow* RecorderCtl::getWindow() {
    return wnd->getWindow(name);
}

CvVideoCapture* RecorderCtl::getCapture() {
    return capture;
}

void RecorderCtl::startGrabInput() {
    if (capture == NULL or !capture->available()) {
        DBG("No input available");
        return;
    }
    if (wnd == NULL) {
        DBG("No window available");
        return;
    }

    if (state != GRAB) {
        state = GRAB;
    }
    if (ctlThread != NULL) {
        DBG("Waiting for work-thread to finish");
        if (ctlThread->joinable()) {
            ctlThread->join();
        }

    }
    ctlThread = new thread(&RecorderCtl::grabLoop, this);
}

void RecorderCtl::startRecording() {
    if (wnd == NULL) {
        DBG("No window available");
        return;
    }
    if (capture == NULL || !capture->available()) {
        DBG("No input available");
    }
    if (state != RECORD) {
        state = RECORD;
    }
    if (ctlThread != NULL) {

        if (ctlThread->joinable()) {
            DBG("Waiting for work-thread to finish");
            ctlThread->join();
        }

    }
    DBG("Starte Aufnahmethread");
    ctlThread = new thread(&RecorderCtl::recordLoop, this);


}

void RecorderCtl::createCapture(ImageSequenceInput& in) {
    capture = new CvVideoCapture(in);
}

void RecorderCtl::grabLoop() {
    time_t curr;
    time(&curr);
    if (lastImgUpdate == -1 || (((long int) curr)-((long int) lastImgUpdate)) > 30) {
        DBG("Initialisiere Zeit.");
    }
    Mat tmp;
    wnd->showWindow(name);
    try {
        DBG("GrabLoop");
        while (state == GRAB) {
            capture->requestNext();
            tmp = capture->getFrame();
            wnd->updateWindowImage(name, &tmp);
        }
    } catch (Exception& ex) {
        DBG("%s", ex.what());
    }
    tmp.release();

}

void RecorderCtl::recordLoop() {

    time_t curr;
    time(&curr);
    if (lastImgUpdate == -1 || (((long int) curr)-((long int) lastImgUpdate)) > 30) {
        DBG("Initialisiere Zeit.");
        time(&lastImgUpdate);
    }
    Mat tmp;
    wnd->showWindow(name);
    if (!capture->isRecording()) {
        DBG("Starte Aufnahme");
        capture->start();
    }
    try {
        DBG("Betrete Record-Loop");
        while (state == RECORD) {
            tmp = capture->getFrame();
            if (cvWaitKey(50) == ESC) {
                DBG("Beende aufnahme->ESC gedrueckt");
                dispose();
                break;
            }
            wnd->updateWindowImage(name, &tmp);
        }
    } catch (Exception& ex) {
        DBG("%s", ex.what());

    }
    tmp.release();

}

void RecorderCtl::stopRecording() {
    startGrabInput();
}

void RecorderCtl::stopGrabbing() {
    dispose();
}


