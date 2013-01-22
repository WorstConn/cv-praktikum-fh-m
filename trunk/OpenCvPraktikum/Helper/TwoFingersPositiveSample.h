/* 
 * File:   TwoFingersPositiveSample.h
 * Author: Nils Frenking
 *
 * Created on 22. Januar 2013, 00:09
 */

#ifndef TWOFINGERSPOSITIVESAMPLE_H
#define	TWOFINGERSPOSITIVESAMPLE_H
#include "../header.h"

using namespace std;
using namespace cv;

class TwoFingersPositiveSample : public CreationBehavior {
public:
    TwoFingersPositiveSample();
    TwoFingersPositiveSample(const TwoFingersPositiveSample& orig);
    virtual ~TwoFingersPositiveSample();
private:

};

#endif	/* TWOFINGERSPOSITIVESAMPLE_H */

//FIXME: Objektklassen erstellen und ausimplementieren.
//FIXME: Einen Detektor, der alle Objekte(Objekt-Klassen) kennt, und bei Erkennung eine Instanz der Klasse(oder kopie) erstellt.
//FIXME: Cascaden für alle fehlenden Objekte anlernen.
//FIXME: Referenzobjekte (Vorsegmentierte) Bilder einlesen, Informationen extrahieren, speichern und dem Detektor eine Vergleichs-/Erkennungs- Möglichkeit bieten.