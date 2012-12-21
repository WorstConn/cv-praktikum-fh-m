/* 
 * File:   VideoOutput.cpp
 * Author: Nils Frenking
 * 
 * Created on 19. Dezember 2012, 23:32
 */

#include "../header.h"

VideoOutput::VideoOutput(String p, String n, int fps, int codec, String fileExt) : Output(p, n, fileExt) {
    framesPerSecond = fps;
    CODEC = codec;
    writer = VideoWriter();

}

VideoOutput::VideoOutput(const VideoOutput& orig) : Output(orig) {
    framesPerSecond = orig.framesPerSecond;
    CODEC = orig.CODEC;
    writer = orig.writer;
}

VideoOutput::~VideoOutput() {

}

bool VideoOutput::open() {
    try {
        writer.open(getFullPath(), CODEC, static_cast<double> (framesPerSecond), outputSize, true);
    } catch (Exception& ex) {
        DBG("Fehler: %s\nFPS: %i\nOutput: %s", ex.what(), framesPerSecond, getFullPath().c_str());
    }
    opened = writer.isOpened();
    return opened;
}

void VideoOutput::write(Mat& img) {
    if (!opened) {
        DBG("Ausgabe nicht offen! Ende!");
        return;
    }
    try {
        writer.write(img);

    } catch (Exception& ex) {
        DBG("Fehler: %s\nFPS: %i\nOutput: %s", ex.what(), framesPerSecond, getFullPath().c_str());
    }


}

void VideoOutput::close() {
    if (opened) {
        writer.release();
        return;
    }
    DBG("Video-Ausgabe nicht offen");

}

