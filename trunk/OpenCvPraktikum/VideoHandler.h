/* 
 * File:   VideoHandler.h
 * Author: Nils Frenking
 *
 * Created on 29. November 2012, 19:27
 */

#ifndef VIDEOHANDLER_H
#define	VIDEOHANDLER_H

#include "header.h"

class VideoHandler : public ImageSequenceInput {
public:
    VideoHandler();
    VideoHandler(const VideoHandler& orig);
    virtual ~VideoHandler();
private:

};

#endif	/* VIDEOHANDLER_H */

