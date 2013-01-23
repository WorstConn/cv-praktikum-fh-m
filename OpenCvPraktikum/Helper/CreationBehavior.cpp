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
    usePresegmentedData=false;
}


CreationBehavior::CreationBehavior(const CreationBehavior& orig) {
    usePresegmentedData=orig.usePresegmentedData;
}

CreationBehavior::~CreationBehavior() {
}

String CreationBehavior::iToStr(int i) {
    stringstream stringStream;
    stringStream << i;
    return stringStream.str();
}

bool CreationBehavior::presegmentedData(){
    return usePresegmentedData;
}