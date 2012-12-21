/* 
 * File:   Prak3A8.cpp
 * Author: Nils Frenking
 * 
 * Created on 21. Dezember 2012, 12:55
 */

#include "../header.h"
using namespace std;
using namespace cv;

Prak3A8::Prak3A8() {
}

Prak3A8::Prak3A8(const Prak3A8& orig) {
}

Prak3A8::~Prak3A8() {
}

int Prak3A8::testMain(vector<String> args) {
    InputHandler input = InputHandler();
    input.setInputSource(INPUT_CAM);
    //input.addVideo("/home/ertai/Videos/VIDEO0023.mp4");
    input.open();

    if (input.requestFormat(r720p)) {
        DBG("Auflösung geändert");
    }

    ImageListOutput out("/home/ertai/NetBeansProjects/OpenCvPraktikum/imgseq_out", "bg4");

       RecorderCtl ctl = RecorderCtl("Test");

       ctl.startGrabInput();
       sleep(1);
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

