/* 
 * File:   PositiveSample.h
 * Author: Nils Frenking
 *
 * Created on 10. Januar 2013, 13:42
 */

#ifndef POSITIVESAMPLE_H
#define	POSITIVESAMPLE_H
#include "../header.h"

using namespace std;
using namespace cv;
class PositiveSample : public CreationBehavior{
public:
    PositiveSample();
    PositiveSample(const PositiveSample& orig);
    virtual ~PositiveSample();
    /**
     * Erstellt eine 'Zeile' Bildinformationen, wie sie f&uuml;r das Training der Cascaden ben&ouml;tigt wird.<br>
     * Unterklassen spezifizieren, welche Informationen im R&uuml;ckgabewert enthalten sind.<br> 
     * -> es werden verschiedene Informationen f&uuml;r positive und negative Samples benoetigt.
     * 
     * @param img das Eingabebild.
     * @param imgPath Pfad des Eingabebildes.
     * @param pos die Position des Bildes in einer Liste von Eingabebildern
     * @return ein Text mit Informationen &uuml;ber das Eingabebild.<br>
     *          enth&auml;lt mindestens den Dateinamen und die Maße des Bildes.<br>
     *          
     */
    virtual String createImageInfo(Mat& img, String imgPath, int pos = -1);

    /**
     * Erstellt in einem 'Abwasch' eine Datei, die allen Bildpfaden in den Eingabevektoren bestimmte Informationen zuweist.<br>
     * Diese Datei kann dann, bei erfolgreicher Erstellung, zum Training von Cascaden verwendet werden.
     * 
     * @param input Vektor von Vektoren von Bildpfaden.<br> 
     *               F&uuml;r jeden Ordner existiert ein Vektor von Pfaden zu Bildern, die in ihm enthalten sind.
     * 
     * @param output Pfad an dem die Ausgabedatei (.dat) erstellt werden soll.
     * @param backgroundImagePath Falls nicht leer und falls <code>backgroundImagePath.size() == input.size()</code>,<br>
     *  werden die enthaltenen Strings als Pfade zu Bildern betrachtet, mithilfe derer eine Segmentierung der Eingabebilder vorgenommen werden kann.
     * @param createMarkedOutputFiles Falls <code>TRUE</code>, wird bei der Operation eine Kopie jedes Eingabebildes erstellt, auf der erkannte Objekte mit einem Rechteck eingefasst sind.
     *          
     */
    virtual void createImageInfo(vector<vector<String> > input, String output, vector<String> backgroundImagePath, bool createMarkedOutputFiles = false);
private:
    String currentBackgroundPath;
    bool drawMarkedSamples;
    String currentOutputPath;

};

#endif	/* POSITIVESAMPLE_H */

