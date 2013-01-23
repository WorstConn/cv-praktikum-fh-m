/* 
 * File:   NegativeSample.cpp
 * Author: Nils Frenking
 * 
 * Created on 10. Januar 2013, 13:42
 */

#include "../header.h"

using namespace std;
using namespace cv;

NegativeSample::NegativeSample() {
}

NegativeSample::NegativeSample(const NegativeSample& orig) : CreationBehavior(orig){
}

NegativeSample::~NegativeSample() {
}

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
String NegativeSample::createImageInfo(Mat& img, String imgPath, int pos) {
    String erg;


    //    // <editor-fold defaultstate="collapsed" desc="Falls 'pos'">
    //    if (pos != -1) {
    //        posStr = iToStr(pos);
    //        DBG("Position: %i", pos);
    //    }// </editor-fold>

    erg = imgPath;
    return erg;
}

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
void NegativeSample::createImageInfo(ArrayOfStringArrays input, String output, StringArray backgroundImagePath, bool createMarkedOutputFiles,bool presegmentedData) {
    CV_Assert(!input.empty());
    CV_Assert(!output.empty());
    if (!backgroundImagePath.empty()) {
        DBG("Ignoiere Hintergrundpfade, da negative Samples keine Objekte beinhalten");
    }
    if (createMarkedOutputFiles) {
        DBG("Werde keine Markierung der negative erstellen,da sie keine Objekte beinhalten");
    }
    int counter = 0;
    ofstream outputStream;
    Mat current = Mat::zeros(20, 20, CV_8UC3);
    outputStream.open(output.c_str(), _Ios_Openmode::_S_out);
    CV_Assert(outputStream.is_open());
    for (ArrayOfStringArrays::iterator root = input.begin(); root != input.end(); root++) {
        for (StringArray::iterator files = (*root).begin(); files != (*root).end(); files++) {

            outputStream << createImageInfo(current, (*files), counter);
            if (((files + 1)) != (*root).end()) {
                outputStream << endl;
            }
            counter++;
        }
    }
    outputStream.close();
    current.release();
}