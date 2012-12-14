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

    CamHandler input = CamHandler();
    input.setUseIpCam(false);
    input.open();

//    if (input.requestFormat(r720p)) {
//        DBG("Auflösung geändert");
//    }
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




// Tipp: falls dir das Erstellen immer zu lange dauert, 
// gehe in den Projektordner und führe von dort 'make -j N' -> N anzahl der synchronen "JOBS"

