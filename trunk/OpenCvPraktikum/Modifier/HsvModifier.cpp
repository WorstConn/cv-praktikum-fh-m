/* 
 * File:   HsvModifier.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 20. Dezember 2012, 11:56
 */


#include "../header.h"
using namespace std;
using namespace cv;

HsvModifier::HsvModifier() {
    helper = CvHelper::getInstance();
}

HsvModifier::HsvModifier(const HsvModifier& orig) {
    helper = orig.helper;
}

HsvModifier::~HsvModifier() {
    if (helper != NULL) {
        delete helper;
    }
}

bool HsvModifier::doesAction() {
    return true;
}

float HsvModifier::getScale() {
    return 1.0f;
}

void HsvModifier::modify(Mat& mat) {
    Mat erg = Mat::zeros(mat.size(), CV_8UC3);
    cvtColor(mat, erg, CV_BGR2HSV);
    mat = erg;

}



