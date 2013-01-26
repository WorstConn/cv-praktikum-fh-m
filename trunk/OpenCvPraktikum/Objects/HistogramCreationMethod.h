/* 
 * File:   HistogramCreationMethod.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 17. Januar 2013, 15:06
 */

#ifndef HISTOGRAMCREATIONMETHOD_H
#define	HISTOGRAMCREATIONMETHOD_H
#include "../header.h"
using namespace std;
using namespace cv;
class HistogramCreationMethod {
public:
    HistogramCreationMethod();
    HistogramCreationMethod(const HistogramCreationMethod& orig);
    virtual ~HistogramCreationMethod();
    virtual MatND createHistogram(Mat img, Mat mask)=0;
    
private:

};

#endif	/* HISTOGRAMCREATIONMETHOD_H */

