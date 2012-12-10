/* 
 * File:   Window.cpp
 * Author: julian
 * 
 * Created on 10. Dezember 2012, 15:50
 */

#include "Window.h"

Window::Window(String name,int width, int height) {
    
    this->currentImage = NULL;
    if (width < 0) {
        DBG("width is lower than 1, cant create window!");
        exit(EXIT_FAILURE);
    } 
    if (height < 0 ) {
        DBG("height is lower than 1, cant create window!");
        exit(EXIT_FAILURE);
    }
    this->width = width;
    this->height = height;
    this->name = name;
    namedWindow(this->name, WINDOW_NORMAL);
}

Window::Window(const Window& orig) {
    this->currentImage = orig.currentImage;
    this->height = orig.height;
    this->width = orig.width;
    this->name = orig.name;
}

Window::~Window() {
}

void Window::setCurrentImage(Mat *current) {
    if (current == NULL) {
        DBG("current Image of Window is null!");
        return;
    }
    this->currentImage = current;

}
void Window::showWindow() {
    if (this->name.empty()) {
        DBG("Name des Fensters ist leer!");
        return;
    }
    if (this->currentImage == NULL) {
        DBG("currentImage of Window is NULL, cant show window!");
        return;
    }
    
    imshow(this->name,*this->currentImage);

}

