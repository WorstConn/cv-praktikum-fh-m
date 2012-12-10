/*
 * CVVideoCapture.h
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef CVVIDEOCAPTURE_H_
#define CVVIDEOCAPTURE_H_

#include "header.h"


#ifndef __GXX_EXPERIMENTAL_CXX0X__
#define __GXX_EXPERIMENTAL_CXX0X__
#endif



using namespace std;
using namespace cv;



class CvVideoCapture {
private:

    /**
     * Der Video-Writer;
     */
    VideoWriter writer;

    /**
     * Webcam Capture
     */
    ImageInput& capture;
    /**
     * Ausgabedateiname
     */
    String outputname;

    /**
     * Falls > 0 , wird das Bild skaliert
     */
    float scaleFac;
    /**
     * Dauer der Aufnahme
     */
    int recordSeconds;

    /**
     * Aufnahmestatus
     */
    bool recording;

    /**
     * Startzeit der Aufnahme (in Sekunden seit 1. Januar, 1970)
     */
    time_t startTime;

    /**
     * Fps der Ausgabedatei
     */
    int fps;

    /**
     * Anzahl an Bildern, die das Video beinhalten soll
     * kann alternativ zu, oder in Kombination mit der oben genannten Angabe
     * der Sekunden genutzt werden. (-> was zuerst eintritt)
     */
    int frames_to_record;

    /**
     * Erleichtert das vor-verarbeiten (beliebige Operation) der Videoframes
     * Vorstellbar sind Graustufen-Bilder,
     */
    ImageModificator *imageMod;

    /**
     * Aktueller Videoframe
     */
    Mat frame;

    /**
     * Ein Mutex-Lock fuer die Schreib und lesevorgaenge des Frames;
     */
    mutex frame_mutex;

    Size videoCaptureSize;

    thread *recthread;



    void releaseVideoWriter();

    void releaseCapture();

    void nextFrame();

    void setFrame(Mat mat);



public:
   

    CvVideoCapture(ImageInput& in);

    CvVideoCapture(const CvVideoCapture&);

    virtual ~CvVideoCapture();
    /**
     * Startet die aufnahme
     */
    bool start();
    /**
     * Stoppt die Aufnahme
     */
    bool stop();
    /**
     * Setzt die Skalierung des Videos
     */
    void setScale(float);
    /**
     * Setzt die Zeit die die Aufnahme dauern soll
     */
    void setRecordingTime(int);

    /**
     * Setzt einen Modifizierer der jeden Frame bearbeitet
     */
    void setImageModifikator(ImageModificator *mod);

    bool isRecording();

    Mat getFrame();

    void record();

    void operator()();

    void setFramesToRecord(int frames);
    
    void release();

    void setInput(ImageInput& in);

    void setOutput(String out);
    
    void setTimeToRecord(int secs);

    void joinThread();
    

};

#endif /* CVVIDEOCAPTURE_H_ */
