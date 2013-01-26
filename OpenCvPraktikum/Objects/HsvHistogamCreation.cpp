/* 
 * File:   HsvHistogamCreation.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 21. Januar 2013, 00:11
 */

#include "../header.h"
using namespace std;
using namespace cv;

HsvHistogamCreation::HsvHistogamCreation() {
}

HsvHistogamCreation::HsvHistogamCreation(const HsvHistogamCreation& orig) {
}

HsvHistogamCreation::~HsvHistogamCreation() {
}

MatND HsvHistogamCreation::createHistogram(Mat img, Mat mask){
    CvHelper* helper = CvHelper::getInstance();
    MatND erg = helper->makeHSHist(img,mask);
    return erg;
}
