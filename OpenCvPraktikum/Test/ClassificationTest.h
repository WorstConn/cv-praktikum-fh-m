/* 
 * File:   ClassificationTest.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 27. Januar 2013, 12:56
 */

#ifndef CLASSIFICATIONTEST_H
#define	CLASSIFICATIONTEST_H

#include "../header.h"
using namespace std;
using namespace cv;

class ClassificationTest : public ATest {
public:
    ClassificationTest();
    ClassificationTest(const ClassificationTest& orig);
    virtual ~ClassificationTest();

    /**
     * F&uuml;hrt einen Test durch.
     * @param args F&uuml;r den Test notwendige Agumente (Dateien, Flags, uva. ...)
     * @return <code>EXIT_SUCCESS</code> wenn der Test ohne Fehler beendet werden konnte. Sonst <code>EXIT_FAILURE</code>.
     */
    virtual int testMain(StringArray args);

    virtual void printUsage();

private:
    StringArray cascadeFiles;
    StringArray positivesPaths;
    String negatives;
    vector<int> numPositives;
};

#endif	/* CLASSIFICATIONTEST_H */

