/*
 * header.h
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef HEADER_H_
#define HEADER_H_


#define CODEC_DEFAULT CV_FOURCC('D','I','V','X')
#include <algorithm>
#include <stdio.h>

#include <thread>
#include <mutex>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "calib3d/calib3d.hpp"

#include <opencv.hpp>
#include <cvaux.hpp>
#include <cv.hpp>



#include <cxcore.hpp>
#include <pthread.h>
#include <highgui/highgui.hpp>
#include <gpu/gpu.hpp>
#include <gpu/gpumat.hpp>

#include <opencv2/video/video.hpp>


#ifdef __unix__

#ifdef DEBUG
#define DBG(format, ...) do {\
        printf("DBG: \"");\
        printf(format, ##__VA_ARGS__);\
        printf("\" line: %d function: %s\n", __LINE__,(char*) __func__);} while(0);
#define DBG_EXIT(format, ...) do {\
        DBG(format, ##__VA_ARGS__)\
        exit(EXIT_FAILURE);} while(0);
#else
#define DBG(format, ...) do {} while(0);
#define DBG_EXIT(format, ...) do {} while(0);
#endif




#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <valarray>
#define MAXPATHLEN 500

struct inode_struct {
    struct inode_struct *next;
    int inode;
    char* filename;
};

typedef struct inode_struct Inode;

#endif
#include "ImageModificator.h"
#include "ScaleModificator.h"

#include "ImageInput.h"
#include "ImageSequenceInput.h"
#include "AInputHandler.h"
#include "InputHandler.h"




#include "CvVideoCapture.h"
#include "CvHelper.h"
#include "View/Window.h"
#include "Control/RecorderCtl.h"



#include "MyMath.h"

#include "FileManager.h"



#endif /* HEADER_H_ */
