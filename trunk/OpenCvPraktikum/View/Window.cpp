/* 
 * File:   Window.cpp
 * Author: julian
 * 
 * Created on 10. Dezember 2012, 15:50
 */

#include "../header.h"

Window::Window(String name, int width, int height) {

    this->currentImage = NULL;
    if (width < 0) {
        DBG("width is lower than 1, cant create window!");
        exit(EXIT_FAILURE);
    }
    if (height < 0) {
        DBG("height is lower than 1, cant create window!");
        exit(EXIT_FAILURE);
    }
    this->width = width;
    this->height = height;
    this->name = name;
    show = false;
    refreshDelay = 40;
    refreshThread = NULL;
    lastupdate = -1;

}

Window::Window(const Window& orig) {
    this->currentImage = orig.currentImage;
    this->height = orig.height;
    this->width = orig.width;
    this->name = orig.name;
    show = orig.show;
    refreshDelay = orig.refreshDelay;
    refreshThread = NULL;
    lastupdate = orig.lastupdate;

}

Window::~Window() {
    destroyAllWindows();
}

void Window::setCurrentImage(Mat *current) {
    if (current == NULL) {
        DBG("current Image of Window is null!");
        return;
    }
    Mat* cpy = new Mat(current->size(), current->type());
    current->copyTo(*cpy);
    imageMutex.lock();
    if (this->currentImage != NULL && this->currentImage->data != NULL) {
        this->currentImage->release();
    }
    this->currentImage = cpy;
    imageMutex.unlock();

}

void Window::showWindow() {


    if (this->name.empty()) {
        DBG("Name des Fensters ist leer!");
        return;
    }
    namedWindow(this->name, CV_GUI_EXPANDED);
    show = true;

    refreshThread = new thread(&Window::loop, this);
}

void Window::closeWindow() {
    if (show) {
        show = false;
        DBG("Warte auf Refreshthread");
        if (refreshThread->joinable()) {
            refreshThread->join();
        }
        destroyWindow(this->name);
    }
}

void Window::loop() {
    DBG("Betrete loop")
    time_t current;
    map < pair<String, bool>, TrackbarData> ::iterator iter;
    while (show) {
        trackbarsMutex.lock();


        for (iter = trackbars.begin(); iter != trackbars.end(); iter++) {
            TrackbarData dat = (*iter).second;
            if (!(*iter).first.second) {
                createTrackbar((*iter).first.first/* Name der Trackbar */, name /* Fenstername */, 0 /* int ptr Position*/, dat.getMaxVal() /* Maximalwert*/, dat.getCallback() /* Callback */, (void*) (*iter).first.first.c_str()/*Benutzerdaten. Name der Trackbar*/);
                trackbars.erase(iter);
                pair<String, bool> id = pair<String, bool> (dat.getName(), true);
                pair < pair<String, bool>, TrackbarData> info = pair < pair<String, bool>, TrackbarData > (id, dat);
                if (!trackbars.insert(info).second) {
                    DBG("Trackbar konnte nicht wieder hinzugefuegt werden.");
                }
            }
        }

        trackbarsMutex.unlock();
        imageMutex.lock();

        if (currentImage != NULL) {
            imshow(this->name, *this->currentImage);

        }

        imageMutex.unlock();

        int c = waitKey(refreshDelay);
        if (c != -1) {
            show = false;
            break;
        }
        time(&current);
        if (lastupdate == -1 || ((long int) current - lastupdate)>(long int) refreshDelay) {
            if (lastupdate == -1) {
                time(&lastupdate);
            } else {
                this_thread::sleep_for(chrono::milliseconds((long int) (current - lastupdate)));
            }

        }
    }

    DBG("Verlasse loop");
}

bool Window::isShowing() {
    return show;
}
//FIME: TrackBar-Prop-Objekt erstellen!!

void Window::addTrackbar(String name, int max, void (*ptr)(int pos, void* usr_dat)) {
    map < pair<String, bool>, TrackbarData> ::iterator iter;
    trackbarsMutex.lock();
    for (iter = trackbars.begin(); iter != trackbars.end(); iter++) {
        if ((*iter).first.first.compare(name) == 0) {
            DBG("Trackbar mit diesem Namen bereits vorhanden.");
            return;
        }

    }
    pair<String, bool> id = pair<String, bool> (name, false);
    pair < pair<String, bool>, TrackbarData> info = pair < pair<String, bool>, TrackbarData > (id, TrackbarData(name, max, ptr));
    if (!trackbars.insert(info).second) {
        DBG("Trackbar konnte nicht hinzugefuegt werden.");
    }
    try {
        trackbarsMutex.unlock();
    } catch (Exception& ex) {
        DBG("Konnte Lock nicht loesen.\nFehler: %s", ex.what());
    }
}

