/* 
 * File:   TrackbarData.cpp
 * Author: Nils Frenking
 * 
 * Created on 21. Dezember 2012, 00:20
 */

#include "../header.h"

using namespace std;
using namespace cv;

TrackbarData::TrackbarData(String n, int max, void (*ptr)(int pos, void* usrData)) {
    name = n;
    this->max = max;
    callback = ptr;
}

TrackbarData::TrackbarData(const TrackbarData& orig) {
    name = orig.name;
    max = orig.max;
    callback = orig.callback;

}

TrackbarData::~TrackbarData() {

}

String TrackbarData::getName() {
    return name;
}

int TrackbarData::getMaxVal() {
    return max;
}

TrackbarCallback TrackbarData::getCallback() {
    return callback;
}
