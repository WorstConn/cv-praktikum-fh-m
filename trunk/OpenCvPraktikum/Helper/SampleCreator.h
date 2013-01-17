/* 
 * File:   SampleCreator.h
 * Author: Nils Frenking
 *
 * Created on 10. Januar 2013, 12:00
 */

#ifndef SAMPLECREATOR_H
#define	SAMPLECREATOR_H

#include "../header.h"

using namespace std;
using namespace cv;

class SampleCreator {
public:

    SampleCreator(const SampleCreator& orig);
    virtual ~SampleCreator();
    static SampleCreator* getInstance();
    void setCreationMethod(CreationBehavior* cb);
    void addInputDir(String dir, String backgroundImage);
    void setOutputPath(String output);
    bool removeFromInput(String dir);
    bool createSampleFile();

protected:
    CreationBehavior* creationMethod;
    StringArray imageInfo;
    String outputFilePath;
    StringArray inputDirectories;
    StringArray backgroundImages;

private:
    SampleCreator();
    static SampleCreator* instance;

};

#endif	/* SAMPLECREATOR_H */

