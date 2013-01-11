/* 
 * File:   Prak3A8.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 21. Dezember 2012, 12:55
 */

#include "../header.h"
using namespace std;
using namespace cv;

void Prak3A8::testCB(int pos, void* dat) {

}

Prak3A8::Prak3A8() {
    threshold = 1;
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

    //ImageListOutput out("/home/ertai/NetBeansProjects/OpenCvPraktikum/imgseq_out", "bg4");

    namedWindow("Gauss");
    namedWindow("Hist1");
    namedWindow("Eq");
    namedWindow("Hist2");
    namedWindow("Gauss-BW");
    namedWindow("Eq-BW");

    //wnd->addTrackbar(String("Bla"),String("P3A8"),static_cast<TrackbarCallback>(&Prak3A8::testCB));
    createTrackbar(String("Gauss"), "Gauss", &threshold, 200);
    sleep(1);
    //    ctl.stopRecording();
    //    ctl.stopGrabbing();
    CvHelper* help = CvHelper::getInstance();
    Mat grid = Mat::zeros(Size(1280, 1024), CV_8UC3);
    Mat frame;
    Mat gray;
    Mat gauss, hist1, hist2, histEq, histEqBW, gaussBW;
    MatND histo1;
    MatND histo2;
    vector<String> tags = vector<String > ();






    DBG("Starte Loop");
    while (true) {
        input.next();
        frame = input.getImage();
        vector<Mat*> images;

        gray = Mat::zeros(frame.size(), CV_8UC1);
        DBG("Convert Grayscale");
        cvtColor(frame, gray, CV_BGR2GRAY);
        DBG("Gaussian Blur");
        if (threshold <= 1) {
            threshold = 1;
        }
        if (threshold % 2 == 0) {
            threshold += 1;
        }
        gauss = help->gaussianBlur(gray, threshold, true);
        imshow("Gauss", gauss);

        DBG("Equalize Hist");
        histEq = help->equalizeHistogram(gauss, true, false);

        imshow("Eq", histEq);


        DBG("Create Gauss BW");
        gaussBW = help->convertBlackAndWhite(gauss, 127);

        imshow("Gauss-BW", gaussBW);
        DBG("Create HistEq BW");
        histEqBW = help->convertBlackAndWhite(histEq, 127);
        imshow("Eq-BW", histEqBW);


        DBG("Create Hist 1");
        histo1 = help->makeHist(&gauss);

        hist1 = help->makeHistImage(histo1);

        DBG("Create Hist 2");
        histo2 = help->makeHist(&histEq);

        hist2 = help->makeHistImage(histo2);
        DBG("Showing image");

        imshow("Hist1", hist1);

        imshow("Hist2", hist2);



        DBG("Clean Up");
        images.clear();
        frame.release();
        gray.release();
        gauss.release();
        hist1.release();
        hist2.release();
        histEq.release();
        histEqBW.release();
        gaussBW.release();
        int c = waitKey(1);

        if (c != -1) {
            break;
        }

    }
    input.close();
    destroyAllWindows();
    return EXIT_SUCCESS;
}

void Prak3A8::printUsage() {
    cout << "No Arguments supported" << endl;
}


