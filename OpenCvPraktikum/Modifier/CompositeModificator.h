/* 
 * File:   CompositeModificator.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 20. Dezember 2012, 12:30
 */

#ifndef COMPOSITEMODIFICATOR_H
#define	COMPOSITEMODIFICATOR_H

#include "../header.h"
#include "ModificatorComponent.h"
using namespace std;
using namespace cv;

class CompositeModificator : public ImageModificator {
public:
    CompositeModificator();
    CompositeModificator(const CompositeModificator& orig);
    virtual ~CompositeModificator();
    virtual void modify(Mat& img);
    virtual float getScale();
    virtual void addModificator(String name, ModificatorComponent* mod);
    virtual bool removModificator(String name);
    virtual bool removeModificator(int pos);
    
protected:
    
    vector<ModificatorComponent*> components;
private:


};

#endif	/* COMPOSITEMODIFICATOR_H */

