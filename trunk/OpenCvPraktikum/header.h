/*
 * header.h
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking
 */

#ifndef HEADER_H_
#define HEADER_H_

#include <thread>
#include <mutex>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <opencv.hpp>
#include <cvaux.hpp>
#include <cv.hpp>
#include <cxcore.hpp>
#include <pthread.h>
#include <highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

#ifdef __unix__

#ifdef DEBUG
#define DBG(X) printf("DBG: %s %d %s\n", X,__LINE__,(char*)__func__);
#define DBG4(X,Y,Z,W) std::cout<<"DBG: "<< X << " " << Y << " " << Z<< " " << W << " " <<__LINE__<< " " <<(char*)__func__<<std::endl;
#define DBG3(X,Y,Z) std::cout<<"DBG: "<< X << " " << Y << " " << Z<< " " <<__LINE__<< " " <<(char*)__func__<<std::endl;
#define DBG2(X,Y) std::cout<<"DBG: "<< X << " " << Y << " " <<__LINE__<< " " <<(char*)__func__<<std::endl;
#else
#define DBG(X) do {} while(0);
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


#include "ImageInput.h"
#include "ImageSequenceInput.h"
#include "VideoHandler.h"
#include "CamHandler.h"
#include "ImageModificator.h"
#include "NopImageModificator.h"
#include "CvVideoCapture.h"


#include "CvHelper.h"

#include "MyMath.h"
#include "NewCamHandler.h"
#include "FileManager.h"



#endif /* HEADER_H_ */
