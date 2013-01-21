/* 
 * File:   ScaleModificator.cpp
 * Author: Nils Frenking, Julian Cordes
 * 
 * Created on 5. Dezember 2012, 01:04
 */

#include "../header.h"
using namespace std;
using namespace cv;

ScaleModificator::ScaleModificator() {
}

ScaleModificator::ScaleModificator(const ScaleModificator& orig) : ImageModificator(orig) {
}

ScaleModificator::~ScaleModificator() {
}

void ScaleModificator::modify(Mat& mat) {
    CvHelper *helper = CvHelper::getInstance();
    Mat erg = helper->scaleImage((mat), 2.0);
    mat = erg;

}

float ScaleModificator::getScale() {
    return 2.0f;
}

