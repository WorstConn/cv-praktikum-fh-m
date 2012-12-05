/*
 * ImageModificator.h
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef IMAGEMODIFICATOR_H_
#define IMAGEMODIFICATOR_H_

#include "header.h"
using namespace std;
using namespace cv;

class ImageModificator {
public:
    ImageModificator();
    ImageModificator(const ImageModificator&);
    virtual ~ImageModificator();
    virtual void modify(Mat&);
    virtual bool doesAction(); // etwas stupide...
};

#endif /* IMAGEMODIFICATOR_H_ */
