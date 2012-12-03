/*
 * NopImageModificator.h
 *
 *  Created on: 17.11.2012
 *      Author: ertai
 */

#ifndef NOPIMAGEMODIFICATOR_H_
#define NOPIMAGEMODIFICATOR_H_
#include "header.h"
class NopImageModificator : public ImageModificator{
public:
	NopImageModificator();
	virtual ~NopImageModificator();
	void modify(IplImage*);
	void modify(cv::Mat*);
};

#endif /* NOPIMAGEMODIFICATOR_H_ */
