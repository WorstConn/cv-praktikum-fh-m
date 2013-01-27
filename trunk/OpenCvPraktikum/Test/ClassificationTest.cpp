/* 
 * File:   ClassificationTest.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 27. Januar 2013, 12:56
 */

#include "../header.h"
using namespace std;
using namespace cv;

ClassificationTest::ClassificationTest() {
    cascadeFiles = StringArray(6);
    cascadeFiles[0] = CASCADE_BASE_PATH + "fist_cascade.xml";
    cascadeFiles[1] = CASCADE_BASE_PATH + "thumb_cascade.xml";
    cascadeFiles[2] = CASCADE_BASE_PATH + "two_finger_cascade.xml";
    cascadeFiles[3] = CASCADE_BASE_PATH + "three_finger_cascade.xml";
    cascadeFiles[4] = CASCADE_BASE_PATH + "four_finger_cascade.xml";
    cascadeFiles[5] = CASCADE_BASE_PATH + "plain_hand_cascade.xml";
    negatives = SAMPLES_NEGATIVES_PATH;
    positivesPaths = StringArray(6);
    positivesPaths[0] = SAMPLES_BASE_PATH + SAMPLES_FIST_DIR + PATH_SEPARATOR + POSITIVES_SUB_DIR;
    positivesPaths[1] = SAMPLES_BASE_PATH + SAMPLES_THUMB_DIR + PATH_SEPARATOR + POSITIVES_SUB_DIR;
    positivesPaths[2] = SAMPLES_BASE_PATH + SAMPLES_TWO_FINGER_DIR + PATH_SEPARATOR + POSITIVES_SUB_DIR;
    positivesPaths[3] = SAMPLES_BASE_PATH + SAMPLES_THREE_FINGER_DIR + PATH_SEPARATOR + POSITIVES_SUB_DIR;
    positivesPaths[4] = SAMPLES_BASE_PATH + SAMPLES_FOUR_FINGER_DIR + PATH_SEPARATOR + POSITIVES_SUB_DIR;
    positivesPaths[5] = SAMPLES_BASE_PATH + SAMPLES_PLAIN_HAND_DIR + PATH_SEPARATOR + POSITIVES_SUB_DIR;

    numPositives = vector<int>(6);
    numPositives[0] = 273;
    numPositives[1] = 811;
    numPositives[2] = 1145;
    numPositives[3] = 1128;
    numPositives[4] = 1162;
    numPositives[5] = 66;
}

ClassificationTest::ClassificationTest(const ClassificationTest& orig) {
}

ClassificationTest::~ClassificationTest() {
}

/**
 * F&uuml;hrt einen Test durch.
 * @param args F&uuml;r den Test notwendige Agumente (Dateien, Flags, uva. ...)
 * @return <code>EXIT_SUCCESS</code> wenn der Test ohne Fehler beendet werden konnte. Sonst <code>EXIT_FAILURE</code>.
 */
int ClassificationTest::testMain(StringArray args) {
    vector<int> hitsOnPositiveSamples = vector<int>(6);
    vector<int> hitsOnNegativeSamples = vector<int>(6);
    CvHelper* helper = CvHelper::getInstance();
    int numNegatives = 962;
    InputHandler handler;
    RectangleArray currentDetection=RectangleArray();
    for (int i = 2; i < 6; i++) {
        handler = InputHandler();
        handler.setInputSource(INPUT_FOLDER);
        handler.addImageFolder(negatives);
        handler.open();
        CascadeClassifier current;
        current.load(cascadeFiles[i]);
        
        Mat currentImage;
        float percent;
        for (int j = 0; j < numNegatives; j++) {
            handler.next();
            currentImage = handler.getImage();
            currentDetection = helper->detectAll(currentImage, current, 100, 200, 0.0f);
            if(!currentDetection.empty()){
                hitsOnNegativeSamples[i]++;
                percent=(((float)j)/((float)numNegatives))*100.0f;
                DBG("Falsche Erkennung %i bei %3.2f 1/100", hitsOnNegativeSamples[i], percent);
            }
            currentDetection.clear();
        }
        
        handler=InputHandler();
        handler.setInputSource(INPUT_FOLDER);
        handler.addImageFolder(positivesPaths[i]);
        handler.open();
        for(int k = 0; k< numPositives[i];k++){
            handler.next();
            currentImage = handler.getImage();
            currentDetection = helper->detectAll(currentImage, current, 100, 200, 0.0f);
            if(!currentDetection.empty()){
                hitsOnPositiveSamples[i]++;
            }else{
                
                DBG("Nicht erkannt Sample-No: %i", k);
            }
        }
        
        DBG("Objekt-Klassifizierer %i, hat von %i samples %i richtig, und aif %i negativen %i objekte gefunden",i,numPositives[i],hitsOnPositiveSamples[i],numNegatives,hitsOnNegativeSamples[i]);
        


    }
    return EXIT_SUCCESS;
}

void ClassificationTest::printUsage() {
    cout << "No parameters supported" << endl;
}


//  "Objekt-Klassifizierer Faust hat von 273 samples 273 richtig, und auf 962 negativen 150 objekte gefunden" 
//  "Objekt-Klassifizierer 1, hat von 811 samples 742 richtig, und auf 962 negativen 65 objekte gefunden"
//  "Objekt-Klassifizierer 2, hat von 1145 samples 1145 richtig, und auf 962 negativen 253 objekte gefunden"
//  "Objekt-Klassifizierer 3, hat von 1128 samples 1128 richtig, und auf 962 negativen 397 objekte gefunden"
//  "Objekt-Klassifizierer 4, hat von 1162 samples 1145 richtig, und auf 962 negativen 52 objekte gefunden"
//  "Objekt-Klassifizierer 5, hat von 66 samples 43 richtig, und auf 962 negativen 609 objekte gefunden"

