/* 
 * File:   VideoInputToImageSequenceOutputTest.h
 * Author: Nils Frenking
 *
 * Created on 10. Januar 2013, 21:50
 */

#ifndef VIDEOINPUTTOIMAGESEQUENCEOUTPUTTEST_H
#define	VIDEOINPUTTOIMAGESEQUENCEOUTPUTTEST_H

#include "../header.h"

using namespace std;
using namespace cv;

class VideoInputToImageSequenceOutputTest : public ATest {
public:
    VideoInputToImageSequenceOutputTest();
    VideoInputToImageSequenceOutputTest(const VideoInputToImageSequenceOutputTest& orig);
    virtual ~VideoInputToImageSequenceOutputTest();
    virtual int testMain(StringArray args);
    virtual void printUsage();
private:
    String inputFile;
    bool useCam;
    String outputPath;
    bool valid;
    void parseInput(StringArray args);

};

#endif	/* VIDEOINPUTTOIMAGESEQUENCEOUTPUTTEST_H */

