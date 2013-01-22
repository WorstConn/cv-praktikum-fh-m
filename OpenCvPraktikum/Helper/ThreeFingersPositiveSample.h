/* 
 * File:   ThreeFingersPositiveSample.h
 * Author: Nils Frenking
 *
 * Created on 22. Januar 2013, 00:24
 */

#ifndef THREEFINGERSPOSITIVESAMPLE_H
#define	THREEFINGERSPOSITIVESAMPLE_H

#include "../header.h"

using namespace std;
using namespace cv;


class ThreeFingersPositiveSample : public CreationBehavior{
public:
    ThreeFingersPositiveSample();
    ThreeFingersPositiveSample(const ThreeFingersPositiveSample& orig);
    virtual ~ThreeFingersPositiveSample();
private:

};

#endif	/* THREEFINGERSPOSITIVESAMPLE_H */

