/* 
 * File:   FourFingersPositveSample.h
 * Author: Nils Frenking
 *
 * Created on 22. Januar 2013, 00:25
 */

#ifndef FOURFINGERSPOSITVESAMPLE_H
#define	FOURFINGERSPOSITVESAMPLE_H

#include "../header.h"

using namespace std;
using namespace cv;

class FourFingersPositveSample : public CreationBehavior {
public:
    FourFingersPositveSample();
    FourFingersPositveSample(const FourFingersPositveSample& orig);
    virtual ~FourFingersPositveSample();
private:

};

#endif	/* FOURFINGERSPOSITVESAMPLE_H */

