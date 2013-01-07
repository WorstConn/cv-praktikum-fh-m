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


int WindowManagerTest::testMain(vector<String> args) {
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
    Window* wnd = manager->createWindow("Test1");
    wnd->showWindow();
    manager->putTrackbarCallback(this, "Test1");
    wnd->setCurrentImage(&img);
    

    waitKey(0);

    return EXIT_SUCCESS;

}

void WindowManagerTest::action(int pos, void* data) {
    cout << "Nix" << endl;
    cvtColor((*img),(*img),CV_BGR2GRAY);
    
}
