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

vector<Window*> WindowManager::windows = vector<Window*>();

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

Window* WindowManager::createWindow(String name, int w, int h) {
    Window* wnd = new Window(name, w, h);
    windows.push_back(wnd);
    return wnd;
}
