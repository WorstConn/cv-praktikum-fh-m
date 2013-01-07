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

    while (show) {

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

void Window::addTrackbar(String name, int max, TrackbarCallback ptr) {

}

String Window::getName() {
    return name;
}