/*
 * CamHandler.cpp
 *
 *  Created on: 06.11.2012
 *      Author: Nils Frenking
 */

#include "header.h"

CamHandler::CamHandler() {
    connected = false;
    defaultIpCamURL = "http://192.168.2.28:8080/videofeed";
    ipCam = false;
}


CamHandler::CamHandler(const char* camURL) {
    connected = false;
    defaultIpCamURL = camURL;
    ipCam = false;
}

CamHandler::~CamHandler() {
    
}

bool CamHandler::isOpen() {
    return connected;
}

bool CamHandler::useIpCam() {
    return ipCam;
}

void CamHandler::setUseIpCam(bool val) {
    ipCam = val;
}






