/* 
 * File:   ImageListOutput.h
 * Author: Nils Frenking
 *
 * Created on 20. Dezember 2012, 00:57
 */

#ifndef IMAGELISTOUTPUT_H
#define	IMAGELISTOUTPUT_H

#include "../header.h"

class ImageListOutput : public Output {
public:
    ImageListOutput(String p, String n, String fileExt = PREF_IMAGE_OUTPUT_FILE_EXT);
    ImageListOutput(const ImageListOutput& orig);
    virtual ~ImageListOutput();
    virtual bool open();
    /**
     * Schreibt das Bild mit aufsteigender Nummerierung in den Ordner.
     * @param mat 
     */
    virtual void write(Mat& mat);

    virtual void close();
    /**
     * Setzt den Dateicounter zur&uuml;ck
     */
    virtual void resetFileCounter();

private:
    /**
     * Erstellt die Standard-Parameter f&uuml;r die <code>imwrite()</code> funktion
     * @return Einen Vektor der l&auml;nge 2.
     */
    vector<int> createWriteParams();
    /**
     * Kleiner Helfer zum erstellen des Dateinamen.
     * @param number die Zahl
     * @return die Zahl als String
     */
    String convertInt(int number);
    /**
     * Z&auml;
     */
    int counter;
    /**
     * Speichert die Standardwerte, um Zeit einzusparen.
     * @see createWriteParams()
     */
    vector<int> writeParams;

};

#endif	/* IMAGELISTOUTPUT_H */

