/*
 * Math.cpp
 *
 *  Created on: 10.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#include "../header.h"
using namespace std;
using namespace cv;

MyMath::MyMath() {


}

MyMath::~MyMath() {

}

int MyMath::ggtIt(int x, int y) {
    int z;
    /**
     * Falls x < y vertausche die Werte
     */
    if (x < y) {
        z = x;
        x = y;
        y = z;
    }

    while (y != 0) {
        z = x % y;
        x = y;
        y = z;
    }
    return x;
}

int MyMath::ggtRek(int x, int y) {

    /**
     * Falls x < y vertausche die Werte
     */
    if (x < y) {
        int z;
        z = x;
        x = y;
        y = z;
    }
    if (y == 0) {
        //Ergebnis
        return x;
    } else {
        //Einen Rekursionsschritt tiefer
        return ggtRek(y, x % y);
    }
}

double MyMath::abs(double value) {
    if (value < 0.0) {
        return (value * (-1.0));
    } else {
        return value;
    }
}

float MyMath::abs(float value) {
    if (value < 0.0) {
        return (value * (-1.0));
    } else {
        return value;
    }
}

int MyMath::abs(int value) {
    if (value < 0) {
        return (value * (-1));
    } else {
        return value;
    }
}

bool MyMath::inRange(unsigned int val, unsigned int ref, unsigned int percent) {
    float p = ((float) percent) / 100.0;
    float max = ((float) ref)*(1 + p);
    float min = ((float) ref)*(1 + p);
    if (((unsigned int)cvRound(min)) > val or ((unsigned int)cvRound(max)) < val) {
        return false;
    }
    return true;
}

bool MyMath::biggerThan(Rect a, Rect b) {
    /*
     * Sind beide Seiten groesser -> true
     */
    if (a.width > b.width && a.height > b.height) {
        return true;

    } else
        /* ist die Flaeche groesser -> true*/
        if ((a.width * a.height)>(b.height * b.width)) {
        return true;
    } else {
        return false;
    }
}//FIXME: ...

float MyMath::dist(Point3f pFrom, Point3f pTo) {
    Point3f diff = pTo - pFrom;

    return sqrt((diff.x * diff.x)+(diff.y * diff.y)+(diff.z * diff.z));

}

float MyMath::dist(Point2i pFrom, Point2i pTo) {
    Point2f diff;
    
    diff.x = (float) (pTo.x - pFrom.x);
    diff.y = (float) (pTo.y - pFrom.y);

    
    float dst=sqrt((diff.x * diff.x)+(diff.y * diff.y));
    
    return dst;

}

bool MyMath::isInCircle(Point2i center, int radius, Point2i examine) {
    if (dist(examine, center) > ((float)radius)) {
        
        return false;

    } else {
        return true;
    }
}

Point3i MyMath::RectToCircle(Rect rect) {
    Point3i erg;
    erg.x = cvRound((rect.width * 0.5));
    erg.y = cvRound((rect.height * 0.5));
    erg.z = cvRound((rect.width + rect.height)*0.25);
    return erg;
}

Point2i MyMath::RectCenter(Rect rect){
    Point2i erg;
    erg.x = cvRound((rect.width * 0.5));
    erg.y = cvRound((rect.height * 0.5));
    
    return erg;
}

int MyMath::RectRadius(Rect rect){
    int erg;
    erg = cvRound((rect.width + rect.height)*0.25);
    return erg;
}