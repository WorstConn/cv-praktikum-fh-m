/* 
 * File:   BgFgSegmModificator.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 3. Januar 2013, 14:50
 */

#include "../header.h"

BgFgSegmModificator::BgFgSegmModificator(String bgImage) {
    if (!FileManager::getInstance()->checkFile(bgImage)) {
        DBG("Eingabedatei %s existiert nicht!", bgImage.c_str());
        return;
    }
    bg = imread(bgImage);
    if (helper == NULL) {
        helper = CvHelper::getInstance();
    }

}

BgFgSegmModificator::BgFgSegmModificator(Mat bgImage) {
    bg = bgImage;
    if (helper == NULL) {
        helper = CvHelper::getInstance();
    }
}

BgFgSegmModificator::BgFgSegmModificator(const BgFgSegmModificator& orig) : ImageModificator(orig) {
}

BgFgSegmModificator::~BgFgSegmModificator() {
}

float BgFgSegmModificator::getScale() {
    return 1.0f;
}

void BgFgSegmModificator::modify(Mat& mat) {
    Mat erg = Mat::zeros(mat.size(), CV_8UC3);
    //Differenzbild erzeugen
    absdiff(mat, bg, erg);

    Mat bw = Mat::zeros(mat.size(), CV_8UC1);
    cvtColor(erg, bw, CV_BGR2GRAY);
    // leict verwischen, um stoerungen zu unterdruecken.
    blur(bw, bw, Size(7, 7), Point(-1, -1), CV_BLUR);
    // zu Schwarz-Weiß konvertieren
    threshold(bw, bw, 25, 255, CV_THRESH_BINARY);
    erg = Mat::zeros(mat.size(), CV_8UC3);
    // unter Verwendung des Eingabebildes und der erstellten Maske, das Ergebnisbild erzeugen.
    mat.copyTo(erg, bw);
    bw.release();
    mat = erg;
}
