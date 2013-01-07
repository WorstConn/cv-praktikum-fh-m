/* 
 * File:   AImageAction.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 6. Januar 2013, 11:36
 */

#include "../header.h"

AImageAction::AImageAction(String windowName, String name, int max, int min) : AAction(windowName, name, max, min) {
    img = NULL;

}

AImageAction::AImageAction(const AImageAction& orig) : AAction(orig) {
    img = orig.img;
}

AImageAction::~AImageAction() {
}

void AImageAction::updateImage(Mat* img) {
    this->img = img;
}

void AImageAction::clearImage() {
    img = NULL;

}