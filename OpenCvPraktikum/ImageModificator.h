/*
 * ImageModificator.h
 *
 *  Created on: 17.11.2012
 *      Author: Nils Frenking
 */

#ifndef IMAGEMODIFICATOR_H_
#define IMAGEMODIFICATOR_H_

#include "header.h"
/**
 * Abstrakte Klasse
 */
class ImageModificator {

public:
	ImageModificator();
	virtual ~ImageModificator();
	virtual void modify(cv::Mat*);
};

#endif /* IMAGEMODIFICATOR_H_ */
