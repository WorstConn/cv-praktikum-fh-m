/* 
 * File:   ImageInput.h
 * Author: Nils Frenking, Julian Cordes
 *
 * Created on 29. November 2012, 18:57
 */

#ifndef IMAGEINPUT_H
#define	IMAGEINPUT_H

#include "header.h"

using namespace std;
using namespace cv;

class ImageInput {
public:
    ImageInput();
    ImageInput(const ImageInput&);
    virtual ~ImageInput();

    virtual Mat getImage() = 0;
    virtual void next() = 0;
    virtual void releaseAll() = 0;
    virtual bool opened() = 0;
    virtual int inputHeight() = 0;
    virtual int inputWidth() = 0;
    virtual int inputFps()=0;
    virtual bool shouldConvertToRGB()=0;
private:

};

#endif	/* IMAGEINPUT_H */

