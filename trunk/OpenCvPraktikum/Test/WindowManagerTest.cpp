/* 
 * File:   WindowManagerTest.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 6. Januar 2013, 14:04
 */

#include "../header.h"

using namespace std;
using namespace cv;

WindowManagerTest::WindowManagerTest() : AImageAction("TestAction", "Test1", 100) {
    manager = WindowManager::getInstance();
}

WindowManagerTest::WindowManagerTest(const WindowManagerTest& orig) : AImageAction(orig) {
}

WindowManagerTest::~WindowManagerTest() {
}

int WindowManagerTest::testMain(StringArray args) {
    InputHandler handler = InputHandler();
    handler.addImageFolder("/home/ertai/Bilder");
    handler.setInputSource(INPUT_FOLDER);
    if (!handler.open()) {
        cout << "Konnte Eingabe nicht oeffnen" << endl;
        return EXIT_FAILURE;
    }


    handler.grabNext();

    Mat img = handler.getImage();
    updateImage(&img);
    CvWindow* wnd = manager->createWindow("Test1");
    wnd->showWindow();
    manager->putTrackbarCallback(this, "Test1");
    wnd->setCurrentImage(&img);


    waitKey(0);

    return EXIT_SUCCESS;

}

void WindowManagerTest::action(int pos, void* data) {
    Mat* tmpGray = new Mat(img->size(), CV_8UC1);
    Mat* tmpBGR = new Mat(img->size(), img->type());
    cvtColor((*img), (*tmpGray), CV_BGR2GRAY);
    if (pos < getMin()) {
        pos = getMin();
    }

    Canny((*tmpGray), (*tmpGray), pos * 2, pos * 2 * 3);
    cvtColor((*tmpGray), (*tmpBGR), CV_GRAY2BGR);
    CvWindow* w = manager->getWindow("Test1");
    w->setCurrentImage(tmpBGR);
    tmpGray->release();
    tmpGray = NULL;
    tmpBGR->release();
    tmpBGR = NULL;


}

void WindowManagerTest::printUsage() {
    cout << "No Arguments supported" << endl;
}
