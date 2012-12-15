/*
 * cvHelper.h
 *
 *  Created on: 07.11.2012
 *      Author: Nils Frenking, Julian Cordes
 */

#ifndef CVHELPER_H_
#define CVHELPER_H_

using namespace std;
using namespace cv;

class CvHelper {
private:
    CvHelper();
    map<int, String> imageTypeMap;
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
    virtual Mat buildImageGrid(vector<Mat*> images, vector<String> imageTags, Scalar color, int maxColumn, int width, int height);


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
    virtual vector<Mat> swapFaces(Mat img1, Mat img1_mask, Rect face1, Mat img2, Mat img2_mask, Rect face2);

    /**
     * Zeichnet die Konturen des Bildes
     * @param img Das Bild dessen Konturen gezeichnet werden
     */
    virtual Mat drawEdges(Mat img);

    virtual bool zero(Rect r);

    
    virtual Mat gaussianBlur(Mat input,int size,bool copy=false);

    virtual Mat homgenousBlur(Mat input, int size,Point anchor, bool copy=false);
    
    virtual Mat median_Blur(Mat input, int size, bool copy=false);
    
    /**
     * Gibt die Id des Codecs zur&auml;ck 
     * @param codec String des Codecs z.b. "DIVX"
     * @return 
     */
    virtual int codecFromString(String codec);
    
    virtual Mat& scaleImage(Mat& img,const float scale);
    
    
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
    
};





#endif /* CVHELPER_H_ */
