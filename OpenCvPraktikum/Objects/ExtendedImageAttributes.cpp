/* 
 * File:   ExtendedImageAttributes.cpp
 * Author: Nils Frenking
 * 
 * Created on 17. Januar 2013, 13:54
 */

#include "../header.h"
using namespace std;
using namespace cv;

ExtendedImageAttributes::ExtendedImageAttributes() {
}

ExtendedImageAttributes::ExtendedImageAttributes(Mat img) {
    image = img;
}

ExtendedImageAttributes::ExtendedImageAttributes(Mat img, MatND hist) {
    image = img;
    imageHistogram = hist;
}

ExtendedImageAttributes::ExtendedImageAttributes(Mat img, MatND hist, Mat mask) {
    image = img;
    imageHistogram = hist;
    imageMask = mask;

}

ExtendedImageAttributes::ExtendedImageAttributes(Mat img, MatND hist, Mat mask, PointArray cont) {
    image = img;
    imageHistogram = hist;
    imageMask = mask;
    imageContour = cont;
}

ExtendedImageAttributes::ExtendedImageAttributes(Mat img, MatND hist, Mat mask, KeyPointArray kp) {
    image = img;
    imageHistogram = hist;
    imageMask = mask;
    imageKeypoints = kp;
}

ExtendedImageAttributes::ExtendedImageAttributes(Mat img, MatND hist, Mat mask, KeyPointArray kp, PointArray cont) {
    image = img;
    imageHistogram = hist;
    imageMask = mask;
    imageContour = cont;
    imageKeypoints = kp;
}

ExtendedImageAttributes::ExtendedImageAttributes(const ExtendedImageAttributes& orig) {
    image = orig.image;
    imageContour = orig.imageContour;
    imageHistogram = orig.imageHistogram;
    imageKeypoints = orig.imageKeypoints;
    imageMask = orig.imageMask;
}

ExtendedImageAttributes::~ExtendedImageAttributes() {
}

Mat ExtendedImageAttributes::getImage() {
    return image;
}

MatND ExtendedImageAttributes::getHistogram() {
    return imageHistogram;
}

Mat ExtendedImageAttributes::getMask() {
    return imageMask;
}

KeyPointArray ExtendedImageAttributes::getKeyPoints() {
    return imageKeypoints;
}

PointArray ExtendedImageAttributes::getContour() {
    return imageContour;
}

void ExtendedImageAttributes::setImage(Mat img) {
    image = img;
}

void ExtendedImageAttributes::setHistogram(MatND hist) {
    imageHistogram = hist;
}

void ExtendedImageAttributes::setMask(Mat mask) {
    imageMask = mask;
}

void ExtendedImageAttributes::setKeyPoints(KeyPointArray kp) {
    imageKeypoints = kp;
}

void ExtendedImageAttributes::setContourPoints(PointArray cont) {
    imageContour = cont;
}
