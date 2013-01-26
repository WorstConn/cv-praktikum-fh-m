/* 
 * File:   VideoInputToImageSequenceOutputTest.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 10. Januar 2013, 21:50
 */

#include "../header.h"

using namespace std;
using namespace cv;

VideoInputToImageSequenceOutputTest::VideoInputToImageSequenceOutputTest() {
}

VideoInputToImageSequenceOutputTest::VideoInputToImageSequenceOutputTest(const VideoInputToImageSequenceOutputTest& orig) {
}

VideoInputToImageSequenceOutputTest::~VideoInputToImageSequenceOutputTest() {
}

int VideoInputToImageSequenceOutputTest::testMain(StringArray args) {
    if (args.size() < 3) {
        cout << "Nicht ausreichend Argumente" << endl;
        printUsage();
        cout << "Nehme Hardgecodete Pfade an" << endl;
        inputFile = "/home/ertai/Videos/VIDEO0024.mp4";
        outputPath = "/home/ertai/Videos/Negs2";
        useCam = false;
        valid = true;
    } else {
        parseInput(args);
    }
    if (!valid) {
        printUsage();
        return EXIT_FAILURE;
    }
    InputHandler handler = InputHandler();
    handler.setInputSource(INPUT_VIDEO);
    handler.addVideo(inputFile);
    if (!handler.open()) {
        DBG("Konnte Eingabe nicht öffnen");
        return EXIT_FAILURE;
    }
    CvVideoCapture* cap = new CvVideoCapture(handler);
    Output* out = new ImageListOutput(outputPath, "img-", ".png");

    cap->setOutput(out);
    cap->setTimeToRecord(10240);
    cap->setRecordingTime(150000);
    cap->start();

    cap->joinThread();
    return EXIT_SUCCESS;
}

void VideoInputToImageSequenceOutputTest::printUsage() {
    cout << "Valid Arguments" << endl << " -c    Input from cam" << endl << " -v [PATH]    Input from Video found at PATH" << endl << "-o [OUTPUTDIR]     Directory, where the videoframes are written. " << endl;
}

void VideoInputToImageSequenceOutputTest::parseInput(StringArray args) {
    StringArray::iterator iter;
    valid = false;
    bool gotOut = false;
    bool gotIn = false;
    for (iter = args.begin(); iter != args.end(); iter++) {
        if ((*iter).find("-o") == 0) {
            outputPath = (*(iter + 1));
            gotOut = true;
            iter++;
            if (gotIn && gotOut) {
                valid = true;
                break;
            }
        } else
            if ((*iter).find("-c") == 0) {
            useCam = true;
            gotIn = true;
            if (gotIn && gotOut) {
                valid = true;
                break;
            }
        } else
            if ((*iter).find("-v") == 0) {
            inputFile = (*(iter + 1));
            useCam = false;
            gotIn = true;
            iter++;
            if (gotIn && gotOut) {
                valid = true;
                break;
            }
        }

    }
}