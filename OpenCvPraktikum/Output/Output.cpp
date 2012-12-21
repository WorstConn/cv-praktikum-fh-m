/* 
 * File:   Output.cpp
 * Author: Nils Frenking
 * 
 * Created on 19. Dezember 2012, 20:47
 */

#include "../header.h"
using namespace std;
using namespace cv;

Output::Output(String p, String n, String fileExt) {
    outputName = n;
    outputPath = p;
    pathExists = checkPath(p);
    fileExists = checkFile(p + PATH_SEPARATOR + n);
    outputSize = Size();
    opened = false;
    fileExtension = fileExt;
}

Output::Output(const Output& orig) {
    outputName = orig.outputName;
    outputPath = orig.outputPath;
    pathExists = orig.pathExists;
    fileExists = orig.fileExists;
    outputSize = orig.outputSize;
    opened = orig.opened;
    fileExtension = orig.fileExtension;
}

Output::~Output() {
}

String Output::getOutputName() {
    return outputName;
}

String Output::getOutputPath() {
    if (outputPath.compare(outputPath.length() - 1, 1, PATH_SEPARATOR) == 0) {
        
        outputPath = outputPath.substr(0, outputPath.length() - 1);
        DBG("Ausgabepfad berichtigt");
    }
    return outputPath;
}

bool Output::checkPath(String p) {
    return FileManager::getInstance()->checkDir(p);

}

bool Output::isOpen() {
    return opened;
}

bool Output::checkFile(String f) {
    if (!checkPath(outputPath)) {
        return false;
    } else {
        return FileManager::getInstance()->checkFile(outputPath + PATH_SEPARATOR + f);
    }
}

void Output::setSize(Size s) {
    outputSize = s;
}

String Output::getFullPath() {
    if (!fileExists && !pathExists) {
        DBG("Kein gueltiger Pfad gegeben!");
        return "";
    }
    return outputPath + PATH_SEPARATOR + outputName;

}

