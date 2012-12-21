/* 
 * File:   VideoOutput.h
 * Author: Nils Frenking
 *
 * Created on 19. Dezember 2012, 23:32
 */

#ifndef VIDEOOUTPUT_H
#define	VIDEOOUTPUT_H

#include "../header.h"

class VideoOutput : public Output {
public:
    VideoOutput(String path, String name, int fps = 25, int codec = CODEC_DEFAULT, String fileExt = PREF_VIDEO_OUTPUT_FILE_EXT);
    VideoOutput(const VideoOutput& orig);
    virtual ~VideoOutput();
    virtual bool open();
    virtual void write(Mat&);
    virtual void close();
private:
    int CODEC;
    int framesPerSecond;
    VideoWriter writer;



};

#endif	/* VIDEOOUTPUT_H */

