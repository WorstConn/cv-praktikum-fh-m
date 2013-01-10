/* 
 * File:   ModificatorAction.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 10. Januar 2013, 00:27
 */

#include "../header.h"

using namespace std;
using namespace cv;

ModificatorAction::ModificatorAction(String wN, String aN, int maxval, int minval) : AImageAction(wN, aN, maxval, minval) {
    mod = NULL;
}

ModificatorAction::ModificatorAction(const ModificatorAction& orig) : AImageAction(orig) {
    mod = orig.mod;
}

ModificatorAction::~ModificatorAction() {
    if (mod != NULL) {
        delete mod;
    }
}

void ModificatorAction::action(int pos, void* data) {
    if (mod == NULL) {
        DBG("Kein Modifikator gesetzt!");
    }
    Mat tmp = (*img);
    mod->modify(tmp);
}

void ModificatorAction::setModifikator(ImageModificator* m) {
    mod = m;
}