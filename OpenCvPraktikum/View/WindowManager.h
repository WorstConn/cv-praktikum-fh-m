/* 
 * File:   WindowManager.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 28. Dezember 2012, 17:11
 */

#ifndef WINDOWMANAGER_H
#define	WINDOWMANAGER_H
#include "../header.h"
using namespace std;
using namespace cv;

class WindowManager {
public:
    
    WindowManager(const WindowManager& orig);
    virtual ~WindowManager();
    static void putTrackbarCallback(AAction* action, String wndName);
    static WindowManager* getInstance();
    static void callBackFkt(int p, void* data);
    CvWindow* getWindow(String name);
    AAction* getAction(String desc);
    CvWindow* createWindow(String name, int w = 0, int h = 0);
    void showWindow(String name);
    void updateWindowImage(String name, Mat* mat);
    void closeWindow(String name);
    
    virtual void relesase();
private:
    WindowManager();
    static WindowManager* instance;
    static vector<CvWindow*> windows;
    static vector<AAction*> callbacks;
    static mutex* wndMutex;


};

#endif	/* WINDOWMANAGER_H */

