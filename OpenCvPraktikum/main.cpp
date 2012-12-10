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

    CamHandler in = CamHandler();
    in.setUseIpCam(false);
    in.open();

    CvVideoCapture cap(in);
    cap.setFramesToRecord(500);
    cap.setTimeToRecord(5);
    ScaleModificator mod;
    cap.setImageModifikator(&mod);  // Bringt irgendwie nichts...
    cap.setOutput("bla2.avi");
    cap.start();


    return EXIT_SUCCESS;

}




// Tipp: falls dir das Erstellen immer zu lange dauert, 
// gehe in den Projektordner und führe von dort 'make -j N' -> N anzahl der synchronen "JOBS"

