/*
 * cvHelper.h
 *
 *  Created on: 07.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef CVHELPER_H_
#define CVHELPER_H_
#include "../header.h"

using namespace std;
using namespace cv;


//struct BufferPSNR
//// Optimized GPU versions
//{
//    // Data allocations are very expensive on GPU. Use a buffer to solve: allocate once reuse later.
//    gpu::GpuMat gI1, gI2, gs, t1, t2;
//};
//static gpu::GpuMat buf;

class CvHelper {
private:
    CvHelper();
    CvImageTypeMap imageTypeMap;
    String imageTypeToString(Mat img);
    static CvHelper *instance;

    /**
     * Zeichnet Text auf ein Bild
     * @param inputImg Das Bild
     * @param text Der Text
     * @param color Farbe des Textes
     * @param posX X-Offset des Textes
     * @param posY Y-Offset des Textes
     * @return das Eingabebild mit enthaltenem Text
     */
    Mat drawString(Mat inputImg, String text, Scalar color, int posX, int posY);
    BooleanArray initVector(BooleanArray vec, bool initValue);
public:
    virtual ~CvHelper();


    static CvHelper* getInstance();



    /**
     * Erstellt ein Bild, auf dem mehrere Bilder platziert werden
     * @param images Vektor von Bildern
     * @param imageTags Vektor von Beschriftungen
     * @param color Farbe des Textes
     * @param maxColumn Maximale Anzahl an Spalten
     * @param width Maximale Weite des Ergebnisbildes
     * @param height Maximale H&ouml;he des Ergebnisbildes
     * @return Ein Bild, das aus den Eingabebildern zusammengesetzt ist
     */
    virtual Mat buildImageGrid(vector<Mat*> images, CvStringArray imageTags, Scalar color, int maxColumn, int width, int height); //FIXME: Fehler erstellen des Grids!


    /**
     * Kopiert <code>roiImg</code> in einen kreisrunden Bereich innerhalb von <code>baseImg</code>, der durch <code>roi</code> gegeben ist
     * @param baseImg Das Bild, auf dem <code>roiImg</code> plaziert werden soll
     * @param roi Ort und Groesse des Bildausschnittes in das Kopiert wird
     * @param roiImg Das Bild, das auf dem Basisbild plaziert wird
     * @return Das ver&auml;nderte Basisbild
     */
    virtual Mat copyToCircularROI(Mat src, Rect roi, Mat roiImg);


    /**
     * Gibt Informationen &uuml;ber das Bild aus (Immo: Ma&szlig;e und Typ)
     * @param image
     */
    virtual void printImageInfo(Mat image);

    /**
     * Erkennt das gr&ouml;&szlig;te Objekt auf einem Bild
     * @param img das Bild
     * @param cascade Caascade
     * @return Ein Rect, das ein Erkanntes Objekt zur&uuml;ck einscklie&szlig;t, oder leer ist, falls kein Objekt gefunden wurde
     */
    virtual Rect detectBiggest(Mat& img, CascadeClassifier& cascade);

    /**
     * Erkennt alle Objekte auf einem Bild
     * @param img Das Bild
     * @param cascade Die cascade
     * @return einen Vektor von Rects, die die einzelnen erkannten Objekte einfassen
     */
    virtual vector<Rect> detectAll(Mat& img, CascadeClassifier& cascade);

    /**
     * Vertauscht bestimmte Regionen zweier Bilder miteinander
     * @param img1 Bild 1
     * @param img1_mask Eine Maske f&uuml;r Bild 1 mit der die Bereiche der Kopie angepasst werden k&ouml;nnen
     * @param face1 die zu kopierende Region von Bild 1
     * @param img2 Bild 1 
     * @param img2_mask Eine Maske f&uuml;r Bild 2 mit der die Bereiche der Kopie angepasst werden k&ouml;nnen
     * @param face2 die zu kopierende Region von Bild 2
     * @return einen Vector, der die Bilder mit den vertauschten Regionen enth&auml;lt, oder leer ist, falls ein Fehler aufgetreten ist.
     */
    virtual CvImageArray swapFaces(Mat img1, Mat img1_mask, Rect face1, Mat img2, Mat img2_mask, Rect face2);

    /**
     * Zeichnet die Konturen des Bildes
     * @param img Das Bild dessen Konturen gezeichnet werden
     */
    virtual Mat drawEdges(Mat img);

    virtual bool zero(Rect r);

    /**
     * Gau&szlig;scher Weichzeichner
     * @param input Eingabebild
     * @param size 
     * @param copy
     * @return 
     */
    virtual Mat gaussianBlur(Mat input, int size, bool copy = false);

    virtual Mat homgenousBlur(Mat input, int size, Point anchor, bool copy = false);

    virtual Mat median_Blur(Mat input, int size, bool copy = false);

    /**
     * Gibt die Id des Codecs zur&auml;ck 
     * @param codec String des Codecs z.b. "DIVX"
     * @return 
     */
    virtual int codecFromString(String codec);

    virtual Mat& scaleImage(Mat& img, const float scale);


    /**
     * Erstellt von einem beliebigen Bild ein Histgramm.
     * Dieses wird nicht direkt als Bild erstellt, sondern als MatND zurückgegeben, mit welchem weitere
     * Berechnungen durchgeführt werden können. Sofern ein Histogramm-Bild erzeugt werden soll,
     * bitte makeHistImage() mit der MatND, welche hier zurückgegeben wird, aufrufen!
     * 
     * ACHTUNG :: Sofern ein mehrkanaliges Bild übergeben wird, wird es zu seinem Graustufenbild umgewandelt und
     * von diesem dann das Histogramm berechnet!! :: ACHTUNG_ENDE
     * 
     * @param Mat* img Zeiger auf eine Mat-Instanz, von der Histogramm erstellt werden soll
     * @return MatND Matrix, mit den jeweiligen rel. Häufigkeiten für die einzelnen Grauton-Kanäle
     */
    MatND makeHist(Mat *img);

    /**
     * Erstellt ein sichtbares Histogramm-Bild von einer MatND Matrix, welche vorher von makeHist()
     * generiert wurde. Gibt das erstelte Bild als Mat zurück, welches ein normales Bild darstellt.
     * 
     * @param MatND& Referenz auf MatND Instanz, welches visualisert werden soll
     * @return Mat Histogramm-Bild als Mat-Instanz
     */
    Mat makeHistImage(MatND &hist);

    Mat applySurfDetect(Mat& refImg, Mat& ref, int hessian, int minDist, int maxDist);
    CvMatchesArray findSurfMatches(Mat& refImg, Mat& ref, int hessian, int minDist, int maxDist);
    CvKeyPointArray findKeyPoints(Mat& img, int hessian);
    MatND makeHSHist(Mat& mat);
    Mat makeHSHistImage(MatND &hist);
    /**
     * F&uuml;hrt eine Histogram Angleichung durch. Die Helligkeit wird normalisiert und der Kontrast erh&ouml;t.
     * @param img Das Eingabebild.
     * @param convertRGB Gibt an, ob das Ausgabebild zu RGB convertiert werden soll.
     * @param inputIsBGR Gibt an, ob das Bild den BGR Farbraum verwendet. Default ist <code>true</code>.
     * @return Ein in Helligkeit normalisiertes und in Kontrast erh&ouml;tes Bild.
     */
    Mat equalizeHistogram(Mat& img, bool convertback, bool inputIsBGR = true);

    /**
     * Vergleicht zwei Histogramme.
     * @param hist1 
     * @param hist2
     * @param m Die Vergleichsmethode die verwendet wird. -> CV_COMP_*
     * @return Ein <code>double</code>, das angibt, wie &auml;hnlich sich die Histogramme sind.
     */
    double compareHistogram(MatND& hist1, MatND& hist2, int method = CV_COMP_BHATTACHARYYA);


    /**
     * Akkumuliert eine Bildfolge
     * @param mat eine Bildfolge
     * @return Das Akkumulierte Bild
     */
    Mat accumulateImages(CvImageArray mat);

    /**
     * Enfernt den Hintergrund eines Bildes mithilfe eines Kallibrierungsbiles(Bildfolge)
     * @param bg der Hintergrund ohne Objekt
     * @param img Das Bild mit Objekt
     * @return Ein Bild mit geschw&auml;rztem Hintergrund.
     */
    Mat removeBackground(CvImageArray bg, Mat img);

    Mat convertBlackAndWhite(Mat& in, int threshold);

    /**
     * Erstellt eine Lokale-H&auml;figkeitsverteilung einer Punktmenge, bezogen auf X oder Y Werte.
     * @param points Eine Menge von Punkten
     * @param imageWidth Weite des Bildes auf dem die Punkte der Menge angesiedelt sind.
     * @param imageHeight H&ouml;he des Bildes auf dem die Punkte der Menge angesiedelt sind.
     * @param histogramBins 'B&auml;nder' des Histograms.<br> Muss Teiler von <code>imageWidth</code> sein, falls <code>direction == DIRECTION_X</code> 
     *                       oder Teiler von <code>imageHeight</code>, falls <code>direction == DIRECTION_Y</code>.
     * @param direction Betrachtungsrichtung. Falls <code>direction == DIRECTION_X</code> werden nur die X-Werte der Punkte in das Histogram einflie&szlig;en.
     * @return Einen Vektor von Vektoren von Punkten. F&uuml;r jedes Band existiert ein Vektor von Punkten, seine L&auml;nge gibt Aufschluss &uuml;ber die Anzahl der Punkte in diesem (&Ouml;rtlichen)-Bereich.
     */
    PointHistogram createPositionHistogram(PointArray points, int imageWidth, int imageHeight, int histogramBins, POSITION_HISTOGRAM_DIRECTION direction = DIRECTION_X);

    /**
     * Entfernt isolierte Punkte aus einem Punktehistogram.
     * @param hist Das Histogram.
     * @param isolationBins Anazahl der B&auml;nder, die in einer Umgebung eines Punktes leer sein m&uuml;ssen, damit der Punkt als isoliert angesehen wird.
     * @return Das Punktehistogram, in dem isolierte Punkte entfernt wurden
     */
    PointHistogram removeIsolatedPoints(PointHistogram hist, int isolationBins);

    /**
     * Filtert ein Punktehistogram. 
     * @param hist Das Punktehistogram.
     * @param fromBin Alle Punkte, die &ouml;rtlich vor diesem Band angesiedelt sind, werden entfernt.
     * @param toBin Alle Punkte, die &ouml;rtlich nach diesem Band angesiedelt sind, werden entfernt.
     * @return Ein Punktehistogram, in dem nur noch die B&auml;nder zweichen <code>fromBin</code> und <code>toBin</code> belegt sind.
     */
    PointHistogram filterPositionHistogramRange(PointHistogram hist, int fromBin, int toBin);


    /**
     * Erstellt aus einem Punktehistogram (Vektor von Vektoren von Punkten) wieder eine Punktmenge (Vektor von Punkten).
     * @param hist Das Punktehistogram.
     * @return Einen Vector von Punkten.
     */
    PointArray retransformPositionHistogram(PointHistogram hist); //FIXME:  Implementieren.

    

    double checkEquality(const Mat& I1, const Mat& I2);


    Scalar checkStructuralEquality(const Mat& i1, const Mat& i2);

    /**
     * Entfernt alle Punkte aus dem Histogram, welche in einem Band liegen, in denem nicht mehr als <code>minLength</code> Punkte liegen.
     * @param hist Das Histogram.
     * @param minLength Minimale Anzahl an Punkten, die in einem Band liegen sollen.
     * @return Ein neues Histogram, in dem die besetzten B&auml;nder mindestens eine L&auml;nge von <code>minLength</code> haben.
     */
    PointHistogram extractNoticableBins(PointHistogram hist, int minLength);

    //FIXME: BACKPROJEKTION:
    //calcBackProject( &hs, 1, 2, hist, backproj, &ranges, 1, true );
}; // Bilder anhand der Histogramme vergleichen: compareHist()






#endif /* CVHELPER_H_ */
