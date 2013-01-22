/* 
 * File:   ThumbUpPositiveSample.h
 * Author: Nils Frenking
 *
 * Created on 22. Januar 2013, 00:08
 */

#ifndef THUMBUPPOSITIVESAMPLE_H
#define	THUMBUPPOSITIVESAMPLE_H

#include "../header.h"

using namespace std;
using namespace cv;


class ThumbUpPositiveSample : public CreationBehavior {
public:
    ThumbUpPositiveSample();
    ThumbUpPositiveSample(const ThumbUpPositiveSample& orig);
    virtual ~ThumbUpPositiveSample();
private:

};

#endif	/* THUMBUPPOSITIVESAMPLE_H */

