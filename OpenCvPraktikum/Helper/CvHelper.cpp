/*
 * cvHelper.cpp
 *
 *  Created on: 07.11.2012
 *  Modified by: Nils Frenking, Julian Cordes
 */



#include "../header.h"
using namespace std;
using namespace cv;

CvHelper* CvHelper::instance = NULL;

/**
 * Zeichnet Text auf ein Bild
 * @param inputImg Das Bild
 * @param text Der Text
 * @param color Farbe des Textes
 * @param posX X-Offset des Textes
 * @param posY Y-Offset des Textes
 * @return das Eingabebild mit enthaltenem Text
 */
Mat CvHelper::drawString(Mat inputImg, String text, Scalar color, int posX, int posY) {
    /**
     * Text platzieren
     */
    if (posX < 0 or posY < 0) {
        posX = 0;
        posY = 0;
    }
    if (posX > inputImg.cols) {
        posX = 0;
    }
    if (posY > inputImg.rows) {
        posY = 0;
    }

    putText(inputImg, text, Point(posX, posY), CV_FONT_NORMAL, 1.0, color, 2, 0, false);
    return inputImg;
}

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
Mat CvHelper::buildImageGrid(vector<Mat*> images, StringArray imageTags, Scalar color, int maxColumn, int width, int height) {

    int rahmenbreite = 5; //Abstand zwischen den Bildern
    Mat grid = Mat(width, height, CV_8UC3);

    if (imageTags.empty()) {
        cout << "Keine Tags vorhanden" << endl;
        return Mat(grid);
    }

    if (images.size() != imageTags.size()) {
        cout << "Keine Tags vorhanden" << endl;
        return Mat(grid);
    }

    int rows;
    int column;
    if (images.size() % maxColumn == 0) {
        column = maxColumn;
        rows = images.size() / column;
    } else if (maxColumn <= 3) {
        column = maxColumn;
        if (images.size() % column == 0) {
            rows = images.size() / column;
        } else {
            rows = (images.size() / column) + 1;
        }
    } else {
        column = maxColumn;
        for (; images.size() % column != 0; column--) {
            ;
        }
        rows = images.size() / column;
    }
    int w = (width - (column * rahmenbreite)) / (column);
    int h = (height - (rows * rahmenbreite)) / rows;
    int gridWidth;
    int gridHeight;
    gridHeight = h * rows + h * rahmenbreite;
    gridWidth = w * column + column * rahmenbreite;
    grid = Mat(gridHeight, gridWidth, CV_8UC3);



    Rect roi;
    /*
     * Bildbereich der ROI
     */
    Mat roiImg;
    Mat currImg;
    int pos = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < column; j++) {
            if (((int) images.size()) <= pos) {
                DBG("Zu wenige Bilder");
                break;
            }

            currImg = (*images.at(pos));

            if (images.at(pos)->type() == CV_8UC3) {
                images[i]->copyTo((currImg));



            } else if (images.at(pos)->type() == CV_8UC1) {
                cvtColor((*images.at(pos)), (currImg), CV_GRAY2RGB);




            }

            roi = Rect(j * w + j * rahmenbreite, i * h + i * rahmenbreite, w, h);
            roiImg = Mat(Size(roi.width, roi.height), images.at(pos)->type());


            resize(currImg, roiImg, Size(roi.width, roi.height), 0, 0, 0);
            drawString(roiImg, imageTags[pos], color, 5, roi.height - 5);

            roiImg.copyTo(grid(roi));

            roiImg.release();
            currImg.release();
            pos++;
        }
    }
    images.clear();
    return Mat(grid);
}

CvHelper::CvHelper() {
    imageTypeMap = ImageTypeMap();

}

CvHelper* CvHelper::getInstance() {
    if (instance == NULL) {
        instance = new CvHelper();

    }

    return instance;

}

/**
 * Zeichnet die Konturen des Bildes
 * @param img Das Bild dessen Konturen gezeichnet werden
 */
Mat CvHelper::drawEdges(Mat img) {
    Mat src;
    Mat src_gray;
    int thresh = 400;

    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /*
     * Ein wenig verwischen...
     */
    blur(img, src_gray, Size(3, 3));



    /*
     * Cannybild erstellen
     */
    Canny(src_gray, canny_output, thresh, thresh * 3, 5);
    /// Finde Konturen
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_TC89_L1, Point(0, 0));

    /// Zeichne Konturen
    Scalar color = Scalar(255, 255, 255, 0);
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (unsigned int i = 0; i < contours.size(); i++) {

        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 5, Point());
    }

    /// Show in a window
    namedWindow("Contours", CV_WINDOW_AUTOSIZE);
    imshow("Contours", drawing);
    return drawing;
}

