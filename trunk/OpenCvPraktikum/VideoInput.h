/* 
 * File:   VideoInput.h
 * Author: Nils Frenking,Julian Cordes
 *
 * Created on 14. Dezember 2012, 20:58
 */

#ifndef VIDEOINPUT_H
#define	VIDEOINPUT_H
#include "header.h"

class VideoInput : public ImageSequenceInput{
public:
    VideoInput();
    VideoInput(const VideoInput& orig);
    virtual ~VideoInput();
private:

};

#endif	/* VIDEOINPUT_H */

