/* 
 * File:   BgFgSegmModificator.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 3. Januar 2013, 14:50
 */

#include "../header.h"

BgFgSegmModificator::BgFgSegmModificator(vector<String> bgImages) {
}

BgFgSegmModificator::BgFgSegmModificator(const BgFgSegmModificator& orig) : ImageModificator(orig){
}

BgFgSegmModificator::~BgFgSegmModificator() {
}


float BgFgSegmModificator::getScale() {
    return 1.0f;
}

void BgFgSegmModificator::modify(Mat& mat) {
    Mat erg = Mat::zeros(mat.size(), CV_8UC3);
    cvtColor(mat, erg, CV_BGR2HSV);
    mat = erg;
    
    

}
