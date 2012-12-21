/* 
 * File:   TrackbarData.h
 * Author: Nils Frenking
 *
 * Created on 21. Dezember 2012, 00:20
 */

#ifndef TRACKBARDATA_H
#define	TRACKBARDATA_H
#include "../header.h"

using namespace std;
using namespace cv;

class TrackbarData {
public:
    TrackbarData(String n, int max, void (*ptr)(int pos, void* usrData));
    TrackbarData(const TrackbarData& orig);
    virtual ~TrackbarData();
    virtual String getName();
    virtual int getMaxVal();
    virtual TrackbarCallback getCallback();
private:
    TrackbarCallback callback;
    int max;
    String name;

};


#endif	/* TRACKBARDATA_H */

