/* 
 * File:   AAction.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 4. Januar 2013, 13:48
 */

#include "../header.h"

using namespace std;
using namespace cv;

AAction::AAction(String wN, String aN, int max, int min) {
    wndName = wN;
    actionName = aN;
    lastPos = 0;
    maxVal = max;
    minVal = min;
}

AAction::AAction(const AAction& orig) {
    wndName = orig.wndName;
    actionName = orig.actionName;
    lastPos = orig.lastPos;
    maxVal = orig.maxVal;
    minVal = orig.minVal;
}

AAction::~AAction() {
}

String AAction::getActionDesc() {
    return actionName;
}

String AAction::getWindowName() {
    return wndName;

}

void AAction::setActionDesc(String ad) {
    actionName = ad;
}

void AAction::setWindowName(String wn) {
    wndName = wn;
}

int* AAction::posPtr() {
    return &lastPos;
}

int AAction::getMax(){
    return maxVal;
}
int AAction::getMin(){
 return minVal;   
}