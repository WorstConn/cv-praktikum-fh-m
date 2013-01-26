/* 
 * File:   MaskCreationMethod.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 17. Januar 2013, 15:07
 */

#ifndef MASKCREATIONMETHOD_H
#define	MASKCREATIONMETHOD_H
#include "../header.h"
using namespace std;
using namespace cv;

class MaskCreationMethod {
public:
    MaskCreationMethod();
    MaskCreationMethod(const MaskCreationMethod& orig);
    /**
     * Erstellt eine Maske des gegebenen Bildes. Unterklassen m&uuml;ssen eventuelles Vorwissen besitzen bzw. spezielle Verfahren anwenden.
     * @param img Das Eingabebild.
     * @return Die bin&auml;re Maske des Bildes. Interessante bereiche sind mit 1 codiert.
     */
    virtual Mat createMask(Mat& img) = 0;
    virtual ~MaskCreationMethod();
private:

};

#endif	/* MASKCREATIONMETHOD_H */

