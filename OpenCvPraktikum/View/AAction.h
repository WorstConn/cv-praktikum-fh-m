/* 
 * File:   AAction.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 4. Januar 2013, 13:48
 */

#ifndef ACTION_H
#define	ACTION_H
#include "../header.h"

using namespace std;
using namespace cv;

class AAction {
public:
    AAction(String wN, String aN, int maxval, int minval = 0);

    AAction(const AAction& orig);
    virtual ~AAction();
    virtual void action(int pos, void* data) = 0;
    virtual String getActionDesc();
    virtual String getWindowName();
    virtual int getMax();
    virtual int getMin();
    virtual void setActionDesc(String ad);
    virtual void setWindowName(String wn);
    virtual int* posPtr();

private:
    String wndName;
    String actionName;
    int lastPos;
    int maxVal;
    int minVal;

};

#endif	/* ACTION_H */

