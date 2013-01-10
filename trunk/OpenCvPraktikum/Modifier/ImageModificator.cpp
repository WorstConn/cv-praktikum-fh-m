/*
 * ImageModificator.cpp
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#include "../header.h"

ImageModificator::ImageModificator() {
    helper = CvHelper::getInstance();

}

ImageModificator::ImageModificator(const ImageModificator& orig) {
    helper = orig.helper;

}

ImageModificator::~ImageModificator() {
    delete helper;
}






