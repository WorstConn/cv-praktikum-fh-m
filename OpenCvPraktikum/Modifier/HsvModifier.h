/* 
 * File:   HsvModifier.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 20. Dezember 2012, 11:56
 */

#ifndef HSVMODIFIER_H
#define	HSVMODIFIER_H

#include "../header.h"
using namespace std;
using namespace cv;

class HsvModifier : public ImageModificator {
public:
    HsvModifier();
    HsvModifier(const HsvModifier& orig);
    virtual ~HsvModifier();
    virtual void modify(Mat&);
    virtual float getScale();

};

#endif	/* HSVMODIFIER_H */

