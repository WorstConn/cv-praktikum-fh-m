/* 
 * File:   PositiveSample.cpp
 * Author: Nils Frenking
 * 
 * Created on 10. Januar 2013, 13:42
 */

#include "../header.h"

using namespace std;
using namespace cv;

PositiveSample::PositiveSample() {
    drawMarkedSamples = FALSE;
}

PositiveSample::PositiveSample(const PositiveSample& orig) {
    currentBackgroundPath = orig.currentBackgroundPath;
    drawMarkedSamples = orig.drawMarkedSamples;
    currentOutputPath = orig.currentOutputPath;
}

PositiveSample::~PositiveSample() {
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
String PositiveSample::createImageInfo(Mat& img, String imgPath, int pos) {
    CV_Assert(!currentBackgroundPath.empty());

    // <editor-fold defaultstate="collapsed" desc="Deklarationen">
    Mat kernel = Mat::ones(3, 3, CV_8U);
    Mat inputImage = img;
    Mat backgroundImage = imread(currentBackgroundPath);
    Mat cannyImage;
    Mat inputImgF64;
    Mat bgF64;
    Mat diff;
    Mat diffGray;
    Mat ergC3;
    vector<vector<Point> > contours0;
    vector<Vec4i> hierarchy;

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Konversion der Eingabebilder">
    inputImgF64 = Mat(inputImage.size(), CV_64FC3);
    inputImage.copyTo(inputImgF64);
    bgF64 = Mat(backgroundImage.size(), CV_64FC3);
    backgroundImage.copyTo(bgF64);
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Erstellung eines 1- und 3- Kanaligen Differenzbildes">
    diff = Mat::zeros(bgF64.size(), CV_64FC3);
    absdiff(inputImgF64, bgF64, diff);



    diffGray = Mat(diff.size(), CV_64FC1);
    cvtColor(diff, diffGray, CV_BGR2GRAY); // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Erstellung des Cannybildes">
    Canny(diffGray, cannyImage, 45.0f, 3.0f * 45.0f);
    dilate(cannyImage, cannyImage, kernel, Point(-1, -1), 2);
    erode(cannyImage, cannyImage, kernel, Point(-1, -1), 2); // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Finden der Kontouren und Approximation durch Polygone">
    findContours(cannyImage, contours0, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_TC89_L1, Point(0, 0));
    int accuracy = 4;
    /// Approximate Poygone to the found contour to repare holes
    bool closed = true;
    vector < vector<Point> > cont = vector < vector <Point> > (contours0.size());
    if (accuracy < 2) {
        accuracy = 2;
    }
    for (unsigned k = 0; k < contours0.size(); k++) {
        approxPolyDP(contours0[k], cont[k], accuracy, closed);
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Gefundene Kontourpunkte in einem Vektor zusammenfassen - Setzt voraus, dass nur das gesuchte Objekt im differenzbild zu sehen ist.">
    vector<Point> contour;
    for (vector < vector<Point> >::const_iterator root = cont.begin(); root != cont.end(); root++) {
        vector<Point> current = (*root);
        for (vector<Point>::const_iterator contX = current.begin(); contX != current.end(); contX++) {
            contour.push_back((*contX));
        }
    }// </editor-fold>

    // DBG("Got: %i contourpoints.", (int) contour.size());

    // <editor-fold defaultstate="collapsed" desc="Bestimmen des Rechtecks, welches das gefundene Objekt beinhaltet.">
    Point maxX, minX;
    Point maxY, minY;
    for (vector<Point>::const_iterator it = contour.begin(); it != contour.end(); it++) {
        Point pb = *it; //before
        Point p = *(it + 1); //current
        Point pn = *(it + 2); //next

        //DBG("Steigung zwischen letztem und nächsten Punkt: %f", MyMath::calcPitch(pb, pn));
        if (p.x <= cannyImage.size().width && p.x > 0) {
            if (maxX.x == 0 || p.x > maxX.x) {
                maxX = p;
            }
            if (minX.x == 0 || p.x < minX.x) {
                minX = p;
            }
            if (minY.y == 0 || p.y < minY.y) {
                minY = p;
            }
            if (maxY.y == 0 || p.y > maxY.y) {
                maxY = p;
            }
        }


    }

    //DBG("Extema: (%i/%i),(%i/%i),(%i/%i),(%i/%i)", minX.x, minX.y, maxX.x, maxX.y, minY.x, minY.y, maxY.x, maxY.y);


    ergC3 = Mat(cannyImage.size(), CV_64FC3);
    cvtColor(cannyImage, ergC3, CV_GRAY2BGR);

    Point x1, x2, x3, x4;
    x1 = Point(minX.x, minY.y);
    x2 = Point(maxX.x, minY.y);
    x4 = Point(minX.x, ((minY.y + MyMath::abs(minX.y - minY.y)*3) > ergC3.size().height) ? ergC3.size().height : (minY.y + MyMath::abs(minX.y - minY.y)*3));
    x3 = Point(maxX.x, ((minY.y + MyMath::abs(minX.y - minY.y)*3) > ergC3.size().height) ? ergC3.size().height : minY.y + MyMath::abs(minX.y - minY.y)*3);
    // </editor-fold>

    Point offset;
    int width, height;
    offset = x1;
    width = MyMath::abs(x2.x - x1.x);
    height = MyMath::abs(x4.y - x1.y);

    // <editor-fold defaultstate="collapsed" desc="Zeichnen der Gefundenen punkte, zur Pruefung.">
    line(inputImage, x1, x2, Scalar(255, 0, 0), 6);
    line(inputImage, x2, x3, Scalar(0, 255, 0), 6);
    line(inputImage, x3, x4, Scalar(0, 0, 255), 6);
    line(inputImage, x4, x1, Scalar(255, 255, 0), 6);
    circle(inputImage, x1, 20, Scalar(255, 0, 0), -1);
    circle(inputImage, x2, 20, Scalar(0, 255, 0), -1);
    circle(inputImage, x3, 20, Scalar(0, 0, 255), -1);
    circle(inputImage, x4, 20, Scalar(255, 255, 0), -1);
    // </editor-fold>
    String erg;
    erg = imgPath + " ";
    if (pos > 0) {
        erg += iToStr(pos) + " ";
    }
    erg += iToStr(offset.x) + " " + iToStr(offset.y) + " " + iToStr(width) + " " + iToStr(height);


    if (drawMarkedSamples) {
        imwrite(FileManager::getParentPath(currentOutputPath) + "Sample-" + FileManager::getFileName(imgPath) + "-" + iToStr(pos) + ".png", inputImage);
        //DBG("Markiertes Bild nach %s geschrieben.", String(FileManager::getParentPath(currentOutputPath) + "Sample-" + iToStr(pos) + ".png").c_str());
    }



    kernel.release();
    inputImage.release();
    backgroundImage.release();
    cannyImage.release();
    inputImgF64.release();
    bgF64.release();
    diff.release();
    diffGray.release();
    ergC3.release();
    contours0.clear();
    hierarchy.clear();
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
void PositiveSample::createImageInfo(vector<vector<String> > input, String output, vector<String> backgroundImagePath, bool createMarkedOutputFiles) {
    if (input.size() != backgroundImagePath.size()) {
        DBG("Falsche Grösse der Eingabe-Arrays: ist %i, soll %i", (int) backgroundImagePath.size(), (int) input.size());
    }

    drawMarkedSamples = createMarkedOutputFiles;
    int samplesPosition = 0;
    int imagesCounter = 1;
    Mat currentImage;
    ofstream outputStream;
    outputStream.open(output.c_str(), _Ios_Openmode::_S_out);
    currentOutputPath = output;
    CV_Assert(outputStream.is_open());
    for (vector<vector<String> >::iterator root = input.begin(); root != input.end(); root++) {
        currentBackgroundPath = backgroundImagePath[samplesPosition];
        for (vector<String>::iterator files = (*root).begin(); files != (*root).end(); files++) {
            currentImage = imread((*files));
            outputStream << createImageInfo(currentImage, (*files), imagesCounter);
            if (((files + 1)) != (*root).end()) {
                outputStream << endl;
            }
            imagesCounter++;
        }
        samplesPosition++;
    }
    outputStream.close();
    currentImage.release();
}

