/* 
 * File:   ScaleModificator.h
 * Author: Nils Frenking, Julian Cordes
 *
 * Created on 5. Dezember 2012, 01:04
 */

#ifndef SCALEMODIFICATOR_H
#define	SCALEMODIFICATOR_H


#include "../header.h"
using namespace std;
using namespace cv;

class ScaleModificator : public ImageModificator {
public:
    ScaleModificator();
    ScaleModificator(const ScaleModificator& orig);
    virtual ~ScaleModificator();
    virtual void modify(Mat& img);
    virtual float getScale();
private:

};

#endif	/* SCALEMODIFICATOR_H */

