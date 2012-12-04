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

int main() {

    NewCamHandler in = NewCamHandler();
    in.setUseIpCam(false);
    in.open();

    CvVideoCapture cap(in);
    cap.setFramesToRecord(500);
    cap.setTimeToRecord(10);
    cap.setOutput("bla2.avi");
    cap.start();


    return EXIT_SUCCESS;

}