CvHelper::~CvHelper() {

}

/**
 * Kopiert <code>roiImg</code> in einen kreisrunden Bereich innerhalb von <code>baseImg</code>, der durch <code>roi</code> gegeben ist
 * @param baseImg Das Bild, auf dem <code>roiImg</code> plaziert werden soll
 * @param roi Ort und Groesse des Bildausschnittes in das Kopiert wird
 * @param roiImg Das Bild, das auf dem Basisbild plaziert wird
 * @return Das ver&auml;nderte Basisbild
 */
Mat CvHelper::copyToCircularROI(Mat inputImg, Rect roi, Mat roiImg) {
    Mat erg = Mat(Size(inputImg.cols, inputImg.rows), CV_8UC3);
    inputImg.copyTo(erg);
    Mat baseRoi = erg(roi);


    for (int i = 0; i < baseRoi.rows; i++) {
        for (int j = 0; j < baseRoi.cols; j++) {
            if (MyMath::isInCircle(Point2i((int) ((float) baseRoi.cols)*0.5, (int) ((float) baseRoi.rows)*0.5), MyMath::RectRadius(roi), Point(j, i))) {
                baseRoi.data[baseRoi.step[0] * i + baseRoi.step[1] * j + 0] = roiImg.data[roiImg.step[0] * i + roiImg.step[1] * j + 0];
                baseRoi.data[baseRoi.step[0] * i + baseRoi.step[1] * j + 1] = roiImg.data[roiImg.step[0] * i + roiImg.step[1] * j + 1];
                baseRoi.data[baseRoi.step[0] * i + baseRoi.step[1] * j + 2] = roiImg.data[roiImg.step[0] * i + roiImg.step[1] * j + 2];
            }
        }
    }

    return erg;
}

/**
 * Gibt Informationen &uuml;ber das Bild aus (Immo: Ma&szlig;e und Typ)
 * @param image
 */
void CvHelper::printImageInfo(Mat image) {
    if (image.data == NULL) {
        DBG("Keine Daten");
        return;
    }
    cout << "Pixel: " << image.cols << "x" << image.rows << endl;

    cout << "Type: " << imageTypeToString(image) << endl;
    cout << "Step " << image.step << endl;














}

String CvHelper::imageTypeToString(Mat img) {


    if (imageTypeMap.empty()) {

        // <editor-fold defaultstate="collapsed" desc="Einmaliges Erstellen der Map-Eintraege.">
        imageTypeMap.insert(std::make_pair<int, String > (CV_8U, "CV_8U"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_8UC1, "CV_8UC1"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_8UC2, "CV_8UC2"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_8UC3, "CV_8UC3"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_8UC4, "CV_8UC4"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_8S, "CV_8S"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_8SC1, "CV_8SC1"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_8SC2, "CV_8SC2"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_8SC3, "CV_8SC3"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_8SC4, "CV_8SC4"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_16U, "CV_16U"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_16UC1, "CV_16UC1"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_16UC2, "CV_16UC2"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_16UC3, "CV_16UC3"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_16UC4, "CV_16UC4"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_16S, "CV_16S"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_16SC1, "CV_16SC1"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_16SC2, "CV_16SC2"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_16SC3, "CV_16SC3"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_16SC4, "CV_16SC4"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_32S, "CV_32S"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_32SC1, "CV_32SC1"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_32SC2, "CV_32SC2"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_32SC3, "CV_32SC3"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_32SC4, "CV_32SC4"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_32F, "CV_32F"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_32FC1, "CV_32FC1"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_32FC2, "CV_32FC2"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_32FC3, "CV_32FC3"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_32FC4, "CV_32FC4"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_64F, "CV_64F"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_64FC1, "CV_64FC1"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_64FC2, "CV_64FC2"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_64FC3, "CV_64FC3"));
        imageTypeMap.insert(std::make_pair<int, String > (CV_64FC4, "CV_64FC4"));
        // </editor-fold>


    }

    ImageTypeMap::iterator iter;

    iter = imageTypeMap.find(img.type());

    if (iter == imageTypeMap.end()) {
        return "Unbekannter Bildtyp!";
    } else {
        return iter->second;
    }


}

/**
 * Erkennt das gr&ouml;&szlig;te Objekt auf einem Bild
 * @param img das Bild
 * @param cascade Caascade
 * @return Ein Rect, das ein Erkanntes Objekt zur&uuml;ck einscklie&szlig;t, oder leer ist, falls kein Objekt gefunden wurde
 */
