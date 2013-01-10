/* 
 * File:   ModificatorComponent.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 9. Januar 2013, 15:09
 */

#include "../header.h"

ModificatorComponent::ModificatorComponent() {
    opt = NULL;

}

ModificatorComponent::ModificatorComponent(ImageModificator* mod) {
    opt = mod;
}

ModificatorComponent::ModificatorComponent(const ModificatorComponent& orig) : ImageModificator(orig) {
    modifierName = orig.modifierName;
    modifierPos = orig.modifierPos;
}

ModificatorComponent::~ModificatorComponent() {
    delete opt;
}

void ModificatorComponent::setName(String name) {
    modifierName = name;
}

void ModificatorComponent::setPosition(int pos) {
    modifierPos = pos;
}

String ModificatorComponent::getName() {
    return modifierName;
}

int ModificatorComponent::getPos() {
    return modifierPos;
}