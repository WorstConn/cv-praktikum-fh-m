/*
 * AInputHandler.cpp
 *
 *  Created on: 06.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#include "../header.h"

AInputHandler::AInputHandler() {
    connected = false;
    defaultIpCamURL = "http://192.168.2.28:8080/videofeed";
    sourceType = INPUT_NONE;
    imageFolders = CvStringSet();
    videoFiles = CvStringArray();
    imageFiles = CvStringArray();
}

AInputHandler::AInputHandler(String camURL) {
    connected = false;
    defaultIpCamURL = camURL;
    sourceType = INPUT_NONE;
    imageFolders = CvStringSet();
    videoFiles = CvStringArray();
    imageFiles = CvStringArray();

}

AInputHandler::AInputHandler(const AInputHandler& orig) {
    connected = orig.connected;
    defaultIpCamURL = orig.defaultIpCamURL;
    sourceType = orig.sourceType;
    videoFiles = orig.videoFiles;
    imageFolders = orig.imageFolders;
    imageFiles = orig.imageFiles;

}

AInputHandler::~AInputHandler() {

}

bool AInputHandler::isOpen() {
    return connected;
}

bool AInputHandler::useIpCam() {
    return (sourceType == INPUT_IP_CAM);
}

void AInputHandler::setUseIpCam() {

    sourceType = INPUT_IP_CAM;
}

/**
 * F&uuml;gt ein Video hinzu
 * @param vid Der Pfad des Videos
 * @return <code>true</code>, wenn die Datei existiert und hinzugef&uuml;gt wurde. Sonst <code>false</code>
 */
bool AInputHandler::addVideo(String vid) {
    DBG("Checke Video Datei");
    if (FileManager::getInstance()->checkFile(vid)) {
        DBG("Datei %s gefunden", vid.c_str());
        videoFiles.push_back(vid);

        return true;
    }
    DBG("Video konnte nicht gefunden werden");
    return false;
}

/**
 * F&uuml;gt einen Bilderordner hinzu
 * @param folder Der Pfad zu einem Ordner, in dem nach Bildern (.jpg, .png, .bmp) gesucht wird 
 * @return <code>true</code>, wenn der Order existiert und hinzugef&uuml;gt wurde. Sonst <code>false</code>
 */
bool AInputHandler::addImageFolder(String folder) {
    DBG("Checke Bilderordner");
    if (FileManager::getInstance()->checkDir(folder) != -1) {
        DBG("Ordner %s gefunden", folder.c_str());
        imageFolders.insert(folder);

        return true;
    }
    DBG("Ordner %s nicht gefunden", folder.c_str());
    return false;
}

void AInputHandler::setInputSource(INPUT_TYPE type) {
    sourceType = type;
}

INPUT_TYPE AInputHandler::getInputSource() {
    return sourceType;
}







