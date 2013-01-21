/* 
 * File:   SimpleMaskCreation.h
 * Author: Nils Frenking
 *
 * Created on 18. Januar 2013, 17:34
 */

#ifndef SIMPLEMASKCREATION_H
#define	SIMPLEMASKCREATION_H

#include "../header.h"

using namespace std;
using namespace cv;

class SimpleMaskCreation : public MaskCreationMethod {
public:
    SimpleMaskCreation(Mat& bg);
    SimpleMaskCreation(const SimpleMaskCreation& orig);

    /**
     * Erstellt eine Maske des gegebenen Bildes.
     * @param img Das Eingabebild.
     * @return Die bin&auml;re Maske des Bildes. Interessante bereiche sind mit 1 codiert.
     */
    virtual Mat createMask(Mat& img);

    virtual ~SimpleMaskCreation();
private:
    Mat background;

};

#endif	/* SIMPLEMASKCREATION_H */

