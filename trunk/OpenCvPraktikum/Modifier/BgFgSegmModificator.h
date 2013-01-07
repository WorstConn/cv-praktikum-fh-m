/* 
 * File:   BgFgSegmModificator.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 3. Januar 2013, 14:50
 */

#ifndef BGFGSEGMMODIFICATOR_H
#define	BGFGSEGMMODIFICATOR_H

#include "../header.h"
using namespace std;
using namespace cv;

/**
 * Modifikator zum entfernen des Hintergrundes aus einem Bild
 * 
 */
class BgFgSegmModificator : public ImageModificator{
public:
    /**
     * Erstellt einen Subtraktor auf Basis eines Vektors von Pfaden zu Bildern, die den Hintergrund darstellen.
     * @param bgImages Vektor von Pfaden zu Bildern, die zu einer Hintergrundmaske Akkumuliert werden.
     */
    BgFgSegmModificator(vector<String> bgImages);
    
    BgFgSegmModificator(const BgFgSegmModificator& orig);
    virtual ~BgFgSegmModificator();
        virtual void modify(Mat&);
    virtual bool doesAction(); // etwas stupide...
    virtual float getScale();
private:
    /**
     */
    BackgroundSubtractorMOG2 bgSubtractor;

};

#endif	/* BGFGSEGMMODIFICATOR_H */

