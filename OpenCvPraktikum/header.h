/*
 * header.h
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef HEADER_H_
#define HEADER_H_


// <editor-fold defaultstate="collapsed" desc="             Defintionen">

/**
 * Ein paar Defaults.
 */
#define CODEC_DEFAULT CV_FOURCC('D','I','V','X')
#define PREF_VIDEO_OUTPUT_FILE_EXT ".avi"
#define PREF_IMAGE_OUTPUT_FILE_EXT ".png"

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

/**
 * Indikator des Ausgabetyps.
 */
enum OUTPUT_TYPE {
    OUTPUT_VIDEO, OUTPUT_FOLDER
};


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
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
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

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Modifikatoren">
/**
 * Die Modifikatoren
 */
#include "Modifier/ImageModificator.h"
#include "Modifier/CompositeModificator.h"
#include "Modifier/ScaleModificator.h"
#include "Modifier/HsvModifier.h"

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
#include "View/TrackbarData.h"
#include "View/Window.h"

#include "Control/RecorderCtl.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="             Test">

#include "Test/ATest.h"
#include "Test/MainTest.h"
#include "Test/Prak3A8.h"

// </editor-fold>

#endif /* HEADER_H_ */
