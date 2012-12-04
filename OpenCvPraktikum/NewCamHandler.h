/*
 * NewCamHandler.h
 *
 *  Created on: 04.11.2012
 *      Author: Nils Frenking
 */

#ifndef NEWCAMHANDLER_H_
#define NEWCAMHANDLER_H_
#include <cv.h>
#include <highgui.h>
#include "CamHandler.h"
using namespace cv;
class NewCamHandler: public CamHandler {
private:
	Mat currentImage;
	VideoCapture cap;
	virtual bool openDefWebCam();

	virtual bool openDefIpCam();
public:
	NewCamHandler();
	NewCamHandler(const char* camURL);
	virtual ~NewCamHandler();

	virtual bool open();
	virtual bool close();
	virtual bool releaseCapture();
	virtual bool releaseCurrentImage();
	virtual IplImage currentIplImage();
	virtual Mat currentMatImage();
	virtual bool grabNext();
	virtual void dispose();
    
    /*
     * 
     */
    virtual Mat getImage();
    virtual void next();
    virtual void releaseAll();
    virtual bool opened();
    virtual int inputHeight();
    virtual int inputWidth();

};

#endif /* NEWCAMHANDLER_H_ */
