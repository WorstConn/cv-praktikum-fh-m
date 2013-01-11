/* 
 * File:   CreationBehavior.cpp
 * Author: Nils Frenking
 * 
 * Created on 10. Januar 2013, 12:00
 */

#include "../header.h"

using namespace std;
using namespace cv;

CreationBehavior::CreationBehavior() {
}

CreationBehavior::CreationBehavior(const CreationBehavior& orig) {
}

CreationBehavior::~CreationBehavior() {
}

String CreationBehavior::iToStr(int i) {
    stringstream stringStream;
    stringStream << i;
    return stringStream.str();
}