Rect CvHelper::detectBiggest(Mat& img, CascadeClassifier& cascade) {
    RectangleArray faces = RectangleArray();
    const static Scalar color = CV_RGB(0, 0, 255);
    Mat gray;
    Mat smallImg(cvRound(img.rows), cvRound(img.cols), CV_8UC1);


    cvtColor(img, gray, CV_BGR2GRAY);
    resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
    equalizeHist(smallImg, smallImg);
    cascade.detectMultiScale(smallImg, faces, 1.3, 3, 0, Size(100, 100));


    if (faces.empty()) {
        return Rect();
    }
    int biggest = 0;
    Rect faceRect = Rect();

    for (unsigned int i = 0; i < faces.size(); i++) {
        try {
            if (biggest == 0 or zero(faceRect) or MyMath::biggerThan(faces.at(i), faceRect)) {

                faceRect = Rect(faces.at(i));
                if (faceRect.width > 100) {
                    if (faceRect.height > 100) {
                        break;
                    }
                }
            }

        } catch (Exception& err) {
            cout << err.msg << endl;
        }

    }

    faces.clear();

    if (!zero(faceRect)) {
        Point center;
        int radius;

        center.x = cvRound((faceRect.x + faceRect.width * 0.5));
        center.y = cvRound((faceRect.y + faceRect.height * 0.5));
        radius = cvRound((faceRect.width + faceRect.height)*0.25);

        /*
         * Ist das erkannte Gesicht zu klein (radius kleiner gleich 10% der Bildbreite)
         */
        if (radius <= cvRound(((float) img.cols)*0.1)) {
            return Rect();
        }

        circle(img, center, radius, color, 2, 8, 0);

        return faceRect;
    } else {
        return Rect();
    }

}

/**
 * Erkennt alle Objekte auf einem Bild
 * @param img Das Bild
 * @param cascade Die cascade
 * @return einen Vektor von Rects, die die einzelnen erkannten Objekte einfassen
 */
RectangleArray CvHelper::detectAll(Mat& img, CascadeClassifier& cascade, int minWidth, float maxWidth, float aspectRatio) {

    RectangleArray objects = RectangleArray();
    Mat gray;
    Mat smallImg(cvRound(img.rows), cvRound(img.cols), CV_8UC1);

    cvtColor(img, gray, CV_BGR2GRAY);
    resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
    equalizeHist(smallImg, smallImg);
    cascade.detectMultiScale(smallImg, objects, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(64, 64));
    DBG("%i Hände gefunden.", (int) objects.size());

    return objects;

}

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
ImageArray CvHelper::swapFaces(Mat img1, Mat img1_mask, Rect face1, Mat img2, Mat img2_mask, Rect face2) {

    if (img1.data == NULL || img2.data == NULL) {
        cout << "Keine Bilder zum vertauschen angegeben" << endl;
        return ImageArray();
    }
    Mat img1Roi = Mat(Size(face2.width, face2.height), CV_8UC3);
    Mat img2Roi = Mat(Size(face1.width, face1.height), CV_8UC3);



    if (img1_mask.data != NULL && img2_mask.data != NULL) {
        cerr << "Sorry, nocht nicht implementiert..." << endl << "Bitte so lange nocht swapFaces ohne Maskenbilder aufrufen" << endl;
        return ImageArray();
        /*
         * Masken leider noch nicht beruecksichtigt         
         */

        //        tmp1 = img1_mask bitor img1;

        //        img1Roi = img2_mask bitand img1Roi;
        resize(img1(face1), img1Roi, Size(face2.width, face2.height), 0, 0);
        resize(img2(face2), img2Roi, Size(face1.width, face1.height), 0, 0);



    } else {
        /*
         * Groesse der gesichter anpassen
         */
        resize(img1(face1), img1Roi, Size(face2.width, face2.height), 0, 0);
        resize(img2(face2), img2Roi, Size(face1.width, face1.height), 0, 0);

        /*
         * Gesicht von Bild 1 auf Bild 2 Kopieren und umgekehrt
         */
        img2 = copyToCircularROI(img2, face2, img1Roi);

        img1 = copyToCircularROI(img1, face1, img2Roi);


        if (img2.data == NULL or img1.data == NULL) {

            return ImageArray();

        }

    }
    ImageArray erg = ImageArray();
    erg.push_back(img1);
    erg.push_back(img2);
    return erg;

}

bool CvHelper::zero(Rect r) {
    return (r.width == 0 && r.height == 0 && r.x == 0 && r.y == 0);
}

Mat CvHelper::gaussianBlur(Mat input, int size, bool copy) {
    if (copy) {
        Mat erg = Mat(input.rows, input.cols, input.type());
        GaussianBlur(input, erg, Size(size, size), 0.0, 0.0);
        return erg;
    } else {
        GaussianBlur(input, input, Size(size, size), 0.0, 0.0);
        return input;
    }

}

