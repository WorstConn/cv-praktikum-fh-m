/*
 * header.h
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef HEADER_H_
#define HEADER_H_


// <editor-fold defaultstate="collapsed" desc="             Enums">

/**
 * Indikator des Eingabeformats.
 */
enum INPUT_FORMAT {
    rNULL, rUnknown, r480p, r720p, r1080p
};

/**
 * Indikator des Eingabetyps.
 */
enum INPUT_TYPE {
    INPUT_NONE, INPUT_VIDEO, INPUT_CAM, INPUT_IP_CAM, INPUT_FOLDER
};

enum POSITION_HISTOGRAM_DIRECTION {
    DIRECTION_X, DIRECTION_Y
};

/**
 * Indikator des Ausgabetyps.
 */
enum OUTPUT_TYPE {
    OUTPUT_VIDEO, OUTPUT_FOLDER
}; // </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Defintionen">

/**
 * Ein paar Defaults.
 */
#define CODEC_DEFAULT CV_FOURCC('D','I','V','X')
#define PREF_VIDEO_OUTPUT_FILE_EXT ".avi"
#define PREF_IMAGE_OUTPUT_FILE_EXT ".png"


#ifdef TRY_KINECT
#include <libfreenect.h>
#include <libfreenect_sync.h>
#include <libfreenect.hpp>
#include <cmath>
#include <pthread.h>
#endif




/**
 * Ausgabedefinition
 */
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

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             System Header">
/**
 * System Header
 */
#include <algorithm>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             OpenCV Header">
/**
 * OpenCV Header
 */
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

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Typendefinitionen">
typedef std::vector<std::vector<cv::Point> > PointHistogram;
typedef std::vector<cv::Point> PointArray;
typedef std::vector<bool> BooleanArray;
typedef std::vector<cv::String> CvStringArray;
typedef std::set<cv::String> CvStringSet;
typedef std::vector<cv::Mat> CvImageArray;
typedef std::vector<CvStringArray> CvArrayOfStringArrays;
typedef std::map<int, cv::String> CvImageTypeMap;
typedef std::vector<cv::DMatch> CvMatchesArray;
typedef std::vector<cv::KeyPoint> CvKeyPointArray;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             OS spezifische Includes">
/**OS spezifische Includes*/
#ifdef __unix__
/**
 * Pfad-Separator
 */
#define PATH_SEPARATOR "/"

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
#else
#define PATH_SEPARATOR "\\"
#endif

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Hilfsklassen">

#include "Helper/MyMath.h"
#include "Helper/FileManager.h"
#include "Helper/CvHelper.h"
#include "Helper/CreationBehavior.h"
#include "Helper/NegativeSample.h"
#include "Helper/PlainHandPositiveSample.h"
#include "Helper/SampleCreator.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Modifikatoren">
/**
 * Die Modifikatoren
 */
#include "Modifier/ImageModificator.h"
#include "Modifier/ModificatorComponent.h"
#include "Modifier/CompositeModificator.h"
#include "Modifier/ScaleModificator.h"
#include "Modifier/HsvModifier.h"
#include "Modifier/BgFgSegmModificator.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Ausgabe">
/**
 * Ausgabe
 */
#include "Output/Output.h"
#include "Output/VideoOutput.h"
#include "Output/ImageListOutput.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Eingabe">
/**
 * Eingabe
 */
#include "Input/ImageInput.h"
#include "Input/ImageSequenceInput.h"
#include "Input/AInputHandler.h"
#include "Input/InputHandler.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Formatumwandlung und Bildverarbeitung">
/*
 * Formatumwandlung und Bildverarbeitung
 */
#include "CvVideoCapture.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Anzeige">
/**
 * Anzeige
 */
#include "View/AAction.h"
#include "View/AImageAction.h"
#include "View/ModificatorAction.h"
#include "View/CvWindow.h"
#include "View/WindowManager.h"
#include "Control/RecorderCtl.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Test">

#include "Test/ATest.h"
#include "Test/VideoInputToImageSequenceOutputTest.h"
#include "Test/CreateNegativeSamplesTest.h"
#include "Test/CreatePositiveSamplesTest.h"
#include "Test/Prak3A8.h"
#include "Test/WindowManagerTest.h"
#include "Test/MainTest.h"


// </editor-fold>

#endif /* HEADER_H_ */
