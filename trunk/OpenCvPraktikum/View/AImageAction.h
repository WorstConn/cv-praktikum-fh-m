/* 
 * File:   AImageAction.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 6. Januar 2013, 11:36
 */

#ifndef AIMAGEACTION_H
#define	AIMAGEACTION_H

#include "../header.h"

using namespace std;

class AImageAction : public AAction {
public:
    AImageAction(String wN, String aN, int maxval, int minval = 0);
    AImageAction(const AImageAction& orig);
    virtual ~AImageAction();
    virtual void updateImage(Mat* img);
    virtual void clearImage();
protected:
    Mat* img;
private:

};

#endif	/* AIMAGEACTION_H */