Mat CvHelper::homgenousBlur(Mat input, int size, Point anchor, bool copy) {
    if (copy) {
        Mat erg = Mat(input.rows, input.cols, input.type());
        blur(input, erg, Size(size, size), anchor);
        return erg;

    } else {
        blur(input, input, Size(size, size), anchor);
        return input;
    }
}

Mat CvHelper::median_Blur(Mat input, int size, bool copy) {
    if (copy) {
        Mat erg = Mat(input.rows, input.cols, input.type());
        medianBlur(input, erg, size);

        return erg;
    } else {
        medianBlur(input, input, size);
        return input;
    }
}

int CvHelper::codecFromString(String codec) {
    if (codec.length() != 4) {
        DBG("Falsche länge: %i", (int) codec.length());
        return -2;
    }
    //FIXME: not well implemented yet.
    return CODEC_DEFAULT;


}

Mat& CvHelper::scaleImage(Mat& img, const float scale) {
    if (img.data == NULL) {
        DBG("Image hat keine Daten");
        return img;
    }

    Mat scaled = Mat::zeros(Size(((int) ((float) img.size().width) * scale), ((int) ((float) img.size().height) * scale)), img.type()); //Mat(Size(((int)((float)img.size().width)*scale),((int)((float)img.size().height)*scale)), img.type());

    resize(img, scaled, scaled.size(), 0, 0, INTER_LINEAR);

    img = scaled;
    return img;
}

MatND CvHelper::makeHist(Mat *leImg) {

    MatND hist;

    cv::Mat greyMat = Mat(leImg->size(), CV_8UC1);

    Mat *img = new Mat(leImg->size(), leImg->type());

    leImg->copyTo((*img));
    if (img->channels() != 1) { // Wenn mehrkanaliges Bild vorliegt, dieses in Grautonbild umwandeln und von diesem Histogram erstellen

        cv::cvtColor(*img, greyMat, CV_BGR2GRAY);
        DBG("Habe Img mit %d Kanälen als Grautonbild umgewandelt!", leImg->channels());
        img = &greyMat;

    }

    int histSize[1];
    int channels[1];
    float hranges[2];
    const float *ranges[1];

    histSize[0] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    channels[0] = 0;

    calcHist(img, // image to make hist from
            1, // histogram from 1 image
            channels, // the channels used
            Mat(), // no mask used
            hist, // the resulting histogram
            1, // 1D histogram
            histSize, // number of bins
            ranges // pixel value range
            );

    return hist;

}

Mat CvHelper::makeHistImage(MatND &hist) {
    double minVal, maxVal;
    int histSize[1];
    int hpt;

    histSize[0] = 256;
    minVal = 0;
    maxVal = 0;

    minMaxLoc(hist, &minVal, &maxVal, 0, 0);

    Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));

    hpt = static_cast<int> (0.9 * histSize[0]);

    DBG("minVal = %f, maxVal =%f ", minVal, maxVal);
    float binVal;
    int intensity;
    for (int h = 0; h < histSize[0]; h++) {
        binVal = hist.at<float>(h);
        intensity = static_cast<int> (binVal * ((float) hpt / maxVal));

        line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));

    }

    return histImg;


}

/**
 * Histogram
 * int main( int argc, char** argv )
{
    Mat src, hsv;
    if( argc != 2 || !(src=imread(argv[1], 1)).data )
        return -1;

    cvtColor(src, hsv, CV_BGR2HSV);

    // Quantize the hue to 30 levels
    // and the saturation to 32 levels
    int hbins = 30, sbins = 32;
    int histSize[] = {hbins, sbins};
    // hue varies from 0 to 179, see cvtColor
    float hranges[] = { 0, 180 };
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0, 1};

    calcHist( &hsv, 1, channels, Mat(), // do not use mask
             hist, 2, histSize, ranges,
             true, // the histogram is uniform
             false );
    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 10;
    Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

    for( int h = 0; h < hbins; h++ )
        for( int s = 0; s < sbins; s++ )
        {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal*255/maxVal);
            rectangle( histImg, Point(h*scale, s*scale),
                        Point( (h+1)*scale - 1, (s+1)*scale - 1),
                        Scalar::all(intensity),
                        CV_FILLED );
        }

    namedWindow( "Source", 1 );
    imshow( "Source", src );

    namedWindow( "H-S Histogram", 1 );
    imshow( "H-S Histogram", histImg );
    waitKey();
}
 */

