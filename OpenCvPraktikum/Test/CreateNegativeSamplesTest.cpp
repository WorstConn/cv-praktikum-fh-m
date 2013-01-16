/* 
 * File:   CreateNegativeSamplesTest.cpp
 * Author: Nils Frenking
 * 
 * Created on 10. Januar 2013, 22:30
 */

#include "../header.h"
using namespace std;
using namespace cv;

CreateNegativeSamplesTest::CreateNegativeSamplesTest() {
}

CreateNegativeSamplesTest::CreateNegativeSamplesTest(const CreateNegativeSamplesTest& orig) {
}

CreateNegativeSamplesTest::~CreateNegativeSamplesTest() {
}

/**
 * F&uuml;hrt einen Test durch.
 * @param args F&uuml;r den Test notwendige Agumente (Dateien, Flags, uva. ...)
 * @return <code>EXIT_SUCCESS</code> wenn der Test ohne Fehler beendet werden konnte. Sonst <code>EXIT_FAILURE</code>.
 */
int CreateNegativeSamplesTest::testMain(CvStringArray args) {
    SampleCreator* creator = SampleCreator::getInstance();
    NegativeSample negSmp = NegativeSample();
    creator->setCreationMethod(&negSmp);
    creator->addInputDir("TestData/NEG", "");
    creator->setOutputPath("TestData/Result/negs.dat");
    if (creator->createSampleFile()) {
        DBG("Erstellung erfolgreich");
    }


    return EXIT_SUCCESS;
}

void CreateNegativeSamplesTest::printUsage() {
    cout << "No Arguments supported" << endl;
}
