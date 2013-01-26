/* 
 * File:   PixelObject.h
 * Author: Julian Cordes, Nils Frenking
 *
 * Created on 17. Januar 2013, 12:45
 */

#ifndef PIXELOBJECT_H
#define	PIXELOBJECT_H

#include "../header.h"
using namespace std;
using namespace cv;

/**
 * //TODO: Passendere Bezeichnung finden.
 */
class PixelObject {
public:
    PixelObject(Mat* objImg);
    PixelObject(const PixelObject& orig);
    virtual ~PixelObject();

    /**
     * Versucht dieses Objekt auf dem Bild zu finden.
     * @return <code>true</code>, wenn dieses Objekt gefunden wurde, sonst <code>false</code>
     */
    virtual bool detect() = 0;

    /**
     * Gibt die Maske des Objektbildes zur&uuml;ck.
     * @return Die Objektmaske oder <code>NULL</code>.
     */
    virtual Mat* getObjectMask();
    /**
     * Gibt das Histogramm des Objektbildes zur&uuml;ck.
     * @return Das Objekthistogramm, oder <code>NULL</code>.
     */
    virtual MatND* getObjectHistogram();

    /**
     * Gibt die errechnete Maske des Eingabe/Vergleichsbildes zur&uuml;ck.
     * @return Die Objektmaske oder <code>NULL</code>.
     */
    virtual Mat* getInputMask();

    /**
     * Setzt das Eingabe/Vergleichsbild
     * @param img Das Eingabefarbbild.
     */
    virtual void setInputImage(Mat* img);





protected:

    ImageAttributes* objectAttributes;
    ImageAttributes* inputAttributes;
    HistogramCreationMethod* histogramCreation;
    MaskCreationMethod* maskCreation;
    ContourCreationMethod* contourCreation;
    KeyPointCreationMethod* keypointCreation;
    
    CvHelper* helper;


    /**
     * Erstellt ein Histogramm des Objektbildes. Unterklassen m&uuml;ssen entscheiden, wie dieses geartet sein soll.
     */
    virtual void createObjectHistogram();

    /**
     * Erstellt ein Histogramm des Eingabebildes. Unterklassen m&uuml;ssen entscheiden, wie dieses geartet sein soll.
     */
    virtual void createInputHistogram();
    /**
     * Erstellt die Maske des Eingabebildes.
     */
    virtual void createObjectMask();

    /**
     * Erstellt die Kontour des Objektbildes.
     */
    virtual void createObjectContour();

    /**
     * Erstellt die Kontour des Eingabebildes.
     */
    virtual void createInputContour();

    /**
     * Sucht Keypoints auf dem Objektbild.
     */
    virtual void createObjectKeypoints();
    /**
     * Sucht Keypoints auf dem Eingabebild.
     */
    virtual void createInputKeypoints();


    /**
     * Falls das Objekt in einer bekannten/vorhersehbaren Art und Weise entartet ist, kann hier versucht werden, den Fehler zu beheben. <br>
     * Es bietet sich an, diese Funktion, in Kombination mit <code>detect()</code> einzusetzen.
     * @return <code>true</code>, wenn der Reparaturvorgang erfoglreich Beendet werden konnte, und das Bild entsprechend . Sonst <code>false</code>.
     */
    virtual bool tryRepair() = 0;


    /**
     * Setzt den Indikator, welcher angibt, ob eine Aktualisierung der Daten sinnvoll/nötig.
     * @param bln Der neue Wert des Indikators.
     */
    virtual void setInputChanged(bool bln);

    /**
     * Gibt an, ob sich die Eingabe ge&auml;ndert hat und die Histoigramme und Masken neu erstellt werden muss.
     * @return <code>true</code>, wenn die Daten <b>NICHT</b> mehr aktuell sind, sonst <code>false</code>.
     */
    virtual bool inputChanges();


private:
    bool inputChanged;
};

#endif	/* PIXELOBJECT_H */

