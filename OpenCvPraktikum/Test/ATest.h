/* 
 * File:   ATest.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 21. Dezember 2012, 00:02
 */

#ifndef ATEST_H
#define	ATEST_H
#include "../header.h"
using namespace std;
using namespace cv;

class ATest {
public:
    ATest();
    ATest(const ATest& orig);
    virtual ~ATest();
    /**
     * F&uuml;hrt einen Test durch.
     * @param args F&uuml;r den Test notwendige Agumente (Dateien, Flags, uva. ...)
     * @return <code>EXIT_SUCCESS</code> wenn der Test ohne Fehler beendet werden konnte. Sonst <code>EXIT_FAILURE</code>.
     */
    virtual int testMain(vector<String> args) = 0;
private:


};

#endif	/* ATEST_H */

