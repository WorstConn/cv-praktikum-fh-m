/* 
 * File:   MainTest.h
 * Author: Nils Frenking
 *
 * Created on 21. Dezember 2012, 12:07
 */

#ifndef MAINTEST_H
#define	MAINTEST_H

#include "../header.h"

using namespace std;
using namespace cv;

class MainTest : public ATest {
public:
    MainTest();
    MainTest(const MainTest& orig);
    virtual ~MainTest();

    /**
     * F&uuml;hrt einen Test durch.
     * @param args F&uuml;r den Test notwendige Agumente (Dateien, Flags, uva. ...)
     * @return <code>EXIT_SUCCESS</code> wenn der Test ohne Fehler beendet werden konnte. Sonst <code>EXIT_FAILURE</code>.
     */
    virtual int testMain(vector<String> args);
    virtual void putTest(ATest* test);
private:
    vector<ATest*> tests;
};

#endif	/* MAINTEST_H */

