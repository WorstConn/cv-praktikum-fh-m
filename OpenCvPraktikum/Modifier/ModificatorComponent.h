/* 
 * File:   ModificatorComponent.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 9. Januar 2013, 15:09
 */

#ifndef MODIFICATORCOMPONENT_H
#define	MODIFICATORCOMPONENT_H

#include "../header.h"
using namespace cv;
using namespace std;

class ModificatorComponent : public ImageModificator {
public:
    ModificatorComponent();
    /**
     * Erstelle die Komponente aus einem bestehenden Modifikator
     * @param mod
     */
    ModificatorComponent(ImageModificator* mod);
    ModificatorComponent(const ModificatorComponent& orig);
    virtual ~ModificatorComponent();
    /**
     * Setzt den Namen der Komponente. Dient der Identifikation.
     * @param name
     */
    virtual void setName(String name);
    /**
     * Setzt die Position der Komponente. Spiegelt die Anordnung der Komponente wieder. Dient der Identifikation.
     * @param pos
     */
    virtual void setPosition(int pos);
    /**
     * Getter f&uuml;r den Namen.
     * @return 
     */
    virtual String getName();
    /**
     * Getter f&uuml;r die Position.
     * @return 
     */
    virtual int getPos();
protected:
    String modifierName;
    int modifierPos;
    /**
     * Optionaler Modifikator, mit dem diese Komponente Instanziert werden kann.<br>
     * <b>Falls !=NULL</b>, kann die enthaltene Operation mit der eigenen kombiniert oder ersetzt werden.
     * 
     */
    ImageModificator* opt;
private:

};
//FIXME: Weiter Implementierung notwendig.
#endif	/* MODIFICATORCOMPONENT_H */

