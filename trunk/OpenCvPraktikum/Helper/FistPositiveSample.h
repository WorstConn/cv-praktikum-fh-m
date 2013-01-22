/* 
 * File:   FistPositiveSample.h
 * Author: Nils Frenking
 *
 * Created on 21. Januar 2013, 23:34
 */

#ifndef FISTPOSITIVESAMPLE_H
#define	FISTPOSITIVESAMPLE_H

#include "../header.h"

using namespace std;
using namespace cv;

class FistPositiveSample : public CreationBehavior {
public:
    FistPositiveSample();
    FistPositiveSample(const FistPositiveSample& orig);
    virtual ~FistPositiveSample();
private:

};

#endif	/* FISTPOSITIVESAMPLE_H */

