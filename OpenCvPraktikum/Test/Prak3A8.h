/* 
 * File:   Prak3A8.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 21. Dezember 2012, 12:55
 */

#ifndef PRAK3A8_H
#define	PRAK3A8_H
#include "../header.h"

using namespace std;
using namespace cv;

class Prak3A8 : public ATest {
public:
    Prak3A8();
    Prak3A8(const Prak3A8& orig);
    virtual ~Prak3A8();
    /**
     * F&uuml;hrt einen Test durch.
     * @param args F&uuml;r den Test notwendige Agumente (Dateien, Flags, uva. ...)
     * @return <code>EXIT_SUCCESS</code> wenn der Test ohne Fehler beendet werden konnte. Sonst <code>EXIT_FAILURE</code>.
     */
    virtual int testMain(StringArray args);
    void testCB(int pos, void* dat);
    virtual void printUsage();
private:
    int threshold;


};
typedef void (Prak3A8::*tb_callback)(int, void*);

#endif	/* PRAK3A8_H */

