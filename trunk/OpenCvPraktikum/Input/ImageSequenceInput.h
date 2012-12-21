/* 
 * File:   ImageSequenceInput.h
 * Author: Nils Frenking, Julian Cordes
 *
 * Created on 29. November 2012, 19:04
 */

#ifndef IMAGESEQUENCEINPUT_H
#define	IMAGESEQUENCEINPUT_H

#include "../header.h"

class ImageSequenceInput : public ImageInput {
public:
    ImageSequenceInput();
    ImageSequenceInput(const ImageSequenceInput& orig);
    virtual ~ImageSequenceInput();
    virtual bool reachesEndOfInput()=0;
protected:
    bool reachesEnd;
private:

};

#endif	/* IMAGESEQUENCEINPUT_H */

