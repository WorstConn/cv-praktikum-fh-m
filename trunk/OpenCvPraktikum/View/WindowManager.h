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
    WindowManager();
    WindowManager(const WindowManager& orig);
    virtual ~WindowManager();
    static void putTrackbarCallback(AAction* action, String wndName);
    static WindowManager* getInstance();
    static void callBackFkt(int p, void* data);
    Window* getWindow(String name);
    AAction* getAction(String desc);
    Window* createWindow(String name, int w = 0, int h = 0);
private:
    static WindowManager* instance;
    static vector<Window*> windows;
    static vector<AAction*> callbacks;
    


};

#endif	/* WINDOWMANAGER_H */

