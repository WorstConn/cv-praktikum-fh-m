/* 
 * File:   CompositeModificator.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 20. Dezember 2012, 12:30
 */

#include "../header.h"

using namespace std;
using namespace cv;

CompositeModificator::CompositeModificator() {
    components = vector<ModificatorComponent*>();
}

CompositeModificator::CompositeModificator(const CompositeModificator& orig) : ImageModificator(orig) {
}

CompositeModificator::~CompositeModificator() {
    ModificatorComponent* tmp;
    while (!components.empty()) {
        tmp = components[0];
        components.erase(components.begin());
        delete tmp;
    }
}

void CompositeModificator::modify(Mat& img) {
    vector<ModificatorComponent*>::const_iterator iter;
    for (iter = components.begin(); iter != components.end(); iter++) {
        (*iter)->modify((img));
    }
}

float CompositeModificator::getScale() {
    vector<ModificatorComponent*>::const_iterator iter;
    float scale = 1.0;
    for (iter = components.begin(); iter != components.end(); iter++) {
        scale *= (*iter)->getScale();
    }
    return scale;
}

void CompositeModificator::addModificator(String name, ModificatorComponent* mod) {
    assert(mod != NULL);
    assert(!name.empty());
    int pos = components.size();
    mod->setName(name);
    mod->setPosition(pos);
    components.push_back(mod);
}

bool CompositeModificator::removModificator(String name) {
    bool erg = false;
    ModificatorComponent* cmp;
    vector<ModificatorComponent*>::iterator iter;
    for (iter = components.begin(); iter != components.end(); iter++) {
        if (name.find((*iter)->getName()) == 0) {
            DBG("Modifikator gefundnen. Wird entfernt");
            cmp = (*iter);
            components.erase(iter);
            erg = true;
            break;
        }
    }
    if (erg) {

        delete cmp;
    }
    return erg;
}

bool CompositeModificator::removeModificator(int pos) {
    if(!(((int)components.size()) > pos && pos > 0)){
        return false;
    }
    vector<ModificatorComponent*>::iterator iter;
    iter = components.begin();
    iter += pos;
    ModificatorComponent* cmp = components.at(pos);

    components.erase(iter);

    delete cmp;
    return true;
}