Mat CvHelper::applySurfDetect(Mat& refImg, Mat& ref, int hessian, int minDist, int maxDist) {
    KeyPointArray refImgKeyPoints = findKeyPoints(refImg, hessian);
    KeyPointArray refKeyPoints = findKeyPoints(ref, hessian);
    if (refImgKeyPoints.size() == 0 or refKeyPoints.size() == 0) {
        DBG("Keine Keypoints gefunden. Leeres Bild?");
        return Mat();
    }
    DBG("KeyPoints gefunden, %d,%d", (int) refImgKeyPoints.size(), (int) refKeyPoints.size());

    MatchesArray goodMatches = findSurfMatches(refImg, ref, hessian, minDist, maxDist);

    //-- Draw only "good" matches
    Mat matchesImg;
#ifdef DEBUG
    drawMatches(refImg, refImgKeyPoints, ref, refKeyPoints,
            goodMatches, matchesImg, Scalar::all(-1), Scalar::all(-1),
            vector<char>(), DrawMatchesFlags::DEFAULT bitor DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS bitor DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    DBG("Show detected matches");
    imshow("Good Matches", matchesImg);
#endif

    return matchesImg;

}

MatchesArray CvHelper::findSurfMatches(Mat& refImg, Mat& ref, int hessian, int minDist, int maxDist) {
    KeyPointArray refImgKeyPoints = findKeyPoints(refImg, hessian);
    KeyPointArray refKeyPoints = findKeyPoints(ref, hessian);
    SurfDescriptorExtractor descExtractor;
    FlannBasedMatcher matcher;

    Mat desc1, desc2;
    descExtractor.compute(refImg, refImgKeyPoints, desc1);
    descExtractor.compute(ref, refKeyPoints, desc2);


    MatchesArray matches;
    matcher.match(desc1, desc2, matches);
    double max_dist = maxDist;
    double min_dist = minDist;

    for (int i = 0; i < desc1.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }
    DBG("-- Max dist : %f \n", max_dist);
    DBG("-- Min dist : %f \n", min_dist);


    MatchesArray goodMatches;
    for (int i = 0; i < desc1.rows; i++) {
        if (matches[i].distance < 2 * min_dist) {
            goodMatches.push_back(matches[i]);
        }
    }
    matches.clear();
    return goodMatches;

}

KeyPointArray CvHelper::findKeyPoints(Mat& img, int hessian) {
    SurfFeatureDetector detector(hessian);
    Mat input1 = img;

    if (input1.data == NULL) {
        DBG(" --(!) Error reading images ");
        return KeyPointArray();
    }



    KeyPointArray keyPoints;
    detector.detect(input1, keyPoints);

    return keyPoints;

}

MatND CvHelper::makeHSHist(Mat& mat, Mat& mask) {
    Mat src = mat;
    Mat hsv;


    cvtColor(src, hsv, CV_BGR2HSV);

    // Quantize the hue to 30 levels
    // and the saturation to 32 levels
    int hbins = 32, sbins = 32;
    int histSize[] = {hbins, sbins};
    // hue varies from 0 to 179, see cvtColor
    float hranges[] = {0, 180};
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float sranges[] = {0, 256};
    const float* ranges[] = {hranges, sranges};
    MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0, 1};

    calcHist(&hsv, 1, channels, mask, // do not use mask
            hist, 2, histSize, ranges,
            true, // the histogram is uniform
            false);
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
    return hist;
}

Mat CvHelper::makeHSHistImage(MatND &hist) {

    double maxVal = 0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 5;
    int hbins = 30, sbins = 32;

    Mat histImg = Mat::zeros(sbins*scale, hbins * 5, CV_8UC3);

    for (int h = 0; h < hbins; h++)
        for (int s = 0; s < sbins; s++) {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal * 255 / maxVal);
            rectangle(histImg, Point(h*scale, s * scale),
                    Point((h + 1) * scale - 1, (s + 1) * scale - 1),
                    Scalar::all(intensity),
                    CV_FILLED);
        }


#ifdef DEBUG

    imshow("H-S Histogram", histImg);
#endif
    return histImg;
}

/**
 * F&uuml;hrt eine Histogram Angleichung durch. Die Helligkeit wird normalisiert und der Kontrast erh&ouml;t.
 * @param img Das Eingabebild.
 * @param convertRGB Gibt an, ob das Ausgabebild zu RGB convertiert werden soll.
 * @param inputIsBGR Gibt an, ob das Bild den BGR Farbraum verwendet. Default ist <code>true</code>.
 * @return Ein in Helligkeit normalisiertes und in Kontrast erh&ouml;tes Bild.
 */
