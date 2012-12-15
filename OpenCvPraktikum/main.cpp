/*
 * main.cpp
 *
 *  Created on: 18.11.2012
 *      Author: Nils Frenking
 */

#include "header.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <string>

#if 0

int main() {

    CamHandler input = CamHandler();
    input.setUseIpCam(false);
    input.open();

    if (input.requestFormat(r720p)) {
        DBG("Auflösung geändert");
    }
    CvVideoCapture cap(input);
   // cap.setFramesToRecord(500);
  //  cap.setTimeToRecord(5);
    cap.setOutput("bla2.avi");
    RecorderCtl ctl = RecorderCtl("Test");
    ctl.setCapture(&cap);
    ctl.startGrabInput();
    sleep(10);
    ctl.startRecording();
    sleep(10);
    ctl.stopRecording();
    ctl.stopGrabbing();
    ScaleModificator mod;

    return EXIT_SUCCESS;

}
#endif

Mat origImage;
int cannyLow = 1, cannyHigh = 350;

#if 1

void doCanny() {
    Mat cannyImage, cannyImageInv;
    
    Canny(origImage, cannyImage, cannyLow, cannyHigh);
    threshold(cannyImage, cannyImageInv, 128, 255, THRESH_BINARY_INV);
    imshow("Canny", cannyImageInv);
}

void callbackCanny(int pos) {
    doCanny();
    DBG("canny erneut mit lowThreshold = %d, highThreshold = %d angewendet!", cannyLow, cannyHigh);
}



int main() {
    CvHelper *help = CvHelper::getInstance();
    
    origImage = imread("bild.jpg");
    Mat sobelX, sobelY, sobel;
   
    
    MatND histo;
    Mat histImg;
    namedWindow("Bild");
    namedWindow("BinBild");
    namedWindow("Histogram");
    namedWindow("SobelX");
    namedWindow("SobelY");
    namedWindow("Canny");
   
    cvCreateTrackbar( "CannyTrack", "Canny",
                      &cannyLow, 255, callbackCanny );
    cvCreateTrackbar( "CannyTrackHigh", "Canny",
                      &cannyHigh, 400, callbackCanny);
    

    
    Sobel(origImage, sobelX, CV_8U,1,0,3,0.4,128);
    Sobel(origImage, sobelY, CV_8U,0,1,3,0.4,128);
    
    sobel = sobelX;
    double sobelMin, sobelMax;
    
    minMaxLoc(sobel, &sobelMin, &sobelMax);
    Mat image, binImage;
    sobel.convertTo(image, CV_8U, -255.0/sobelMax, 255);
    threshold(image,binImage,30,255, cv::THRESH_BINARY);
    
    Mat cannyImage, cannyImageInv;
    
    Canny(origImage, cannyImage, 125, 350);
    threshold(cannyImage, cannyImageInv, 128, 255, THRESH_BINARY_INV);
    
    
    
    histo =help->makeHist(&image);
    histImg = help->makeHistImage(histo);
    imshow("Bild", image);
    imshow("BinBild", binImage);
    imshow("SobelX", sobelX);
    imshow("SobelY", sobelY);
    imshow("Histogram", histImg);
    imshow("Canny", cannyImageInv);
    waitKey(300);
    
    waitKey(0);
    
    printf("bin am ende !\n");
    
    return EXIT_SUCCESS;
}

#endif



// Tipp: falls dir das Erstellen immer zu lange dauert, 
// gehe in den Projektordner und führe von dort 'make -j N' -> N anzahl der synchronen "JOBS"

