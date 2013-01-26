/* 
 * File:   ExtendedImageAttributes.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 17. Januar 2013, 13:54
 */

#ifndef EXTENDEDIMAGEATTRIBUTES_H
#define	EXTENDEDIMAGEATTRIBUTES_H

#include "../header.h"
using namespace std;
using namespace cv;

/**
 * Datenklasse f&uuml;r Bildmerkmale
 */
class ExtendedImageAttributes {
public:

    ExtendedImageAttributes();
    ExtendedImageAttributes(Mat img);
    ExtendedImageAttributes(Mat img, MatND hist);
    ExtendedImageAttributes(Mat img, MatND hist, Mat mask);
    ExtendedImageAttributes(Mat img, MatND hist, Mat mask, PointArray cont);
    ExtendedImageAttributes(Mat img, MatND hist, Mat mask, KeyPointArray kp);
    ExtendedImageAttributes(Mat img, MatND hist, Mat mask, KeyPointArray kp, PointArray cont);

    Mat getImage();
    MatND getHistogram();
    Mat getMask();
    KeyPointArray getKeyPoints();
    PointArray getContour();

    void setImage(Mat img);
    void setHistogram(MatND);
    void setMask(Mat mask);
    void setKeyPoints(KeyPointArray kp);
    void setContourPoints(PointArray cont);


    ExtendedImageAttributes(const ExtendedImageAttributes& orig);
    virtual ~ExtendedImageAttributes();

private:

    /**
     * Histogramm des Bildes
     */
    MatND imageHistogram;

    /**
     * Das Bild.
     */
    Mat image;

    /**
     * Bildmaske.
     */
    Mat imageMask;

    /**
     * Keypoints des Bildes.
     */
    KeyPointArray imageKeypoints;

    /**
     * Kontourpunkte des Bildes.
     */
    PointArray imageContour;


};

#endif	/* EXTENDEDIMAGEATTRIBUTES_H */

