/* 
 * File:   RecorderCtl.h
 * Author: Nils Frenking, Julian Cordes
 *
 * Created on 14. Dezember 2012, 17:01
 */

#ifndef RECORDERCTL_H
#define	RECORDERCTL_H
#include "../header.h"
using namespace std;
using namespace cv;

enum REC_CTL_STATE {
    INIT, GRAB, RECORD, DELETED
};



class RecorderCtl {
public:

    RecorderCtl(String ctlName = "Default");
    RecorderCtl(const RecorderCtl& orig);
    virtual ~RecorderCtl();

    bool refreshWindowImage(Mat img);
    void dispose();
    void setWindow(Window *wnd);
    void setCapture(CvVideoCapture *capture);
    void createCapture(ImageInput& in);
    void startGrabInput();
    void startRecording();
    void stopRecording();
    void stopGrabbing();
    CvVideoCapture* getCapture();
    Window* getWindow();



    void grabLoop();
    void recordLoop();
private:
    REC_CTL_STATE state;
    String name;
    Window* wnd;
    CvVideoCapture* capture;
    thread* ctlThread;


};

#endif	/* RECORDERCTL_H */

