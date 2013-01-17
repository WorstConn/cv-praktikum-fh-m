/* 
 * File:   HistogramCreationMethod.h
 * Author: Nils Frenking
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
private:

};

#endif	/* HISTOGRAMCREATIONMETHOD_H */

