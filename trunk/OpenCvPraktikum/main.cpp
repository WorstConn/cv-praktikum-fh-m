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

#if 1

using namespace std;
using namespace cv;

int main() {

    InputHandler input = InputHandler();
    input.setInputSource(INPUT_CAM);
    //input.addVideo("/home/ertai/Videos/VIDEO0023.mp4");
    input.open();

    if (input.requestFormat(r720p)) {
        DBG("Auflösung geändert");
    }
    //    CvVideoCapture cap(input);
    //    cap.setFramesToRecord(50000);
    //    cap.setTimeToRecord(15);
    ImageListOutput out("/home/ertai/NetBeansProjects/OpenCvPraktikum/imgseq_out", "bg4");
    //    cap.setOutput(&out);
    //    RecorderCtl ctl = RecorderCtl("Test");
    //    ctl.setCapture(&cap);

    //    ctl.startGrabInput();
    //    sleep(1);
    //    ctl.startRecording();
    //    sleep(15);
    //    ctl.stopRecording();
    //    ctl.stopGrabbing();
    CvHelper* help = CvHelper::getInstance();
    Mat grid = Mat::zeros(Size(800, 600), CV_8UC3);
    Mat frame;
    vector<String> tags = vector<String > ();
    tags.push_back("Normal");
    tags.push_back("Gauß");
    tags.push_back("Hist.Eq.");
    tags.push_back("Hist pre");
    tags.push_back("Hist post");

    while (true) {
        input.next();
        frame = input.getImage();
        vector<Mat*> images;
        grid = help->equalizeHistogram(frame, true, true);
        
    }

    return EXIT_SUCCESS;

}
#endif

Mat origImage;
int cannyLow = 1, cannyHigh = 350;

#if 0

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

    origImage = imread("hands.png");
    Mat sobelX, sobelY, sobel;


    MatND histo;
    Mat histImg;
    namedWindow("Bild");
    namedWindow("BinBild");
    namedWindow("Histogram");
    namedWindow("SobelX");
    namedWindow("SobelY");
    namedWindow("Canny");
    namedWindow("Alle");

    cvCreateTrackbar("CannyTrack", "Canny",
            &cannyLow, 255, callbackCanny);
    cvCreateTrackbar("CannyTrackHigh", "Canny",
            &cannyHigh, 400, callbackCanny);



    Sobel(origImage, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
    Sobel(origImage, sobelY, CV_8U, 0, 1, 3, 0.4, 128);

    sobel = sobelX;
    double sobelMin, sobelMax;

    minMaxLoc(sobel, &sobelMin, &sobelMax);
    Mat image, binImage, all;
    sobel.convertTo(image, CV_8U, -255.0 / sobelMax, 255);
    threshold(image, binImage, 30, 255, cv::THRESH_BINARY);

    Mat cannyImage, cannyImageInv;

    Canny(origImage, cannyImage, 125, 350);
    threshold(cannyImage, cannyImageInv, 128, 255, THRESH_BINARY_INV);



    histo = help->makeHist(&image);
    histImg = help->makeHistImage(histo);


    DBG("Baue Vektoren");
    vector<Mat*> images = vector<Mat*>();
    images.push_back(&image);
    images.push_back(&binImage);
    images.push_back(&sobelX);
    images.push_back(&sobelY);
    images.push_back(&histImg);
    images.push_back(&cannyImageInv);
    vector<String> tags = vector<String > ();
    tags.push_back("Bild");
    tags.push_back("BinBild");
    tags.push_back("SobelX");
    tags.push_back("SobelY");
    tags.push_back("Histogram");
    tags.push_back("Canny");

    all = help->buildImageGrid(images, tags, Scalar(0, 0, 255, 0), 3, 1280, 1024);
    imshow("Bild", image);
    imshow("BinBild", binImage);
    imshow("SobelX", sobelX);
    imshow("SobelY", sobelY);
    imshow("Histogram", histImg);
    imshow("Canny", cannyImageInv);
    imshow("Alle", all);
    waitKey(300);

    waitKey(0);

    printf("bin am ende !\n");

    return EXIT_SUCCESS;
}

