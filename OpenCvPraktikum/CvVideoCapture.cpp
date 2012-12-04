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


    //capture=(in);
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
    scaleToHeight = other.scaleToHeight;

    scaleToWidth = other.scaleToWidth;
    recordSeconds = other.recordSeconds;
    recording = other.recording;
    frame = other.frame;
    fps = other.fps;
    frames_to_record = other.frames_to_record;
    outputname = other.outputname;


}

CvVideoCapture::~CvVideoCapture() {
    // TODO Auto-generated destructor stub

}

void record();

// TODO: Naja, die ganze Logik eben...

bool CvVideoCapture::start() {

//    if (recording) {
//        return false;
//    }
    recthread = new std::thread(&CvVideoCapture::record, this);
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
        recordSeconds = len;
    } else {
        cerr << "Aufnahmedauer kann nur geaendert werden, wenn keine Aufnahme getstartet wurde." << endl;
    }

}

void CvVideoCapture::setImageModifikator(ImageModificator mod) {
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

    DBG("Record");
    //    if (recording || false) {
    //        return;
    //    }

    recording = true;

    if (!capture.opened()) {
        DBG("Capture is not Open");
    }
    Mat frame;
    if (fps == 0) {
        DBG("FPS is 0 setting to 30");
        fps = 30;
    }
    capture.next();


    frame = capture.getImage(); // get first frame for size

    if (frame.data != NULL) {
        DBG("Got first frame");
        DBG3("Frame size is", frame.cols, frame.rows);
    } else {
        DBG("Error getting first frame");
    }

    if (!writer.isOpened()) {
        DBG("Writer is not Open");
        DBG2("Video Outputname: ", outputname);
        writer.open(outputname, CV_FOURCC('D', 'I', 'V', 'X'), fps, Size(640, 480));
        if (writer.isOpened()) {
            DBG("VideoWriter is not open");
        } else {
            DBG("Error opening VideoWriter... end");
            return;
        }
        //writer.open(outputname, CV_FOURCC('D', 'I', 'V', 'X'), fps, frame.size(), true);
    }



    time(&startTime);
    time_t current;
    time(&current);
    int framecount = 0;


    while (/*(startTime - current) < recordSeconds and*/ framecount < frames_to_record) {
        // if (!recording)break;

        //time(&current);
        framecount++;
        printf("%d %d\n", framecount, frames_to_record);

        capture.next();

        Mat frm = capture.getImage();

        setFrame(frm);


        /*
        if(imageMod!=NULL){
            //frm=getFrame();
            imageMod->modify(&frm);
        }*/

        writer.write(frm);



    }
    writer.release();
}

void CvVideoCapture::operator()() {
    record();
    //cout<<"Hallo"<<endl;

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

/*
 * http://www.justsoftwaresolutions.co.uk/threading/multithreading-in-c++0x-part-3.html
 * http://de.cppreference.com/w/cpp/thread/mutex
 * Compiler Flag: -std=gnu++0x
 * 
 **/
