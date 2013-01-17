/* 
 * File:   MaskCreationMethod.h
 * Author: Nils Frenking
 *
 * Created on 17. Januar 2013, 15:07
 */

#ifndef MASKCREATIONMETHOD_H
#define	MASKCREATIONMETHOD_H
#include "../header.h"
using namespace std;
using namespace cv;
class MaskCreationMethod {
public:
    MaskCreationMethod();
    MaskCreationMethod(const MaskCreationMethod& orig);
    virtual ~MaskCreationMethod();
private:

};

#endif	/* MASKCREATIONMETHOD_H */