#endif

#if 0



#include <cstdio>
#include <string>
#include <vector>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/nonfree/nonfree.hpp"


using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    int hesse = 400;

    Mat input1 = imread("bild1.png", CV_LOAD_IMAGE_GRAYSCALE);
    InputHandler* handler = new InputHandler();
    handler->setInputSource(INPUT_CAM);
    handler->requestFormat(INPUT_FORMAT::r720p);
    handler->open();
    handler->grabNext();
    Mat input2;

    if (input1.data == NULL) {
        DBG_EXIT(" --(!) Error reading images ");

    }



    CvHelper* help = CvHelper::getInstance();


    namedWindow("H-S Histogram");
    while (true) {
        handler->grabNext();
        input2 = handler->getImage();
        MatND histo = help->makeHSHist(input2);
        help->makeHSHistImage(histo);
        DBG("Histogram Erstellt")
        help->applySurfDetect(input1, input2, hesse, 10, 50);
        int c = waitKey(1);

        if (c != -1) {
            break;
        }
    }
    return EXIT_SUCCESS;







}

#endif


#if 0 


using namespace cv;
using namespace std;

Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;
String source_window = "Source image";
String corners_window = "Corners detected";

void cornerHarris_demo(int, void*);

/** @function main */
int main(int argc, char** argv) {
    /// Load source image and convert it to gray
    src = imread("bild1.png", 1);
    cvtColor(src, src_gray, CV_BGR2GRAY);
    /// Create a window and a trackbar
    namedWindow(source_window, CV_WINDOW_AUTOSIZE);
    createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
    imshow(source_window, src);
    cornerHarris_demo(0, 0);
    waitKey(0);
    return (0);

}

/** @function cornerHarris_demo */
void cornerHarris_demo(int, void*) {
    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros(src.size(), CV_32FC1);
    /// Detector parameters
    int blockSize = 1;
    int apertureSize = 3;
    double k = 0.04;
    /// Detecting corners
    cornerHarris(src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
    /// Normalizing
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);
    /// Drawing a circle around corners
    for (int j = 0; j < dst_norm.rows; j++) {
        for (int i = 0; i < dst_norm.cols; i++) {
            if ((int) dst_norm.at<float>(j, i) > thresh) {
                circle(dst_norm_scaled, Point(i, j), 5,
                        Scalar(0), 2, 8, 0);
            }
        }
    }
    /// Showing the result
    namedWindow(corners_window, CV_WINDOW_AUTOSIZE);
    imshow(corners_window, dst_norm_scaled);
}

#endif

// Tipp: falls dir das Erstellen immer zu lange dauert, 
// gehe in den Projektordner und führe von dort 'make -j N' -> N anzahl der synchronen "JOBS"





//Samples erstellen
//opencv_createsamples -img 01.png -num 10 -bg /media/WD-Platte/Bilder\&Fotos/Wallpaper/bg.dat -vec samples.vec -maxxangle 0.6 -maxyangle 0 -maxzangle 0.3 -maxidev 100 -bgcolor 0 -bgthresh 0 -w 200 -h 200
//http://docs.opencv.org/doc/user_guide/ug_traincascade.html
//find . -name '*.jpg' -exec identify -format '%i 1 0 0 %w %h' \{\} \; > info.dat
//opencv_traincascade -data hnd -vec samples.vec -bg /media/WD-Platte/Bilder\&Fotos/Wallpaper/bg.dat -numPos 100 -numNeg 340 -numStages 20 -precalcValBufSize 1024 -precalcIdxBufSize 2048 -featureType LBP -w 200 -h 200 -minHitRate 0.999 -maxFalseAlarmRate 0.5 -mode ALL
//http://note.sonots.com/SciSoftware/haartraining.html#ybd647df


//FIXME: PRAKTIKUM!!
//TODO: Ein paar Modifikatoren...
//TODO: Schreiberthread-Queue für ImageListOutput
//TODO: Die Einzelnen Mains in Unterfkt. packen, und von der cmd auswählbar machen.
