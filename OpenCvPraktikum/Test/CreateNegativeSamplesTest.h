/* 
 * File:   CreateNegativeSamplesTest.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 10. Januar 2013, 22:30
 */

#ifndef CREATENEGATIVESAMPLESTEST_H
#define	CREATENEGATIVESAMPLESTEST_H
#include "../header.h"
using namespace std;
using namespace cv;

class CreateNegativeSamplesTest : public ATest{
public:
    CreateNegativeSamplesTest();
    CreateNegativeSamplesTest(const CreateNegativeSamplesTest& orig);
    virtual ~CreateNegativeSamplesTest();
        /**
     * F&uuml;hrt einen Test durch.
     * @param args F&uuml;r den Test notwendige Agumente (Dateien, Flags, uva. ...)
     * @return <code>EXIT_SUCCESS</code> wenn der Test ohne Fehler beendet werden konnte. Sonst <code>EXIT_FAILURE</code>.
     */
    virtual int testMain(StringArray args);

    virtual void printUsage();
private:

};

#endif	/* CREATENEGATIVESAMPLESTEST_H */

