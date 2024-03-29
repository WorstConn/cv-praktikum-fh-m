/* 
 * File:   FourFingersPositveSample.cpp
 * Author: Julian Cordes, Nils Frenking
 * 
 * Created on 22. Januar 2013, 00:25
 */

#include "../header.h"

using namespace std;
using namespace cv;

FourFingersPositveSample::FourFingersPositveSample() {
}

FourFingersPositveSample::FourFingersPositveSample(const FourFingersPositveSample& orig) : CreationBehavior(orig) {
}

FourFingersPositveSample::~FourFingersPositveSample() {
}

String FourFingersPositveSample::createImageInfo(Mat& img, String imgPath, int pos) {

    // <editor-fold defaultstate="collapsed" desc="Vorbedingungen Pruefen.">
    if (img.empty()) {
        DBG("Kein Bild!");
        return "ERROR";
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Deklarationen">
    Mat kernel = Mat::ones(3, 3, CV_8U);
    Mat inputImage = img;
    if (!usePresegmentedData) {
        if (backgroundImage.empty()) {
            backgroundImage = imread(currentBackgroundPath); //FIXME: nur einmal einlesen...
        }
    }
    Mat cannyImage;
    Mat inputImgF64;
    Mat bgF64;
    Mat diff;
    Mat diffGray;
    Mat ergC3;
    ContourArray contours0;
    vector<Vec4i> hierarchy;

    // </editor-fold>

    if (usePresegmentedData) {
        // <editor-fold defaultstate="collapsed" desc="Konversion der Eingabebilder">
        inputImgF64 = Mat(inputImage.size(), CV_64FC3);
        inputImage.copyTo(inputImgF64);



        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Graustufen-Konversion">

        diffGray = Mat(diff.size(), CV_64FC1);
        cvtColor(inputImgF64, diffGray, CV_BGR2GRAY);
        // </editor-fold>
    } else {
        // <editor-fold defaultstate="collapsed" desc="Konversion der Eingabebilder">
        inputImgF64 = Mat(inputImage.size(), CV_64FC3);
        inputImage.copyTo(inputImgF64);

        bgF64 = Mat(backgroundImage.size(), CV_64FC3);
        backgroundImage.copyTo(bgF64);

        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Erstellung eines Differenzbildes">
        diff = Mat::zeros(bgF64.size(), CV_64FC3);
        absdiff(inputImgF64, bgF64, diff);
        diffGray = Mat(diff.size(), CV_64FC1);
        cvtColor(diff, diffGray, CV_BGR2GRAY);
        // </editor-fold>
    }


    // Untere Grenze muss evtl. an Gegebenheiten angepasst werden, um eine 'gute' Maske zu erhalten.
    threshold(diffGray, diffGray, 25, 255, CV_THRESH_BINARY);

    // <editor-fold defaultstate="collapsed" desc="Erstellung des Cannybildes">
    Canny(diffGray, cannyImage, 45.0f, 3.0f * 45.0f);
    dilate(cannyImage, cannyImage, kernel, Point(-1, -1), 2);
    erode(cannyImage, cannyImage, kernel, Point(-1, -1), 2);
    // </editor-fold>

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

    // <editor-fold defaultstate="collapsed" desc="Wenn DEBUG definiert ist, Zeige ein Bild mit allen Kontourpunkten, dem Polygonen und der konvexen Huelle des Objektes an.">
#if DEBUG
    ContourArray hull(1);

    convexHull(Mat(contour), hull[0], false);


    Mat drawing = img.clone(); //Mat::zeros(cannyImage.size(), CV_8UC3);
    //ContourArray cont_conv_test(1);
    cont[0] = contour;
    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    drawContours(drawing, cont, 0, color, 1, 8, vector<Vec4i > (), 0, Point());
    drawContours(drawing, hull, 0, color, 1, 8, vector<Vec4i > (), 0, Point());
    //    int count = 3;
    //    for (vector<Point>::iterator iter = hull[0].begin(); iter != hull[0].end(); iter++) {
    //        circle(drawing, (*iter), count++, color, -1);
    //    }
    float fcounter = 7.0f;
    color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    for (vector<Point>::iterator iter = contour.begin(); iter != contour.end(); iter++) {
        circle(drawing, (*iter), (int) fcounter, color, -1);
        circle(inputImage, (*iter), (int) fcounter, color, -1);

    }

    /// Show in a window

    imshow("Sample-Creation", drawing);

    waitKey(25);
#endif
    // </editor-fold>

    PointHistogram hist = PointHistogram();
    CvHelper* helper = CvHelper::getInstance();
    hist = helper->createPositionHistogram(contour, img.size().width, img.size().height, 40, DIRECTION_X);
    hist = helper->removeIsolatedPoints(hist, 2);
    contour = helper->retransformPositionHistogram(hist);

    // <editor-fold defaultstate="collapsed" desc="Bestimmen des Rechtecks, welches das gefundene Objekt beinhaltet.">
    Point maxX, minX;
    Point maxY, minY;
    int imageWidth = cannyImage.size().width;
    for (vector<Point>::const_iterator it = contour.begin(); it != contour.end(); it++) {
        //        Point pb = *(it); //last
        //        Point p = *(it + 1); //current
        //        Point pn = *(it + 2); //next
        Point p = *(it); //current
        //DBG("Steigung zwischen letztem und nächsten Punkt: %f", MyMath::calcPitch(pb, pn));

        if (p.x <= imageWidth && p.x > 0) {
            if (maxX.x == 0 || p.x > maxX.x) {
                if ((((float) p.y) / ((float) inputImgF64.size().height)) < 0.90f) {
                    maxX = p;
                }
            }
            if (minX.x == 0 || p.x < minX.x) {
                if ((((float) p.y) / ((float) inputImgF64.size().height)) < 0.90f) {
                    minX = p;
                }

            }
            if (minY.y == 0 || p.y < minY.y) {
                if ((((float) p.y) / ((float) inputImgF64.size().height)) < 0.90f) {
                    minY = p;
                }

            }
            if (maxY.y == 0 || p.y > maxY.y) {
                if ((((float) p.y) / ((float) inputImgF64.size().height)) < 0.90f) {
                    maxY = p;
                }

            }
        }


    }

    //DBG("Extema: (%i/%i),(%i/%i),(%i/%i),(%i/%i)", minX.x, minX.y, maxX.x, maxX.y, minY.x, minY.y, maxY.x, maxY.y);


    ergC3 = Mat(cannyImage.size(), CV_64FC3);
    cvtColor(cannyImage, ergC3, CV_GRAY2BGR);

    Point x1, x2, x3, x4;
    x1 = Point(minX.x, minY.y);
    x2 = Point(maxX.x, minY.y);
    int tmpW = MyMath::abs(maxX.x - minX.x);
    int tmpY = 0;
    if ((minX.y - minY.y) < static_cast<int> (((float) tmpW)*0.60f) and (maxX.y - minY.y) < static_cast<int> (((float) tmpW)*0.60f)) {
        tmpY = static_cast<int> (((float) tmpW)*1.75f);
    } else if ((minX.y - minY.y) >= static_cast<int> (((float) tmpW)*0.85f)) {
        tmpY = static_cast<int> (((float) tmpW)*1.75f);
    } else if ((maxX.y - minY.y) >= static_cast<int> (((float) tmpW)*0.85f)) {
        tmpY = static_cast<int> (((float) tmpW)*1.75f);
    } else {
        tmpY = static_cast<int>(((float)tmpW)*1.09f);
    }



    tmpY += minY.y;

    if (tmpY > img.size().height) {
        tmpY = img.size().height;
    }
    x4 = Point(minX.x, tmpY);
    x3 = Point(maxX.x, tmpY);

    // </editor-fold>


    // <editor-fold defaultstate="collapsed" desc="Zeichnen der Gefundenen punkte, zur Pruefung.">
    line(inputImage, x1, x2, Scalar(255, 0, 0), 6);
    line(inputImage, x2, x3, Scalar(0, 255, 0), 6);
    line(inputImage, x3, x4, Scalar(0, 0, 255), 6);
    line(inputImage, x4, x1, Scalar(255, 255, 0), 6);
    // </editor-fold>

    Point offset;
    int width, height;
    offset = x1;
    width = MyMath::abs(x2.x - x1.x);
    height = MyMath::abs(x4.y - x1.y);
    String erg;
    erg = imgPath + " ";
    if (pos > 0) {
        erg += iToStr(1) + " ";
    }
    erg += iToStr(offset.x) + " " + iToStr(offset.y) + " " + iToStr(width) + " " + iToStr(height);
    width = MyMath::abs(x2.x - x1.x);
    height = MyMath::abs(x4.y - x1.y);
    if (height <= 0 or width <= 0) {
        DBG("Vermutlich nicht erfolgreiche Erkennung. Weite %i und Hoehe %i des Erkannten Rechtecks", width, height);
        erg = "Error: " + imgPath;
    } else {

        if (drawMarkedSamples) {
            imwrite(FileManager::getParentPath(currentOutputPath) + "Sample-" + FileManager::getFileName(imgPath) + "-" + iToStr(pos) + ".png", inputImage);
        }
    }

    // <editor-fold defaultstate="collapsed" desc="Aufraeumen">
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
    // </editor-fold>

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
void FourFingersPositveSample::createImageInfo(ArrayOfStringArrays input, String output, StringArray backgroundImagePath, bool createMarkedOutputFiles, bool presegmentedData) {
    usePresegmentedData = presegmentedData;
    if (!usePresegmentedData) {

        if (input.size() != backgroundImagePath.size()) {
            DBG("Falsche Grösse der Eingabe-Arrays: ist %i, soll %i", (int) backgroundImagePath.size(), (int) input.size());
        }
    }
    /* Wenn wir uns im Debugmodus befinden, Zeichne doch bitte die markierten Bilder zur Pruefung*/
#if DEBUG
    drawMarkedSamples = true;
#else
    drawMarkedSamples = createMarkedOutputFiles;
#endif


    int samplesPosition = 0;
    int imagesCounter = 1;
    Mat currentImage;
    ofstream outputStream;
    outputStream.open(output.c_str(), _Ios_Openmode::_S_out);
    currentOutputPath = output;
    CV_Assert(outputStream.is_open());

#if DEBUG
    DBG("Erstelle Fenster");
    namedWindow("Sample-Creation", CV_WINDOW_AUTOSIZE);
#endif

    for (ArrayOfStringArrays::iterator root = input.begin(); root != input.end(); root++) {
        if (!usePresegmentedData) {
            currentBackgroundPath = backgroundImagePath[samplesPosition];
        }
        for (StringArray::iterator files = (*root).begin(); files != (*root).end(); files++) {
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
