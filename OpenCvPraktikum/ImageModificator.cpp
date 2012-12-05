/*
 * ImageModificator.cpp
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#include "header.h"

ImageModificator::ImageModificator() {


}

ImageModificator::ImageModificator(const ImageModificator&) {


}

ImageModificator::~ImageModificator() {

}

void ImageModificator::modify(cv::Mat&) {
    //NIX
    DBG("No Modification done");
}

bool ImageModificator::doesAction() {
    return false;
}




