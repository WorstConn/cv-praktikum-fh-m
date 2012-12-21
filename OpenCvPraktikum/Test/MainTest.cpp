/* 
 * File:   MainTest.cpp
 * Author: Nils Frenking
 * 
 * Created on 21. Dezember 2012, 12:07
 */

#include "../header.h"

using namespace std;
using namespace cv;

MainTest::MainTest() {
    tests = vector<ATest* > ();
}

MainTest::MainTest(const MainTest& orig) {
    tests = orig.tests;
}

MainTest::~MainTest() {

}

int MainTest::testMain(vector<String> args) {// LOL
    vector<int> retVals;
    int testsResult = 0x00;
    vector<ATest*>::iterator iter;
    for (iter = tests.begin(); iter != tests.end(); iter++) {
        retVals.push_back((*iter)->testMain(args));
    }
}

void MainTest::putTest(ATest* test) {

    tests.push_back(test);
}



