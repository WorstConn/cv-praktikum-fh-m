/*
 * ImageModificator.h
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef IMAGEMODIFICATOR_H_
#define IMAGEMODIFICATOR_H_

#include "../header.h"
using namespace std;
using namespace cv;

class ImageModificator {
public:
    ImageModificator();
    ImageModificator(const ImageModificator&);
    virtual ~ImageModificator();
    virtual void modify(Mat&) = 0;
    virtual float getScale() = 0;
protected:
    CvHelper* helper;
};

#endif /* IMAGEMODIFICATOR_H_ */
