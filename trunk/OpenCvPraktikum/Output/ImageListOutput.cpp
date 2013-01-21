/* 
 * File:   ImageListOutput.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 20. Dezember 2012, 00:57
 */

#include "../header.h"

using namespace std;
using namespace cv;

ImageListOutput::ImageListOutput(String p, String n, String fileExt) : Output(p, n, fileExt) {
    counter = 0;
    writeParams = vector<int>();
    
}

ImageListOutput::ImageListOutput(const ImageListOutput& orig) : Output(orig) {
    counter = orig.counter;
    writeParams = writeParams;
}

ImageListOutput::~ImageListOutput() {
}

bool ImageListOutput::open() {
#ifdef DEBUG
    if (!pathExists) {
        DBG("Pfad existiert nicht: %s", outputPath.c_str());

    }
#endif 
    opened = pathExists;
    return pathExists;
}

void ImageListOutput::close() {
    //NIX
}

/**
 * Schreibt das Bild mit aufsteigender Nummerierung in den Ordner.
 * @param mat 
 */
void ImageListOutput::write(Mat& mat) {
    if (!opened) {
        DBG("Kann Bilder an diesem Ort nicht schreiben: %s", getFullPath().c_str());
        return;
    }
    Mat w = mat;
    if (outputSize.height > 0 && outputSize.width > 0) {
        if (outputSize.width != w.size().width or outputSize.height != w.size().height) {
            resize(mat, w, outputSize, 0, 0, CV_INTER_CUBIC);
        }
    }
    imwrite(outputPath + PATH_SEPARATOR + outputName + convertInt(counter) + fileExtension, w, createWriteParams());
    counter++;
    w.release();
}

String ImageListOutput::convertInt(int num) {
    stringstream strstr;
    strstr << num;
    return strstr.str();
}

vector<int> ImageListOutput::createWriteParams() {
    if (!writeParams.empty()) {
        return writeParams;
    }
    if (fileExtension.find(".png") != String::npos) {
        DBG("Setze Parameter fuer png");
        writeParams.push_back(CV_IMWRITE_PNG_COMPRESSION);
        writeParams.push_back(9);
    } else if (fileExtension.find(".jpg") != String::npos) {
        DBG("Setze Parameter fuer jpg");
        writeParams.push_back(CV_IMWRITE_JPEG_QUALITY);
        writeParams.push_back(99);
    }
    return writeParams;

}

void ImageListOutput::resetFileCounter() {
    counter = 0;
}