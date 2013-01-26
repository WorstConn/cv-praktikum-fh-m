/* 
 * File:   SampleCreator.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 10. Januar 2013, 12:00
 */

#include "../header.h"

using namespace std;
using namespace cv;

SampleCreator* SampleCreator::instance = NULL;

SampleCreator::SampleCreator() {
    creationMethod = NULL;
}

SampleCreator::SampleCreator(const SampleCreator& orig) {
    creationMethod = orig.creationMethod;
    backgroundImages = orig.backgroundImages;
    imageInfo = orig.imageInfo;
    inputDirectories = orig.inputDirectories;
    outputFilePath = orig.outputFilePath;
}

SampleCreator::~SampleCreator() {
    if (creationMethod != NULL) {
        delete creationMethod;
    }
}

SampleCreator* SampleCreator::getInstance() {
    if (instance == NULL) {
        instance = new SampleCreator();
    }
    return instance;
}

void SampleCreator::setCreationMethod(CreationBehavior* cb) {
    creationMethod = cb;
}

void SampleCreator::addInputDir(String dir, String backgroundImage) {
    if (inputDirectories.empty()) {
        inputDirectories.push_back(dir);
        if (!backgroundImage.empty()) {
            backgroundImages.push_back(backgroundImage);
        }
    } else {
        bool contains = false;
        for (StringArray::iterator iter = inputDirectories.begin(); iter != inputDirectories.end(); iter++) {
            if ((*iter).compare(dir) == 0) {
                contains = true;
                break;
            }

        }
        if (!contains) {
            inputDirectories.push_back(dir);

            if (!backgroundImage.empty()) {
                backgroundImages.push_back(backgroundImage);
                DBG("Eingabeordner: %s und Hintergrundbild: %s hinzugefuegt.", dir.c_str(), backgroundImage.c_str());
            }

        }
    }
}

void SampleCreator::setOutputPath(String output) {
    if (output.length() <= 4 || output.compare(output.length() - 4, 4, ".dat")) {
        DBG("Ausgabe muss eine .dat Datei sein.");
    }
    outputFilePath = output;
}

bool SampleCreator::removeFromInput(String dir) {
    StringArray::iterator iter;
    bool contains;
    int pos = 0;
    for (iter = inputDirectories.begin(); iter != inputDirectories.end(); iter++) {
        if ((*iter).compare(dir) == 0) {
            contains = true;
            break;
        }
        pos++;
    }
    if (contains) {
        inputDirectories.erase(iter);
        if (!backgroundImages.empty() && ((int) backgroundImages.size()) > pos) {
            backgroundImages.erase((backgroundImages.begin() + pos));
        }
    }
    return contains;
}

bool SampleCreator::createSampleFile() {
    if (creationMethod == NULL) {
        DBG("Kein Erstellverhalten definiert.");
        return false;
    }
    if (inputDirectories.empty()) {
        DBG("Keine Eingabe");
        return false;
    }
    if (!backgroundImages.empty() && backgroundImages.size() != inputDirectories.size()) {
        DBG("Wenn festgelegt, muss für jeden Eingabeordner eine Hintergrunddatei existieren.");
        return false;
    }
    StringSet searchStrings = StringSet();
    searchStrings.insert("jpg");
    searchStrings.insert("jpeg");
    searchStrings.insert("png");
    searchStrings.insert("bmp");


    FileManager* fileMan = FileManager::getInstance();
    StringArray tmp;
    vector < StringArray > images = vector < StringArray > ();
    for (StringArray::iterator iter = inputDirectories.begin(); iter != inputDirectories.end(); iter++) {
        if (fileMan->checkDir((*iter)) <= 0) {
            DBG("Ordner %s enthaelt keine Bilder!", (*iter).c_str());
            return false;
        }

        fileMan->setSearchPath((*iter));
        fileMan->setSearchStrings(searchStrings);
        tmp = fileMan->getFoundList();
        fileMan->clearAll();
        images.push_back(tmp);
    }

#if DEBUG
    /*Falls wir uns im Debugmodus befinden, moechten wir, falls möglich die Zwischenergebnisse(Bilder) der Erstellung sehen.*/
    creationMethod->createImageInfo(images, outputFilePath, backgroundImages, true, (backgroundImages.empty()) ? true : false);
#else
    creationMethod->createImageInfo(images, outputFilePath, backgroundImages, false, (backgroundImages.empty()) ? true : false);
#endif
    return true;
}