/* 
 * File:   WindowManagerTest.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 6. Januar 2013, 14:04
 */

#ifndef WINDOWMANAGERTEST_H
#define	WINDOWMANAGERTEST_H

#include "../header.h"

using namespace std;
using namespace cv;

class WindowManagerTest : public ATest, public AImageAction{
public:
    WindowManagerTest();
    WindowManagerTest(const WindowManagerTest& orig);
    virtual ~WindowManagerTest();
    virtual void action(int pos, void* data);
    virtual int testMain(StringArray args);
    virtual void printUsage();
private:
    WindowManager *manager;
    Mat *currentFrame;

};

#endif	/* WINDOWMANAGERTEST_H */

