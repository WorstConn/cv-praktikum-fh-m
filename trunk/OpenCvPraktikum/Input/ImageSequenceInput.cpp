/* 
 * File:   ImageSequenceInput.cpp
 * Author: Nils Frenking, Julian Cordes
 * 
 * Created on 29. November 2012, 19:04
 */

#include "../header.h"

ImageSequenceInput::ImageSequenceInput() {
    reachesEnd = false;
}

ImageSequenceInput::ImageSequenceInput(const ImageSequenceInput& orig) {
    reachesEnd = orig.reachesEnd;
}

ImageSequenceInput::~ImageSequenceInput() {
}