Mat CvHelper::equalizeHistogram(Mat& img, bool convertback, bool inputIsBGR) {

    Mat equalized = Mat::zeros(img.size(), CV_8UC1);
    Mat gray = Mat::zeros(img.size(), CV_8UC1);
    if (img.type() != CV_8UC1) {
        try {
            if (inputIsBGR) {
                cvtColor(img, gray, CV_BGR2GRAY);
            } else {
                cvtColor(img, gray, CV_RGB2GRAY);
            }
        } catch (Exception& ex) {
            DBG("%s", ex.what());
        }

    } else {
        gray = img;
    }

    try {
        equalizeHist(gray, equalized);
    } catch (Exception& ex) {
        DBG("%s", ex.what());
    }
    Mat erg = Mat::zeros(img.size(), (convertback) ? CV_8UC3 : CV_8UC1);
    if (convertback) {
        cvtColor(equalized, erg, CV_GRAY2BGR);
    } else {
        erg = equalized;
    }
    return erg;

}

/**
 * Vergleicht zwei Histogramme.
 * @param hist1 
 * @param hist2
 * @param m Die Vergleichsmethode die verwendet wird. -> CV_COMP_*
 * @return Ein <code>double</code>, das angibt, wie &auml;hnlich sich die Histogramme sind.
 */
double CvHelper::compareHistogram(MatND& hist1, MatND& hist2, int m) {
    double erg = 0.0;

    try {
        if (m != CV_COMP_BHATTACHARYYA && m != CV_COMP_CHISQR && m != CV_COMP_CORREL && m != CV_COMP_INTERSECT) {
            erg = compareHist(hist1, hist2, CV_COMP_BHATTACHARYYA);
        } else {
            erg = compareHist(hist1, hist2, m);
        }
    } catch (Exception& ex) {
        DBG("%s", ex.what());
    }
    return erg;
}

/**
 * Akkumuliert eine Bildfolge
 * @param mat eine Bildfolge
 * @return Das Akkumulierte Bild
 */
Mat CvHelper::accumulateImages(ImageArray mats) {
    if (mats.size() < 2) {
        DBG("Vektor der Laenge: %i mind. 2 benoetigt", static_cast<int> (mats.size()));
        return Mat();
    }

    Mat erg = Mat::zeros(mats[0].size(), CV_64FC3);
    mats[0].copyTo(erg);

    for (int i = 1; i < (int) mats.size(); i++) {
        Mat current = mats[i];

        //accumulate(current, erg);
        add(erg, current, erg);
        erg /= 2;

    }

    return erg;
}

/**
 * Enfernt den Hintergrund eines Bildes mithilfe eines Kallibrierungsbiles(Bildfolge)
 * @param bg der Hintergrund ohne Objekt
 * @param img Das Bild mit Objekt
 * @return Ein Bild mit geschw&auml;rztem Hintergrund.
 */
Mat CvHelper::removeBackground(ImageArray bg, Mat img) {
    Mat accum = accumulateImages(bg);
    MatND mask;
    absdiff(accum, img, mask);
    return mask;
}

Mat CvHelper::convertBlackAndWhite(Mat& in, int thld) {
    Mat singleChannelImg;
    if (in.type() != CV_8UC1) {
        DBG("Convertiere zu 8UC1");

        singleChannelImg = Mat(in.size(), CV_8UC1);
        cvtColor(in, singleChannelImg, CV_BGR2GRAY);
    } else {
        singleChannelImg = Mat(in.size(), CV_8UC1);
        in.copyTo(singleChannelImg);
    }
    threshold(singleChannelImg, singleChannelImg, thld, 255, CV_THRESH_BINARY);
    return singleChannelImg;
}

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
PointHistogram CvHelper::createPositionHistogram(vector<Point> points, int imageWidth, int imageHeight, int histogramBins, POSITION_HISTOGRAM_DIRECTION direction) {
    if (points.empty()) {
        DBG("Keine Punkte angegeben.");
        return vector < vector < Point >> ();
    }

    if (imageHeight <= 0 || imageWidth <= 0) {
        DBG("Ungueltige Bildmasse: %i x %i.", imageWidth, imageHeight);
        return vector < vector < Point >> ();
    }

    int binWidth;
    switch (direction) {
        case DIRECTION_X:
            if (imageHeight % histogramBins != 0) {
                DBG("Bildhoehe muss vielfaches von %i sein, ist %i. Eventuelle Skalierung muss vor dieser Operation erfolgen.", histogramBins, imageHeight);
                return vector < vector < Point >> ();
            } else {
                binWidth = imageHeight / histogramBins;
            }
        case DIRECTION_Y:
            if (imageWidth % histogramBins != 0) {
                DBG("BildWeite muss vielfaches von %i sein, ist %i. Eventuelle Skalierung muss vor dieser Operation erfolgen.", histogramBins, imageWidth);
                return vector < vector < Point >> ();
            } else {
                binWidth = imageWidth / histogramBins;
            }
    };

    if (binWidth <= 0) {
        DBG("Konnte Weite der Bins nicht ermitteln!");
    }
    int currentMin, currentMax;
    currentMin = 0;
    currentMax = binWidth;
    PointHistogram hist = PointHistogram(histogramBins);

    for (int i = 0; i < histogramBins; i++) {
        hist[i] = vector<Point > ();
        for (vector<Point>::iterator iterate = points.begin(); iterate != (points.end() - 1); iterate++) {
            switch (direction) {
                case DIRECTION_X:
                    if ((*iterate).x >= currentMin && (*iterate).x < currentMax) {
                        hist[i].push_back((*iterate));
                    }

                    break;
                case DIRECTION_Y:
                    if ((*iterate).y >= currentMin && (*iterate).y < currentMax) {
                        hist[i].push_back((*iterate));
                    }
                    break;
                default:
                    break;
            };

        }


        switch (direction) {
            case DIRECTION_X:
                if (currentMax > imageWidth) {
                    DBG("Weite %i hat Bildbegrenzungen %i ueberschritten. Ergebnis evtl. unvollstaendig", currentMax, imageWidth);

                }
                break;
            case DIRECTION_Y:
                if (currentMax > imageHeight) {
                    DBG("Hoehe %i hat Bildbegrenzungen %i ueberschritten. Ergebnis evtl. unvollstaendig", currentMax, imageHeight);
                }
                break;
        };
        currentMin = currentMax;
        currentMax += binWidth;

    }


    return hist;
}

