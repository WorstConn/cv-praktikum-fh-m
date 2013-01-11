/* 
 * File:   MainTest.cpp
 * Author: Julian Cordes, Nils Frenking
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

    vector<ATest*>::iterator iter;
    for (iter = tests.begin(); iter != tests.end(); iter++) {
        retVals.push_back((*iter)->testMain(args));
    }
    vector<int>::iterator it;
    for (it = retVals.begin(); it != retVals.end(); it++) {
        if ((*it) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
    }
    DBG("%i Tests ohne Fehler ausgeführt.", static_cast<int>(retVals.size()));
    return EXIT_SUCCESS;
}

void MainTest::putTest(ATest* test) {

    tests.push_back(test);
}


void MainTest::printUsage() {
    cout << "No Arguments supported" << endl;
}
