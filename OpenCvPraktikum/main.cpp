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

    InputHandler input = InputHandler();
    input.setInputSource(VIDEO_FILE);
    input.addVideo("bla2.avi");
    input.open();

    if (input.requestFormat(r720p)) {
        DBG("Auflösung geändert");
    }
    CvVideoCapture cap(input);
    // cap.setFramesToRecord(500);
    //  cap.setTimeToRecord(5);
    cap.setOutput("bla3.avi");
    RecorderCtl ctl = RecorderCtl("Test");
    ctl.setCapture(&cap);
    //ctl.startGrabInput();
    sleep(10);
    ctl.startRecording();
    sleep(10);
    ctl.stopRecording();
    ctl.stopGrabbing();


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

    all = help->buildImageGrid(images, tags, Scalar(0, 0, 0, 0), 3, 1280, 1024);
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

#if 1



#include <cstdio>
#include <string>
#include <vector>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/nonfree/nonfree.hpp"


using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    Mat img_1 = imread("bild1.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img_2 = imread("bild2.png", CV_LOAD_IMAGE_GRAYSCALE);
     Sobel(img_1, img_1, CV_8U, 1, 1, 5, 0.5, 128);
    Sobel(img_2, img_2, CV_8U, 1, 1, 5, 0.5, 128);
    if (!img_1.data || !img_2.data) {
        std::cout << " --(!) Error reading images " << std::endl;
        return -1;
    }
    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;
    SurfFeatureDetector detector(minHessian);
    std::vector<KeyPoint> keypoints_1, keypoints_2;
    detector.detect(img_1, keypoints_1);
    detector.detect(img_2, keypoints_2);
    //-- Step 2: Calculate descriptors (feature vectors)
    SurfDescriptorExtractor extractor;
    Mat descriptors_1, descriptors_2;
    extractor.compute(img_1, keypoints_1, descriptors_1);
    imshow("Desc1", descriptors_1);
    extractor.compute(img_2, keypoints_2, descriptors_2);
    //-- Step 3: Matching descriptor vectors using FLANN matcher
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match(descriptors_1, descriptors_2, matches);
    double max_dist = 0;
    double min_dist = 200;
    //-- Quick calculation of max and min distances between keypoints
    for (int i = 0; i < descriptors_1.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }
    printf("-- Max dist : %f \n", max_dist);
    printf("-- Min dist : %f \n", min_dist);
    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
    //-- PS.- radiusMatch can also be used here.
    std::vector< DMatch > good_matches;
    for (int i = 0; i < descriptors_1.rows; i++) {
        if (matches[i].distance < 2 * min_dist) {
            good_matches.push_back(matches[i]);
        }
    }
    //-- Draw only "good" matches
    Mat img_matches;
    drawMatches(img_1, keypoints_1, img_2, keypoints_2,
            good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
            vector<char>(), DrawMatchesFlags::DEFAULT);
    //-- Show detected matches
    imshow("Good Matches", img_matches);
    for (int i = 0; i < good_matches.size(); i++) {
        waitKey(0);
        return 0;
    }



}

#endif


#if 0 


using namespace cv;
using namespace std;

Mat src, src_gray;
int
thresh = 200;
int
max_thresh = 255;
String source_window = "Source image";
String corners_window = "Corners detected";
/// Function header
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
//find . -name '*.jpg' -exec identify -format '%i 1 0 0 %w %h' \{\} \; > info.dat
//http://docs.opencv.org/doc/user_guide/ug_traincascade.html
//find . -name '*.jpg' -exec identify -format '%i 1 0 0 %w %h' \{\} \; > info.dat
//opencv_traincascade -data hnd -vec samples.vec -bg /media/WD-Platte/Bilder\&Fotos/Wallpaper/bg.dat -numPos 100 -numNeg 340 -numStages 20 -precalcValBufSize 1024 -precalcIdxBufSize 2048 -featureType LBP -w 200 -h 200 -minHitRate 0.999 -maxFalseAlarmRate 0.5 -mode ALL
//http://note.sonots.com/SciSoftware/haartraining.html#ybd647df