/**
 * Entfernt isolierte Punkte aus einem Punktehistogram.
 * @param hist Das Histogram.
 * @param isolationBins Anazahl der B&auml;nder, die in einer Umgebung eines Punktes leer sein m&uuml;ssen, damit der Punkt als isoliert angesehen wird.
 * @return Das Punktehistogram, in dem isolierte Punkte entfernt wurden
 */
PointHistogram CvHelper::removeIsolatedPoints(PointHistogram hist, int isolationBins) {
    if (isolationBins <= 0) {
        DBG("Ein wert von <=0 ist in diesem Kontext nicht sinnvoll.");
        return vector < vector<Point> > ();
    }
    if (isolationBins >= (int) hist.size()) {
        DBG("Ein wert von <=0 ist in diesem Kontext nicht sinnvoll.");
        return vector < vector<Point> > ();
    }


    PointHistogram erg = PointHistogram(hist.size());
    BooleanArray isolatedLeft = BooleanArray(isolationBins);
    BooleanArray isolatedRight = BooleanArray(isolationBins);
    for (int i = 0; i < (int) hist.size(); i++) {
        initVector(isolatedLeft, true);
        initVector(isolatedRight, true);
        for (int left = 1; left <= isolationBins and (i - left) >= 0; left++) {
            /*Pruefe alle Bins links von root, bis zu einem Abstand von isolationBins*/
            if (hist[i - left].size() > 0) {
                isolatedLeft[left - 1] = false;
                break;
            }
        }
        for (int right = 1; right <= isolationBins and (i + right) <= (int) hist.size(); right++) {
            /*Pruefe alle Bins rechts von root, bis zu einem Abstand von isolationBins*/
            if (hist[i + right].size() > 0) {
                isolatedRight[right - 1] = false;
                break;
            }
        }
        bool chk = true;
        for (int j = 0; j < isolationBins; j++) {
            if (!isolatedLeft[j] or !isolatedRight[j]) {
                chk = false;
                break;
            }
        }
        if (chk) {
            DBG("Entferne %i isolierte Punkte von Stelle %i", (int) hist[i].size(), i);
            erg[i].clear();
            erg[i] = PointArray();
        } else {
            erg[i] = hist[i];
        }
    }
    return erg;
}

/**
 * Filtert ein Punktehistogram. 
 * @param hist Das Punktehistogram.
 * @param fromBin Alle Punkte, die &ouml;rtlich vor diesem Band angesiedelt sind, werden entfernt.
 * @param toBin Alle Punkte, die &ouml;rtlich nach diesem Band angesiedelt sind, werden entfernt.
 * @return Ein Punktehistogram, in dem nur noch die B&auml;nder zweichen <code>fromBin</code> und <code>toBin</code> belegt sind.
 */
PointHistogram CvHelper::filterPositionHistogramRange(PointHistogram hist, int fromBin, int toBin) {
    if (toBin < fromBin) {
        return filterPositionHistogramRange(hist, toBin, fromBin);
    }
    vector<vector<Point> > erg = vector<vector<Point> >(hist.size());
    for (int i = 0; i < (int) hist.size(); i++) {
        if (i >= fromBin && i <= toBin) {
            erg[i] = hist[i];
        } else {
            erg[i] = vector<Point > ();
        }
    }
    return erg;
}

