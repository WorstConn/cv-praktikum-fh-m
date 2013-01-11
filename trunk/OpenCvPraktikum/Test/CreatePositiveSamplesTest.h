/* 
 * File:   CreatePositiveSamplesTest.h
 * Author: Nils Frenking
 *
 * Created on 11. Januar 2013, 00:17
 */

#ifndef CREATEPOSITIVESAMPLESTEST_H
#define	CREATEPOSITIVESAMPLESTEST_H

#include "../header.h"
using namespace std;
using namespace cv;

class CreatePositiveSamplesTest : public ATest {
public:
    CreatePositiveSamplesTest();
    CreatePositiveSamplesTest(const CreatePositiveSamplesTest& orig);
    virtual ~CreatePositiveSamplesTest();
    virtual int testMain(vector<String> args);

    virtual void printUsage();
private:

};

#endif	/* CREATEPOSITIVESAMPLESTEST_H */

