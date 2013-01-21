/* 
 * File:   WindowManager.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 28. Dezember 2012, 17:11
 */


#include "../header.h"

using namespace std;
using namespace cv;

WindowManager* WindowManager::instance = NULL;
vector<AAction*> WindowManager::callbacks = vector<AAction*>();

vector<CvWindow*> WindowManager::windows = vector<CvWindow*>();

WindowManager::WindowManager() {
}

WindowManager::WindowManager(const WindowManager& orig) {
}

WindowManager::~WindowManager() {
}

WindowManager* WindowManager::getInstance() {
    if (instance == NULL) {
        instance = new WindowManager();
    }
    return instance;
}

void WindowManager::callBackFkt(int p, void* data) {
    char* str = (char*) data;
    String s = String(str);
    vector<AAction*>::iterator iter;
    for (iter = callbacks.begin(); iter != callbacks.end(); iter++) {
        if ((*iter)->getActionDesc().find(s) != String::npos) {
            (*iter)->action(p, data);
        }
    }

    str = NULL;
}

void WindowManager::putTrackbarCallback(AAction* action, String wndName) {

    for (int i = 0; i < (int) callbacks.size(); i++) {
        /*Pruefen, ob die Aktion mit diesem Fenster Verknuept ist*/
        if (callbacks[i]->getActionDesc().find(action->getActionDesc()) != String::npos && callbacks[i]->getWindowName().find(wndName) != String::npos) {

            DBG("Callback bereits vorhanden");
            return;
        }
    }
    /*Registriere die Trackbar, falls noch nicht geschehen*/

    DBG("Registriere Callback");
    action->setWindowName(wndName);
    createTrackbar(action->getActionDesc(), wndName, action->posPtr(), action->getMax(), &callBackFkt, (void*) action->getActionDesc().c_str());
    callbacks.push_back(action);



}

CvWindow* WindowManager::createWindow(String name, int w, int h) {
    CvWindow* wnd = new CvWindow(name, w, h);
    windows.push_back(wnd);
    return wnd;
}

CvWindow* WindowManager::getWindow(String name) {
    CvWindow* erg = NULL;
    vector<CvWindow*>::const_iterator iter;
    for (iter = windows.begin(); iter != windows.end(); iter++) {
        if ((*iter)->getName().find(name) != String::npos) {
            erg = (*iter);
            break;
        }
    }
    return erg;
}

AAction* WindowManager::getAction(String desc) {
    AAction* erg = NULL;
    vector<AAction*>::const_iterator iter;
    for (iter = callbacks.begin(); iter != callbacks.end(); iter++) {
        if ((*iter)->getActionDesc().find(desc) != String::npos) {
            erg = (*iter);
            break;
        }
    }
    return erg;
}

void WindowManager::relesase() {
    while (!callbacks.empty()) {
        AAction* cb = callbacks[0];
        callbacks.erase(callbacks.begin());
        if (cb != NULL) {

            cb = NULL;
        }
    }
    while (!windows.empty()) {
        CvWindow* wnd = windows[0];
        windows.erase(windows.begin());
        if (wnd != NULL) {
            if (wnd->isShowing()) {
                wnd->closeWindow();
            }

            delete wnd;
        }
    }
}

void WindowManager::showWindow(String name) {

    int len = windows.size();
    for (int i = 0; i < len; i++) {
        if (windows[i]->getName().find(name) != String::npos) {
            if (!windows[i]->isShowing()) {
                DBG("Fenster anzeigen");
                windows[i]->showWindow();
                break;
            }
        }
    }
}

void WindowManager::updateWindowImage(String name, Mat* mat) {
    int len = windows.size();
    for (int i = 0; i < len; i++) {
        if (windows[i]->getName().find(name) != String::npos) {
            DBG("Fensterbild gesetzt");
            windows[i]->setCurrentImage(mat);
            break;

        }
    }
}

void WindowManager::closeWindow(String name) {
    int len = windows.size();
    for (int i = 0; i < len; i++) {
        if (windows[i]->getName().find(name) != String::npos) {
            if (windows[i]->isShowing()) {
                windows[i]->closeWindow();
                windows.erase(windows.begin()+i);
                break;
            }
        }
    }
}