/**
 * Erstellt aus einem Punktehistogram (Vektor von Vektoren von Punkten) wieder eine Punktmenge (Vektor von Punkten).
 * @param hist Das Punktehistogram.
 * @return Einen Vector von Punkten.
 */
PointArray CvHelper::retransformPositionHistogram(PointHistogram hist) {
    vector<Point> erg = vector<Point > ();
    for (vector<vector<Point> >::iterator root = hist.begin(); root != hist.end(); root++) {
        for (vector<Point>::iterator iter = (*root).begin(); iter != (*root).end(); iter++) {
            Point p = (*iter);
            erg.push_back(p);
        }
    }
    return erg;
}

BooleanArray CvHelper::initVector(BooleanArray vec, bool initValue) {
    for (int i = 0; i < (int) vec.size(); i++) {
        vec[i] = initValue;
    }
    return vec;
}

/**
 * Pr&uuml;ft auf Gleichheit.
 */
double CvHelper::checkEquality(const Mat& img1, const Mat& img2) {
    Mat sumArr;
    absdiff(img1, img2, sumArr);
    sumArr.convertTo(sumArr, CV_32F);
    sumArr = sumArr.mul(sumArr);
    Scalar sumScalar = sum(sumArr);
    double channelSum = sumScalar.val[0] + sumScalar.val[1] + sumScalar.val[2];
    if (channelSum <= 1e-10)
        return 0;
    else {
        double mse = channelSum / (double) (img1.channels() * img1.total());
        double psnr = 10.0 * log10((255 * 255) / mse);
        return psnr;
    }


}

/**
 * Pr&uuml;ft auf strukrurelle Gleichheit (relativ Langsam).
 */
Scalar CvHelper::checkStructuralEquality(const Mat& in1, const Mat& in2) {
    const double C1 = 6.5025, C2 = 58.5225;
    Mat img1, img2;

    in1.convertTo(img1, CV_32F);
    in2.convertTo(img2, CV_32F);

    Mat img2_2 = img2.mul(img2);
    Mat img1_2 = img1.mul(img1);
    Mat img1_img2 = img1.mul(img2);

    Mat blured1, blured2;

    GaussianBlur(img1, blured1, Size(11, 11), 1.5);
    GaussianBlur(img2, blured2, Size(11, 11), 1.5);

    Mat blured1_2 = blured1.mul(blured1);
    Mat blured2_2 = blured2.mul(blured2);
    Mat blured1_blured2 = blured1.mul(blured2);
    Mat sigma1_2, sigma2_2, sigma12;

    GaussianBlur(img1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= blured1_2;
    GaussianBlur(img2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= blured2_2;
    GaussianBlur(img1_img2, sigma12, Size(11, 11), 1.5);
    sigma12 -= blured1_blured2;


    Mat t1, t2, t3;
    t1 = 2 * blured1_blured2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);

    t1 = blured1_2 + blured2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);
    Mat ssim_map;
    divide(t3, t1, ssim_map);
    Scalar mssim = mean(ssim_map);

    return mssim;
}

PointHistogram CvHelper::extractNoticableBins(PointHistogram hist, int minLength) {
    int len = hist.size();
    PointHistogram erg = PointHistogram(hist.size());
    for (int i = 0; i < len; i++) {
        if (hist[i].size() < (unsigned int) minLength) {
            erg[i] = PointArray();
        } else {
            erg[i] = hist[i];
        }
    }
    return erg;
}

Size CvHelper::resToSize(INPUT_FORMAT fmt) {
    Size erg = Size();

    // <editor-fold defaultstate="collapsed" desc="Switch ueber alle bekannten Aufloesungen.">
    switch (fmt) {
        case r720p:
            erg = Size(1280, 720);
            break;
        case r1080p:
            erg = Size(1920, 1080);
            break;
        case r480p:
            erg = Size(640, 480);
            break;
        case rUnknown:
            erg = Size(0, 0);
            break;
        case rNULL:
            erg = Size(0, 0);
            break;
    }
    // </editor-fold>

    return erg;
}

String CvHelper::resToString(INPUT_FORMAT fmt) {
    String erg = "Unbekannt";

    // <editor-fold defaultstate="collapsed" desc="Switch ueber alle bekannten Aufloesungen.">
    switch (fmt) {
        case r720p:
            erg = "720p";
            break;
        case r1080p:
            erg = "1080p";
            break;
        case r480p:
            erg = "VGA";
            break;
        case rUnknown:
            erg = "Unbekannt";
            break;
        case rNULL:
            erg = "Unbekannt";
            break;
    }
    // </editor-fold>

    return erg;
}
