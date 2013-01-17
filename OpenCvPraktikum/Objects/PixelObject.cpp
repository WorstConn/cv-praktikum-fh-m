/* 
 * File:   PixelObject.cpp
 * Author: Nils Frenking
 * 
 * Created on 17. Januar 2013, 12:45
 */

#include "../header.h"
using namespace std;
using namespace cv;

PixelObject::PixelObject(Mat* objImg) {


    // <editor-fold defaultstate="collapsed" desc="Vorinitialisierung der Objekt-Informationen">
    objectAttributes = new ImageAttributes((*objImg));
    inputAttributes = NULL;
    helper = CvHelper::getInstance();
    // </editor-fold>

    createObjectHistogram();
    createObjectContour();
    createObjectMask();
    createObjectKeypoints();




    inputChanged = false;

}

PixelObject::PixelObject(const PixelObject& orig) {
}

PixelObject::~PixelObject() {
}

/**
 * Gibt an, ob sich die Eingabe ge&auml;ndert hat und die Histoigramme und Masken neu erstellt werden muss.
 * @return <code>true</code>, wenn die Daten <b>NICHT</b> mehr aktuell sind, sonst <code>false</code>.
 */
bool PixelObject::inputChanges() {
    return inputChanged;
}

void PixelObject::setInputChanged(bool bln) {
    inputChanged = bln;
}

/**
 * Gibt die Maske des Objektbildes zur&uuml;ck.
 * @return Die Objektmaske oder <code>NULL</code>.
 */
Mat* PixelObject::getObjectMask() {
    Mat erg = objectAttributes->getMask();
    return &erg;
}

/**
 * Gibt das Histogramm des Objektbildes zur&uuml;ck.
 * @return Das Objekthistogramm, oder <code>NULL</code>.
 */
MatND* PixelObject::getObjectHistogram() {
    MatND erg = objectAttributes->getHistogram();
    return &erg;
}

/**
 * Gibt die errechnete Maske des Eingabe/Vergleichsbildes zur&uuml;ck.
 * @return Die Objektmaske oder <code>NULL</code>.
 */
Mat* PixelObject::getInputMask() {
    if (inputAttributes == NULL) {
        return NULL;
    }
    Mat erg = inputAttributes->getMask();
    return &erg;
}

/**
 * Setzt das Eingabe/Vergleichsbild
 * @param img Das Eingabefarbbild.
 */
void PixelObject::setInputImage(Mat* img) {
    if (inputAttributes == NULL) {
        inputAttributes = new ImageAttributes((*img));
        inputChanged = true;
    } else {
        inputAttributes->setImage((*img));
        inputChanged = true;
    }
}

/**
 * Erstellt ein Histogramm des Objektbildes.
 */
void PixelObject::createObjectHistogram() {

}

/**
 * Erstellt ein Histogramm des Eingabebildes.
 */
void PixelObject::createInputHistogram() {

}

/**
 * Erstellt die Maske des Eingabebildes.
 */
void PixelObject::createObjectMask() {

}

/**
 * Erstellt die Kontour des Objektbildes.
 */
void PixelObject::createObjectContour() {

}

/**
 * Erstellt die Kontour des Eingabebildes.
 */
void PixelObject::createInputContour() {

}

/**
 * Sucht Keypoints auf dem Objektbild.
 */
void PixelObject::createObjectKeypoints() {

}

/**
 * Sucht Keypoints auf dem Eingabebild.
 */
void PixelObject::createInputKeypoints() {

}