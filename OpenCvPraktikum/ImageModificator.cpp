/*
 * ImageModificator.cpp
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking
 */

#include "header.h"

ImageModificator::ImageModificator() {


}

ImageModificator::ImageModificator(const ImageModificator&) {


}

ImageModificator::~ImageModificator() {

}

void ImageModificator::modify(cv::Mat*) {
    //NIX
}

/**
 * Gibt an, dass dieser Modifikator nix tut...
 * @return immer <code>false</code>
 */
bool ImageModificator::doesAction() {
    return false;
}

