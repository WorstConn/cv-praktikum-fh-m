/* 
 * File:   ContourCreationMethod.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 17. Januar 2013, 15:52
 */

#ifndef CONTOURCREATIONMETHOD_H
#define	CONTOURCREATIONMETHOD_H
#include "../header.h"
using namespace std;
using namespace cv;

class ContourCreationMethod {
public:
    ContourCreationMethod();
    ContourCreationMethod(const ContourCreationMethod& orig);
    virtual ~ContourCreationMethod();
    /**
     * Erstellt ein Kontour-Array des Eingabebildes.
     * @param inputImg Das Eingabebild.
     * @param mask Eine optionale Eingabemaske.
     * @param maxObjects maximale Anzahl an einzelnen Contourbereiche, die zusammengefasst werden sollen. 1 -> nur das gr&ouml;&szlig;te Objekt ist im Ergebnis enthalten.
     * @param isColorImage
     * @return Das errechnete Kontour-Array
     */
    virtual PointArray createContour(Mat inputImg,Mat mask, int maxObjects, bool isColorImage)=0;
private:

};

#endif	/* CONTOURCREATIONMETHOD_H */

//FIXME: Implementieren.