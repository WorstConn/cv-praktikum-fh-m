/* 
 * File:   CompositeModificator.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 20. Dezember 2012, 12:30
 */

#ifndef COMPOSITEMODIFICATOR_H
#define	COMPOSITEMODIFICATOR_H

#include "../header.h"

class CompositeModificator : public ImageModificator {
public:
    CompositeModificator();
    CompositeModificator(const CompositeModificator& orig);
    virtual ~CompositeModificator();
protected:
    
private:


};

#endif	/* COMPOSITEMODIFICATOR_H */

