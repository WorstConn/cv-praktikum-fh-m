/* 
 * File:   ImageSequenceInput.h
 * Author: Nils Frenking
 *
 * Created on 29. November 2012, 19:04
 */

#ifndef IMAGESEQUENCEINPUT_H
#define	IMAGESEQUENCEINPUT_H

#include "header.h"


class ImageSequenceInput : public ImageInput{
public:
    ImageSequenceInput();
    ImageSequenceInput(const ImageSequenceInput& orig);
    virtual ~ImageSequenceInput();
    
private:

};

#endif	/* IMAGESEQUENCEINPUT_H */

