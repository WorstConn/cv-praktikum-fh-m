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
std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;

//void save_page(const std::string &url)
//{
//    // simulate a long page fetch
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//    std::string result = "fake content";
// 
//    g_pages_mutex.lock();
//    g_pages[url] = result;
//    g_pages_mutex.unlock();
//}

int main() {
    //    std::thread t1(save_page, "http://foo");
    //    std::thread t2(save_page, "http://bar");
    //    t1.join();
    //    t2.join();
    // 
    //    g_pages_mutex.lock();
    //    for (const auto &pair : g_pages) {
    //        std::cout << pair.first << " => " << pair.second << '\n';
    //    }
    //    g_pages_mutex.unlock();

    FileManager manager;
    NewCamHandler in = NewCamHandler();
    in.setUseIpCam(false);
    in.open();

    CvVideoCapture cap(in);
    cap.setFramesToRecord(50);
    cap.setOutput("bla.avi");
    cap.start();

    
    //cap.record();

    DBG("Blub");


    //manager.find(".jpg","/home");
    //    
    return EXIT_SUCCESS;

}
#endif
#if 0

int main(int, char**) {
    VideoCapture capture(0); // open the default camera
    if (!capture.isOpened()) {
        printf("Camera failed to open!\n");
        return -1;
    }

    Mat frame;
    capture >> frame; // get first frame for size

    // record video
    VideoWriter record("RobotVideo.avi", CV_FOURCC('D', 'I', 'V', 'X'), 30, frame.size(), true);
    if (!record.isOpened()) {
        printf("VideoWriter failed to open!\n");
        return -1;
    }

    namedWindow("video", 1);

    for (;;) {
        // get a new frame from camera
        capture >> frame;

        // show frame on screen
        imshow("video", frame);

        // add frame to recorded video
        record << frame;

        if (waitKey(30) >= 0) break;
    }

    // the camera will be deinitialized automatically in VideoCapture destructor
    // the recorded video will be closed automatically in the VideoWriter destructor
    return 0;
}
#endif