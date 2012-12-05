/*
 * ACamHandler.cpp
 *
 *  Created on: 06.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#include "header.h"

ACamHandler::ACamHandler() {
    connected = false;
    defaultIpCamURL = "http://192.168.2.28:8080/videofeed";
    ipCam = false;
}


ACamHandler::ACamHandler(const char* camURL) {
    connected = false;
    defaultIpCamURL = camURL;
    ipCam = false;
}

ACamHandler::~ACamHandler() {
    
}

bool ACamHandler::isOpen() {
    return connected;
}

bool ACamHandler::useIpCam() {
    return ipCam;
}

void ACamHandler::setUseIpCam(bool val) {
    ipCam = val;
}






