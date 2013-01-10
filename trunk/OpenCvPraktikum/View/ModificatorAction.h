/* 
 * File:   ModificatorAction.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 10. Januar 2013, 00:27
 */

#ifndef MODIFICATORACTION_H
#define	MODIFICATORACTION_H

#include "../header.h"

using namespace std;
using namespace cv;

class ModificatorAction : public AImageAction {
public:
    ModificatorAction(String wN, String aN, int maxval, int minval = 0);
    ModificatorAction(const ModificatorAction& orig);

    virtual ~ModificatorAction();
    virtual void action(int pos, void* data);
    virtual void setModifikator(ImageModificator* m);
protected:
    ImageModificator* mod;
private:


};

#endif	/* MODIFICATORACTION_H */

