/*
 * CVVideoCapture.cpp
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking
 */

#include <thread>

#include "header.h"


using namespace std;
using namespace cv;
//#define err(x) std::cout<<x<<std::endl;

CvVideoCapture::CvVideoCapture(ImageInput& in) : capture(in) {

    writer = VideoWriter();
    startTime = 0;
    scaleToHeight = 0;
    scaleToWidth = 0;
    recordSeconds = 0;
    recording = false;
    frame = cv::Mat();
    fps = 25;
    frames_to_record = 0;


}

CvVideoCapture::CvVideoCapture(const CvVideoCapture& other) : capture(other.capture) {
    capture = other.capture;
    writer = other.writer;
    startTime = other.startTime;
    imageMod = other.imageMod;
    scaleToHeight = other.scaleToHeight;
    scaleToWidth = other.scaleToWidth;
    recordSeconds = other.recordSeconds;
    recording = other.recording;
    frame = other.frame;
    fps = other.fps;
    frames_to_record = other.frames_to_record;
    outputname = other.outputname;
    recording = other.recording;


}

CvVideoCapture::~CvVideoCapture() {


}



bool CvVideoCapture::start() {
    recthread = new thread(&CvVideoCapture::record, this);
    recthread->join();
    return true;



}

bool CvVideoCapture::stop() {
    recording = false;

    return true;
}

void CvVideoCapture::setScale(int x, int y) {
    if (!recording) {
        scaleToHeight = y;
        scaleToWidth = x;
    } else {
        cerr << "Skalierung kann nur geaendert werden, wenn keine Aufnahme getstartet wurde." << endl;
    }

}

void CvVideoCapture::setRecordingTime(int len) {
    if (!recording) {
        if (len > 0) {
            recordSeconds = len;
        }
    } else {
        cerr << "Aufnahmedauer kann nur geaendert werden, wenn keine Aufnahme getstartet wurde." << endl;
    }

}

void CvVideoCapture::setImageModifikator(ImageModificator& mod) {
    if (!recording) {
        imageMod = mod;
    } else {
        cerr << "Modifikator kann nur geaendert werden, wenn keine Aufnahme getstartet wurde." << endl;
    }
}

bool CvVideoCapture::isRecording() {
    return recording;
}

cv::Mat CvVideoCapture::getFrame() {
    if (recording) {
        /* Lock anfordern*/
        frame_mutex.lock();
        /*Aktuellen Frame Kopieren*/
        Mat m = Mat(frame.rows, frame.cols, frame.type());
        frame.copyTo(m);
        /* Lock freigeben*/
        frame_mutex.unlock();
        return m;
    } else {
        return frame;
    }
}

void CvVideoCapture::record() {

    // <editor-fold defaultstate="collapsed" desc="Vorbedingungen und Fehlerabfrage">
    recording = true;
    if (!capture.opened()) {
        DBG("Capture is not Open... end");
        return;

    }
    if (fps == 0) {
        DBG("FPS is 0 setting to 30");
        fps = 30;
    }
    Size frameSize = Size(capture.inputWidth(), capture.inputHeight());
    if (frameSize.width <= 0 || frameSize.height <= 0) {
        DBG("Error getting framesize");
    } else {
        DBG("Got framesize of input: %d %d", frameSize.width, frameSize.height);
    }
    if (!writer.isOpened()) {
        DBG("Writer is not open");

        writer.open(outputname, CV_FOURCC('D', 'I', 'V', 'X'), fps, Size(640, 480));
        if (writer.isOpened()) {
            DBG("VideoWriter is now open");
        } else {
            DBG("Error opening VideoWriter... end");
            return;
        }

    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Zeit und Framecounter Initialisierung">
    time(&startTime);
    time_t current;
    time(&current);
    int framecount = 0; // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Aufnahme Schleife">
    while (recording) {


        if (frames_to_record != 0 and frames_to_record < framecount) {
            break;
        }
        if (recordSeconds != 0 and ((long int) (current - startTime)) > ((long int) (recordSeconds + 2))) {
            break;
        }



        time(&current);
        framecount++;

        capture.next();
        Mat frm = capture.getImage();
        setFrame(frm);



        if (imageMod.doesAction()) {
            //frm=getFrame();  // Falls es zu 'Concurrent modification error' kommt...
            imageMod.modify(&frm);
        }

        writer.write(frm);



    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Aufräumen...">
    writer.release();
    recording = false;
    startTime = (long int) 0; // </editor-fold>

}

void CvVideoCapture::operator()() {
    record();


}

void CvVideoCapture::nextFrame() {

    try {
        if (!capture.opened()) throw Exception();

        capture.next();
        setFrame(capture.getImage());
    } catch (Exception& ex) {
        cerr << "Fehler: " << ex.what() << endl;
    }
}

void CvVideoCapture::release() {

}

void CvVideoCapture::releaseCapture() {
    if (capture.opened()) {
        capture.releaseAll();


    } else {
        cerr << "VideoCapture konnte nicht freigegeben werden" << endl;
    }
}

void CvVideoCapture::releaseVideoWriter() {
    if (!recording) {
        writer.release();

    } else {
        cerr << "VideoWriter konnte nicht freigegeben werden" << endl;
    }
}

void CvVideoCapture::setFramesToRecord(int frames) {
    if (!recording) {
        frames_to_record = frames;
    } else {
        cerr << "Anzahl der Frames kann nur geaendert werden, wenn keine aufnahme gestartet ist!" << endl;
    }

}

void CvVideoCapture::setFrame(Mat mat) {
    frame_mutex.lock();
    frame = mat;

    frame_mutex.unlock();
}

void CvVideoCapture::setInput(ImageInput& in) {
    capture = in;
}

void CvVideoCapture::setOutput(String out) {
    outputname = out;
}

void CvVideoCapture::setTimeToRecord(int secs) {
    setRecordingTime(secs);
}


// TODO: Zum testen den ImageModifikator ableiten
// TODO: Join nur bei bedarf
// TODO: Test mit Ansichtsfenster ->(Hat sich der Aufwand gelont?)