/* 
 * File:   ContourCreationMethod.h
 * Author: Nils Frenking
 *
 * Created on 17. Januar 2013, 15:52
 */

#ifndef CONTOURCREATIONMETHOD_H
#define	CONTOURCREATIONMETHOD_H
#include "../header.h"
using namespace std;
using namespace cv;

class ContourCreationMethod {
public:
    ContourCreationMethod();
    ContourCreationMethod(const ContourCreationMethod& orig);
    virtual ~ContourCreationMethod();
    virtual PointArray createContour(Mat inputImg, int maxObjects, bool isColorImage)=0;
private:

};

#endif	/* CONTOURCREATIONMETHOD_H */

//FIXME: Implementieren.