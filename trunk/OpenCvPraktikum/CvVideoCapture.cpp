/*
 * CVVideoCapture.cpp
 *
 *  Created on: 17.11.2012
 *      Author: ertai
 */

#include <thread>

#include "header.h"

//#define err(x) std::cout<<x<<std::endl;

CvVideoCapture::CvVideoCapture() {
    capture = NULL;
    writer = NULL;
    startTime = 0;
    scaleToHeight = 0;
    scaleToWidth = 0;
    recordSeconds = 0;
    recording = false;
    frame = cv::Mat();
    fps = 25;
    frames_to_record = 0;


}

CvVideoCapture::CvVideoCapture(ImageInput* in) {
    capture = in;
    writer = NULL;
    startTime = 0;
    scaleToHeight = 0;
    scaleToWidth = 0;
    recordSeconds = 0;
    recording = false;
    frame = cv::Mat();
    fps = 25;
    frames_to_record = 0;


}

CvVideoCapture::CvVideoCapture(const CvVideoCapture& other) {
    capture = NULL;
    writer = NULL;
    startTime = 0;
    scaleToHeight = 0;
    scaleToWidth = 0;
    recordSeconds = 0;
    recording = false;
    frame = cv::Mat();
    fps = 25;
    frames_to_record = 0;


}

CvVideoCapture::~CvVideoCapture() {
    // TODO Auto-generated destructor stub

}

void record();

// TODO: Naja, die ganze Logik eben...

bool CvVideoCapture::start() {
    if (capture != NULL && writer != NULL) {
        if (recording) {
            return false;
        }
       
        return true;
    } else {
        //err("Capture ist NULL");
        return false;
    }


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
        recordSeconds = len;
    } else {
        cerr << "Aufnahmedauer kann nur geaendert werden, wenn keine Aufnahme getstartet wurde." << endl;
    }

}

void CvVideoCapture::setImageModifikator(ImageModificator* mod) {
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
        cv::Mat m = cv::Mat(frame.rows, frame.cols, frame.type());
        frame.copyTo(m);
        /* Lock freigeben*/
        frame_mutex.unlock();
        return m;
    } else {
        return frame;
    }
}

void CvVideoCapture::record() {
     if (recording) {
        return;
    }
    DBG("sds1")
    recording=true;
    
    if (writer == NULL) {
        writer = new cv::VideoWriter(outputname, CV_FOURCC('D','I','V','X'), 30, cv::Size(640, 480), true);

    }
    DBG("sds2")
    if (capture == NULL) {
        //FIXME:
    }
    
    time(&startTime);
    time_t current;
    time(&current);
    int framecount = 0;

    DBG("sds")
    while ((startTime - current) < recordSeconds and framecount < frames_to_record) {
        if (!recording)break;
        DBG("sds")
        time(&current);
        framecount++;
        capture->next();
        Mat frm=capture->getImage();
        setFrame(frm);
        
        if(imageMod!=NULL){
            //frm=getFrame();
            imageMod->modify(&frm);
        }
        writer->write(frm);



    }
    writer->release();
}

void CvVideoCapture::operator()(){
    record();
    //cout<<"Hallo"<<endl;
    
}

void CvVideoCapture::nextFrame() {

    try {
        if (capture == NULL) throw Exception();

        capture->next();
        setFrame(capture->getImage());
    } catch (Exception& ex) {
        cerr << "Fehler: " << ex.what() << endl;
    }
}

void CvVideoCapture::release() {

}

void CvVideoCapture::releaseCapture() {
    if (capture != NULL) {
        capture->releaseAll();

        delete capture;
    } else {
        cerr << "VideoCapture konnte nicht freigegeben werden" << endl;
    }
}

void CvVideoCapture::releaseVideoWriter() {
    if (writer != NULL && !recording) {
        writer->release();
        delete writer;
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

void CvVideoCapture::setInput(ImageInput* in){
    capture=in;
}

void CvVideoCapture::setOutput(std::string out){
    outputname=out;
}

/*
 * http://www.justsoftwaresolutions.co.uk/threading/multithreading-in-c++0x-part-3.html
 * http://de.cppreference.com/w/cpp/thread/mutex
 * Compiler Flag: -std=gnu++0x
 * 
 **/
