/*
 * CVVideoCapture.cpp
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#include <thread>

#include "header.h"


using namespace std;
using namespace cv;

CvVideoCapture::CvVideoCapture(ImageSequenceInput& in) : capture(in) {

    writer = NULL;
    startTime = 0;
    scaleFac = 0;
    recordSeconds = 0;
    recording = false;
    frame = Mat();
    fps = 25;
    frames_to_record = 0;
    imageMod = NULL;
    frameDelay = 0;
    window = NULL;

}

CvVideoCapture::CvVideoCapture(const CvVideoCapture& other) : capture(other.capture) {
    capture = other.capture;
    writer = other.writer;
    startTime = other.startTime;
    imageMod = other.imageMod;
    scaleFac = other.scaleFac;
    recordSeconds = other.recordSeconds;
    recording = other.recording;
    frame = other.frame;
    fps = other.fps;
    frames_to_record = other.frames_to_record;
    outputname = other.outputname;
    recording = other.recording;
    frameDelay = other.frameDelay;
    window = other.window;
}

CvVideoCapture::~CvVideoCapture() {


}

bool CvVideoCapture::start() {
    recthread = new thread(&CvVideoCapture::record, this);
    DBG("thread gestartet!");
    return true;



}

void CvVideoCapture::stop() {
    recording = false;
}

void CvVideoCapture::setScale(float scale) {
    if (!recording) {
        scaleFac = scale;
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

void CvVideoCapture::setImageModifikator(ImageModificator *mod) {
    if (!recording) {
        if (mod == NULL) throw Exception();
        imageMod = mod;
    } else {
        cerr << "Modifikator kann nur geaendert werden, wenn keine Aufnahme getstartet wurde." << endl;
    }
}

bool CvVideoCapture::isRecording() {
    return recording;
}

Mat CvVideoCapture::getFrame() {
    if (recording) {
        /* Lock anfordern*/
        frame_mutex.lock();
        /*Aktuellen Frame Kopieren*/
        Mat m = Mat::zeros(frame.size(), frame.type());
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
        fps = capture.inputFps();
    }

    Size frameSize = Size(capture.inputWidth(), capture.inputHeight());
    if (imageMod != NULL) {
        if (imageMod->getScale() != 1.0f) {
            DBG("Modifier skaliert den Frame um %f", imageMod->getScale());
            frameSize.height = static_cast<int> (((float) frameSize.height) * imageMod->getScale());
            frameSize.width = static_cast<int> (((float) frameSize.width) * imageMod->getScale());
        }
    }
    if (frameSize.width <= 0 || frameSize.height <= 0) {
        DBG("Error getting framesize");
    } else {
        DBG("Got framesize of input: %d %d", frameSize.width, frameSize.height);
    }
    if (writer == NULL) {
        DBG("Ausgabe NULL");
        return;
    }
    if (!writer->isOpen()) {
        DBG("Writer is not open");

        try {
            if (writer->open()) {
                DBG("VideoWriter is now open");
            } else {
                DBG("Error opening VideoWriter... end");
                return;
            }

        } catch (Exception& ex) {
            DBG("Fehler: %s\nAusgabe: %s\nFPS: %i\nSize: %i x %i", ex.what(), outputname.c_str(), fps, frameSize.width, frameSize.height);
            return;
        }


    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Zeit und Framecounter Initialisierung">
    time(&startTime);
    time_t lastupd = -1;
    time_t current;
    time(&current);
    int framecount = 0; // </editor-fold>
    if (frames_to_record == 0) {

        frames_to_record = DEFAULT_FRAME_COUNT;

    }
    frameDelay = (int) (1000.0f / ((float) fps));
    DBG("Framedelay = %i", frameDelay);
    if (recordSeconds == 0) {
        recordSeconds = DEFAULT_DURATION;
    }
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

        try {
            capture.next();

        } catch (Exception& ex) {
            DBG("%s", ex.what());
            break;
        }
        if (capture.reachesEndOfInput()) {
            DBG("Input Ende erreicht!");
            break;
        }

        Mat frm = capture.getImage();
        if (imageMod != NULL) {
            //frm=getFrame();  // Falls es zu 'Concurrent modification error' kommt...


            imageMod->modify(frm);

            
        }
        if (window != NULL) {
            if (!window->isShowing()) {
                window->showWindow();
            }
            window->setCurrentImage(&frm);
        }
        setFrame(frm);
        writer->write(frm);

        if (lastupd == -1) {
            time(&lastupd);
        } else if ((((long int) current)-((long int) lastupd)) < frameDelay) {
            this_thread::sleep_for(chrono::milliseconds(frameDelay - (((long int) current)-((long int) lastupd))));

            time(&lastupd);

        }
        frm.release();


    }// </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Aufräumen...">
    writer->close();
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
        cerr << "Fehler: " << ex.msg << endl;
    }
}

void CvVideoCapture::requestNext() {

    try {

        if (!capture.opened()) throw Exception();
        frame_mutex.lock();
        capture.next();
        frame_mutex.unlock();
        setFrame(capture.getImage());

    } catch (Exception& ex) {
        cerr << "Fehler: " << ex.msg << endl;
    }
}

void CvVideoCapture::release() {


    if (recthread != NULL) {
        recording = false;
        if (recthread->joinable()) {
            recthread->join();
        }

    }
    frame.release();
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
        writer->close();

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

void CvVideoCapture::setInput(ImageSequenceInput& in) {
    capture = in;
}

void CvVideoCapture::setTimeToRecord(int secs) {
    setRecordingTime(secs);
}

void CvVideoCapture::joinThread() {
    if (recthread == NULL) {
        DBG("Thread ist NULL");
        return;
    }
    if (!recthread->joinable()) {
        DBG("Thread kann nicht gejoint werden");
        return;
    }
    recthread->join();
}

bool CvVideoCapture::available() {
    return capture.opened();
}

void CvVideoCapture::setOutput(Output* out) {
    if (writer == NULL) {
        writer = out;
        return;
    }
    if (recording) {
        DBG("Bei der Aufnahme!");
        DBG("Warte auf Ende der Aufnahme");
        joinThread();

        writer = out;
        return;
    }

}

void CvVideoCapture::setWindow(CvWindow* wnd) {
    window = wnd;
    window->showWindow();
}

void CvVideoCapture::closeWindow() {
    window->closeWindow();
    window = NULL;
}
