/*
 * CamHandler.h
 *
 *  Created on: 04.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef NEWCAMHANDLER_H_
#define NEWCAMHANDLER_H_
#include <cv.h>
#include <highgui.h>
#include "ACamHandler.h"
using namespace cv;

class CamHandler : public ACamHandler {
private:
    Mat currentImage;
    VideoCapture cap;
    virtual bool openDefWebCam();

    virtual bool openDefIpCam();

    INPUT_FORMAT currentDimToInputFormat();
    Point2i formatToDimension(INPUT_FORMAT fmt);
public:
    CamHandler();
    CamHandler(const char* camURL);
    virtual ~CamHandler();


    virtual bool open();

    virtual bool close();
    virtual bool releaseCapture();
    virtual bool releaseCurrentImage();
    virtual IplImage currentIplImage();
    virtual Mat currentMatImage();
    virtual bool grabNext();
    virtual void dispose();


    /*
     * Funktionen der Basisklasse
     * 
     */

    /**
     * Gibt das Aktuelle Bild zur&uuml;ck
     * @return das Bild
     */
    virtual Mat getImage();

    /**
     * Holt das n&auml;chste Bild
     */
    virtual void next();
    /**
     * Gibt alles Frei
     */
    virtual void releaseAll();
    /**
     * Ist die Kamera bereit
     * @return true, wenn die Kamera initialisiert wurde
     */
    virtual bool opened();
    /**
     * Bildh&ouml;he des Kamerabildes
     * @return die h&ouml;he in PX
     */
    virtual int inputHeight();

    /**
     * Bildbreite des Kamerabildes
     * @return die h&ouml;he in PX
     */
    virtual int inputWidth();

    /**
     * Fps der Kamera
     * @return die FPS
     */
    virtual int inputFps();

    /**
     * Gibt an, ob das Kamerabild zu RGB umgewandelt werden sollte.
     *
     */
    virtual bool shouldConvertToRGB();


    /**
     * Versucht eine Andere Bildgr&ouml;&szlig;e von der Kamera anzufordern.
     * @param newResolution Die Aufl&ouml;sung, die von der Kamera angefordert wird.
     * @return <code>true</code>, wenn die &Auml;nderung angenommen wurden, sonst <code>false</code>.
     */
    virtual bool requestFormat(INPUT_FORMAT fmt);

    /**
     * Gibt die aktuelle <code>RESOLUTION</code> des Kamerabildes zur&uuml;ck.
     * @return die aktuelle <code>RESOLUTION</code>.
     */
    virtual INPUT_FORMAT currentCamInputFormat();

};

#endif /* NEWCAMHANDLER_H_ */
