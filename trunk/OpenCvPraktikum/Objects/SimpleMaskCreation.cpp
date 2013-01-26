/* 
 * File:   SimpleMaskCreation.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 18. Januar 2013, 17:34
 */

#include "../header.h"

using namespace std;
using namespace cv;

SimpleMaskCreation::SimpleMaskCreation(Mat& bg) {
    background = bg;
}

SimpleMaskCreation::SimpleMaskCreation(const SimpleMaskCreation& orig) {
    background = orig.background;
}

SimpleMaskCreation::~SimpleMaskCreation() {
}

/**
 * Erstellt eine Maske des gegebenen Bildes.
 * @param img Das Eingabebild.
 * @return Die bin&auml;re Maske des Bildes. Interessante bereiche sind mit 1 codiert.
 */
Mat SimpleMaskCreation::createMask(Mat& img) {
    if (background.empty()) {
        DBG("Kein Hintergrund zur Segmentierung vorhanden!");
        return img;
    }
    if (img.empty()) {
        DBG("Eingabe leer!");
        return img;
    }

    Mat erg = Mat::zeros(img.size(), CV_8UC3);
    absdiff(img, background, erg);
    blur(erg, erg, Size(7, 7));
    Mat gray = Mat::zeros(erg.size(), CV_8UC1);
    cvtColor(erg, gray, CV_BGR2GRAY);
    threshold(gray, gray, 80, 255, THRESH_BINARY);
    erg.release();
    erg = gray;
    return erg;
}