/* 
 * File:   HsvHistogamCreation.h
 * Author: Nils Frenking
 *
 * Created on 21. Januar 2013, 00:11
 */

#ifndef HSVHISTOGAMCREATION_H
#define	HSVHISTOGAMCREATION_H
#include "../header.h"
using namespace std;
using namespace cv;
class HsvHistogamCreation : public HistogramCreationMethod{
public:
    HsvHistogamCreation();
    HsvHistogamCreation(const HsvHistogamCreation& orig);
    virtual ~HsvHistogamCreation();
    virtual MatND createHistogram(Mat img, Mat mask=Mat());
private:

};

#endif	/* HSVHISTOGAMCREATION_H */

