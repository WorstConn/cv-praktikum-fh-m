/* 
 * File:   ImageInput.h
 * Author: Nils Frenking
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
    ImageInput(const ImageInput& orig);
    virtual ~ImageInput();

    virtual Mat getImage() = 0;
    virtual void next() = 0;
    virtual void releaseAll() = 0;
private:

};

#endif	/* IMAGEINPUT_H */

