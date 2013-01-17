/* 
 * File:   KeyPointCreationMethod.h
 * Author: Nils Frenking
 *
 * Created on 17. Januar 2013, 15:54
 */

#ifndef KEYPOINTCREATIONMETHOD_H
#define	KEYPOINTCREATIONMETHOD_H
#include "../header.h"
using namespace std;
using namespace cv;

class KeyPointCreationMethod {
public:
    KeyPointCreationMethod();
    KeyPointCreationMethod(const KeyPointCreationMethod& orig);
    virtual ~KeyPointCreationMethod();
private:

};

#endif	/* KEYPOINTCREATIONMETHOD_H */

