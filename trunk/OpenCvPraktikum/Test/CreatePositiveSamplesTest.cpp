/* 
 * File:   CreatePositiveSamplesTest.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 11. Januar 2013, 00:17
 */

#include "../header.h"
using namespace std;
using namespace cv;

CreatePositiveSamplesTest::CreatePositiveSamplesTest() {

}

CreatePositiveSamplesTest::CreatePositiveSamplesTest(const CreatePositiveSamplesTest& orig) {
}

CreatePositiveSamplesTest::~CreatePositiveSamplesTest() {
}

/**
 * F&uuml;
hrt einen Test durch.
 * @param args F&uuml;
r den Test notwendige Agumente(Dateien, Flags, uva. ...)
 * @return <code>EXIT_SUCCESS< / code> wenn der Test ohne Fehler beendet werden konnte. Sonst <code>EXIT_FAILURE< / code>.
 */
int CreatePositiveSamplesTest::testMain(StringArray args) {
    SampleCreator* creator = SampleCreator::getInstance();
    FourFingersPositveSample posSamp = FourFingersPositveSample();
    creator->setCreationMethod(&posSamp);
    creator->addInputDir("/home/ertai/Videos/FourFingers/POS", "");
//    creator->addInputDir("/home/ertai/Videos/POS2", "/home/ertai/Videos/BG2");
    creator->setOutputPath("/home/ertai/Videos/FourFingers/Result/positives.dat");
    if (creator->createSampleFile()) {
        DBG("Erstellung erfolgreich");
    }


    return EXIT_SUCCESS;
}

void CreatePositiveSamplesTest::printUsage() {
    cout << "No Arguments supported" << endl;
}