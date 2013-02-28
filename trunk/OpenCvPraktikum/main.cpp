/*
 * main.cpp
 *
 *  Created on: 18.11.2012
 *      Author: Julian Cordes, Nils Frenking
 */

#include "header.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <string>

// <editor-fold defaultstate="collapsed" desc="Letzte Aufgabe">
#if /* Letzte Aufgabe */1

String getNameByDetectionIdx(int i);

int main(int argc, char** argv) {
    RectangleArray history = RectangleArray();
    const int histMax = 7;
    InputHandler handler = InputHandler();
    CvHelper* helper = CvHelper::getInstance();
    handler.setInputSource(INPUT_CAM);
    handler.open();
    //handler.requestFormat(r720p);
    Mat currentImage;
    WindowManager* winman = WindowManager::getInstance();
    CvWindow* wnd = winman->createWindow("Detection", 0, 0);


    // <editor-fold defaultstate="collapsed" desc="Initialisieren der Cascaden">
    vector<CascadeClassifier> cascades;
    CascadeClassifier ccf;
    ccf.load(CASCADE_BASE_PATH + "fist_cascade.xml");
    cascades.push_back(ccf);
    ccf = CascadeClassifier();
    ccf.load(CASCADE_BASE_PATH + "thumb_cascade.xml");
    cascades.push_back(ccf);

    ccf = CascadeClassifier();
    ccf.load(CASCADE_BASE_PATH + "two_finger_cascade.xml");
    cascades.push_back(ccf);

    ccf = CascadeClassifier();
    ccf.load(CASCADE_BASE_PATH + "three_finger_cascade.xml");
    cascades.push_back(ccf);

    ccf = CascadeClassifier();
    ccf.load(CASCADE_BASE_PATH + "four_finger_cascade.xml");
    cascades.push_back(ccf);

    ccf = CascadeClassifier();
    ccf.load(CASCADE_BASE_PATH + "plain_hand_cascade.xml");
    cascades.push_back(ccf);
    // </editor-fold>

    for (int i = 0; i < 5; i++) {
        handler.next();
        currentImage = handler.getImage();
    }

    wnd->showWindow();
    wnd->setCurrentImage(&currentImage);
    RectangleArray detection;
    while (true) {
        handler.next();
        currentImage = handler.getImage();
        for (int i = 0; i < 6; i++) {
            detection = helper->detectAll(currentImage, cascades[i], 100, 0.0f, 0.0f);
            if (!detection.empty()) {
                
                    rectangle(currentImage, detection[0], Scalar(0, 255, 0), 3);
                    
                    helper->drawString(currentImage, getNameByDetectionIdx(i), Scalar(0, 255, 0), detection[0].x, detection[0].y + detection[0].height + 1);
                
                
            }

        }
        wnd->setCurrentImage(&currentImage);
        if (cvWaitKey(10) == KEY_CHAR::ESC) {
            cout << "ESC-Gedrueckt -> Ende!"<<endl;
            break;
        }
    }
    winman->relesase();
    wnd->closeWindow();

    return EXIT_SUCCESS;
}

String getNameByDetectionIdx(int i) {
    switch (i) {
        case 0: return "Faust";
        case 1: return "Daumen hoch";
        case 2: return "Zwei Finger";
        case 3: return "Drei Finger";
        case 4: return "Vier Finger";
        case 5: return "Flache Hand";
        default: return "Unbekannt";
    }
}



#endif// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Beurteilung der Klassifikation">
#if /* Beurteilung der Klassifikation */0

int main(int argc, char** argv) {
    ATest* test = new ClassificationTest();
    if (test->testMain(StringArray()) == EXIT_SUCCESS) {
        cout << "Test erfolgreich! :-)" << endl;
        return EXIT_SUCCESS;
    } else {
        cout << "Test fehlgeschlagen! :-(" << endl;
        return EXIT_FAILURE;
    }

}

#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Detect-Object Cascade">
#if /* Detect-Object Cascade */0


using namespace std;
using namespace cv;

typedef vector<Rect> RectArray;

int main(int, char** argv) {
    CvHelper* helper = CvHelper::getInstance();
    CascadeClassifier cascade;
    cascade.load(CASCADE_BASE_PATH + String("thumb_cascade.xml"));
    InputHandler handler = InputHandler();
    handler.setInputSource(INPUT_CAM);
    handler.open();
    Mat img;
    // handler.requestFormat(r720p);
    handler.next();
    img = handler.getImage();
    namedWindow("Cam");
    helper->detectAll(img, cascade, 100, 1000, 4 / 3);
    imshow("Cam", img);

    RectArray hands;

    while (true) {
        if (!handler.reachesEndOfInput()) {
            handler.next();
            img = handler.getImage();
            hands = helper->detectAll(img, cascade, 100, 1000, 4 / 3);
            if (!hands.empty()) {
                for (RectArray::const_iterator iter = hands.begin(); iter != hands.end(); iter++) {
                    Point center;

                    int radius;

                    center.x = cvRound((iter->x + iter->width * 0.5));
                    center.y = cvRound((iter->y + iter->height * 0.5));
                    radius = cvRound((iter->width + iter->height)*0.25);

                    circle(img, center, radius, Scalar(255, 255, 255), 3, 8, 0);

                }

            }
        }
        imshow("Cam", img);
        cvWaitKey(5);
    }
    return EXIT_SUCCESS;
}

#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Detection Description Matching">
#if /* Detection Description Matching */0

#include "highgui/highgui.hpp"
#include "calib3d/calib3d.hpp"
#include "imgproc/imgproc.hpp"
#include "features2d/features2d.hpp"

#include <iostream>

using namespace cv;
using namespace std;

void help(char** argv) {
    cout << "\nThis program demonstrats keypoint finding and matching between 2 images using features2d framework.\n"
            << "   In one case, the 2nd image is synthesized by homography from the first, in the second case, there are 2 images\n"
            << "\n"
            << "Case1: second image is obtained from the first (given) image using random generated homography matrix\n"
            << argv[0] << " [detectorType] [descriptorType] [matcherType] [matcherFilterType] [image] [evaluate(0 or 1)]\n"
            << "Example of case1:\n"
            << "./descriptor_extractor_matcher SURF SURF FlannBased NoneFilter cola.jpg 0\n"
            << "\n"
            << "Case2: both images are given. If ransacReprojThreshold>=0 then homography matrix are calculated\n"
            << argv[0] << " [detectorType] [descriptorType] [matcherType] [matcherFilterType] [image1] [image2] [ransacReprojThreshold]\n"
            << "\n"
            << "Matches are filtered using homography matrix in case1 and case2 (if ransacReprojThreshold>=0)\n"
            << "Example of case2:\n"
            << "./descriptor_extractor_matcher SURF SURF BruteForce CrossCheckFilter cola1.jpg cola2.jpg 3\n"
            << "\n"
            << "Possible detectorType values: see in documentation on createFeatureDetector().\n"
            << "Possible descriptorType values: see in documentation on createDescriptorExtractor().\n"
            << "Possible matcherType values: see in documentation on createDescriptorMatcher().\n"
            << "Possible matcherFilterType values: NoneFilter, CrossCheckFilter." << endl;
}

#define DRAW_RICH_KEYPOINTS_MODE     0
#define DRAW_OUTLIERS_MODE           1

const string winName = "correspondences";

enum {
    NONE_FILTER = 0, CROSS_CHECK_FILTER = 1
};

int getMatcherFilterType(const string& str) {
    if (str == "NoneFilter")
        return NONE_FILTER;
    if (str == "CrossCheckFilter")
        return CROSS_CHECK_FILTER;
    CV_Error(CV_StsBadArg, "Invalid filter name");
    return -1;
}

void simpleMatching(Ptr<DescriptorMatcher>& descriptorMatcher,
        const Mat& descriptors1, const Mat& descriptors2,
        vector<DMatch>& matches12) {

    descriptorMatcher->match(descriptors1, descriptors2, matches12);
}

void crossCheckMatching(Ptr<DescriptorMatcher>& descriptorMatcher,
        const Mat& descriptors1, const Mat& descriptors2,
        vector<DMatch>& filteredMatches12, int knn = 1) {
    filteredMatches12.clear();
    vector<vector<DMatch> > matches12, matches21;
    descriptorMatcher->knnMatch(descriptors1, descriptors2, matches12, knn);
    descriptorMatcher->knnMatch(descriptors2, descriptors1, matches21, knn);
    for (size_t m = 0; m < matches12.size(); m++) {
        bool findCrossCheck = false;
        for (size_t fk = 0; fk < matches12[m].size(); fk++) {
            DMatch forward = matches12[m][fk];

            for (size_t bk = 0; bk < matches21[forward.trainIdx].size(); bk++) {
                DMatch backward = matches21[forward.trainIdx][bk];
                if (backward.trainIdx == forward.queryIdx) {
                    filteredMatches12.push_back(forward);
                    findCrossCheck = true;
                    break;
                }
            }
            if (findCrossCheck) break;
        }
    }
}

void warpPerspectiveRand(const Mat& src, Mat& dst, Mat& H, RNG& rng) {
    H.create(3, 3, CV_32FC1);
    H.at<float>(0, 0) = rng.uniform(0.8f, 1.2f);
    H.at<float>(0, 1) = rng.uniform(-0.1f, 0.1f);
    H.at<float>(0, 2) = rng.uniform(-0.1f, 0.1f) * src.cols;
    H.at<float>(1, 0) = rng.uniform(-0.1f, 0.1f);
    H.at<float>(1, 1) = rng.uniform(0.8f, 1.2f);
    H.at<float>(1, 2) = rng.uniform(-0.1f, 0.1f) * src.rows;
    H.at<float>(2, 0) = rng.uniform(-1e-4f, 1e-4f);
    H.at<float>(2, 1) = rng.uniform(-1e-4f, 1e-4f);
    H.at<float>(2, 2) = rng.uniform(0.8f, 1.2f);

    warpPerspective(src, dst, H, src.size());
}

void doIteration(const Mat& img1, Mat& img2, bool isWarpPerspective,
        vector<KeyPoint>& keypoints1, const Mat& descriptors1,
        Ptr<FeatureDetector>& detector, Ptr<DescriptorExtractor>& descriptorExtractor,
        Ptr<DescriptorMatcher>& descriptorMatcher, int matcherFilter, bool eval,
        double ransacReprojThreshold, RNG& rng) {
    assert(!img1.empty());
    Mat H12;
    if (isWarpPerspective)
        warpPerspectiveRand(img1, img2, H12, rng);
    else
        assert(!img2.empty()/* && img2.cols==img1.cols && img2.rows==img1.rows*/);

    cout << endl << "< Extracting keypoints from second image..." << endl;
    vector<KeyPoint> keypoints2;
    detector->detect(img2, keypoints2);
    cout << keypoints2.size() << " points" << endl << ">" << endl;

    if (!H12.empty() && eval) {
        cout << "< Evaluate feature detector..." << endl;
        float repeatability;
        int correspCount;
        evaluateFeatureDetector(img1, img2, H12, &keypoints1, &keypoints2, repeatability, correspCount);
        cout << "repeatability = " << repeatability << endl;
        cout << "correspCount = " << correspCount << endl;
        cout << ">" << endl;
    }

    cout << "< Computing descriptors for keypoints from second image..." << endl;
    Mat descriptors2;
    descriptorExtractor->compute(img2, keypoints2, descriptors2);
    cout << ">" << endl;

    cout << "< Matching descriptors..." << endl;
    vector<DMatch> filteredMatches;
    switch (matcherFilter) {
        case CROSS_CHECK_FILTER:
            crossCheckMatching(descriptorMatcher, descriptors1, descriptors2, filteredMatches, 2);
            break;
        default:
            simpleMatching(descriptorMatcher, descriptors1, descriptors2, filteredMatches);
    }
    cout << ">" << endl;

    if (!H12.empty() && eval) {
        cout << "< Evaluate descriptor matcher..." << endl;
        vector<Point2f> curve;
        Ptr<GenericDescriptorMatcher> gdm = new VectorDescriptorMatcher(descriptorExtractor, descriptorMatcher);
        evaluateGenericDescriptorMatcher(img1, img2, H12, keypoints1, keypoints2, 0, 0, curve, gdm);

        Point2f firstPoint = *curve.begin();
        Point2f lastPoint = *curve.rbegin();
        int prevPointIndex = -1;
        cout << "1-precision = " << firstPoint.x << "; recall = " << firstPoint.y << endl;
        for (float l_p = 0; l_p <= 1 + FLT_EPSILON; l_p += 0.05f) {
            int nearest = getNearestPoint(curve, l_p);
            if (nearest >= 0) {
                Point2f curPoint = curve[nearest];
                if (curPoint.x > firstPoint.x && curPoint.x < lastPoint.x && nearest != prevPointIndex) {
                    cout << "1-precision = " << curPoint.x << "; recall = " << curPoint.y << endl;
                    prevPointIndex = nearest;
                }
            }
        }
        cout << "1-precision = " << lastPoint.x << "; recall = " << lastPoint.y << endl;
        cout << ">" << endl;
    }

    vector<int> queryIdxs(filteredMatches.size()), trainIdxs(filteredMatches.size());
    for (size_t i = 0; i < filteredMatches.size(); i++) {
        queryIdxs[i] = filteredMatches[i].queryIdx;
        trainIdxs[i] = filteredMatches[i].trainIdx;
    }

    if (!isWarpPerspective && ransacReprojThreshold >= 0) {
        cout << "< Computing homography (RANSAC)..." << endl;
        vector<Point2f> points1;
        KeyPoint::convert(keypoints1, points1, queryIdxs);
        vector<Point2f> points2;
        KeyPoint::convert(keypoints2, points2, trainIdxs);
        H12 = findHomography(Mat(points1), Mat(points2), CV_RANSAC, ransacReprojThreshold);
        cout << ">" << endl;
    }

    Mat drawImg;
    if (!H12.empty()) // filter outliers
    {
        vector<char> matchesMask(filteredMatches.size(), 0);
        vector<Point2f> points1;
        KeyPoint::convert(keypoints1, points1, queryIdxs);
        vector<Point2f> points2;
        KeyPoint::convert(keypoints2, points2, trainIdxs);
        Mat points1t;
        perspectiveTransform(Mat(points1), points1t, H12);

        double maxInlierDist = ransacReprojThreshold < 0 ? 3 : ransacReprojThreshold;
        for (size_t i1 = 0; i1 < points1.size(); i1++) {
            if (norm(points2[i1] - points1t.at<Point2f > ((int) i1, 0)) <= maxInlierDist) // inlier
                matchesMask[i1] = 1;
        }
        // draw inliers
        drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, drawImg, CV_RGB(0, 255, 0), CV_RGB(0, 0, 255), matchesMask
#if DRAW_RICH_KEYPOINTS_MODE
                , DrawMatchesFlags::DRAW_RICH_KEYPOINTS
#endif
                );

#if DRAW_OUTLIERS_MODE
        // draw outliers
        for (size_t i1 = 0; i1 < matchesMask.size(); i1++)
            matchesMask[i1] = !matchesMask[i1];
        drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, drawImg, CV_RGB(0, 0, 255), CV_RGB(255, 0, 0), matchesMask,
                DrawMatchesFlags::DRAW_OVER_OUTIMG | DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
#endif
    } else
        drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, drawImg);

    imshow(winName, drawImg);
}

int main(int argc, char** argv) {

    bool isWarpPerspective = false;
    double ransacReprojThreshold = -1.1;
    if (!isWarpPerspective)
        ransacReprojThreshold = 1.2;

    cout << "< Creating detector, descriptor extractor and descriptor matcher ..." << endl;
    Ptr<FeatureDetector> detector = FeatureDetector::create("SURF");
    Ptr<DescriptorExtractor> descriptorExtractor = DescriptorExtractor::create("SURF");
    Ptr<DescriptorMatcher> descriptorMatcher = DescriptorMatcher::create("FlannBased");
    int mactherFilterType = getMatcherFilterType("CrossCheckFilter");
    bool eval = true; //!isWarpPerspective ? false : (atoi(argv[6]) == 0 ? false : true);
    cout << ">" << endl;
    if (detector.empty() || descriptorExtractor.empty() || descriptorMatcher.empty()) {
        cout << "Can not create detector or descriptor exstractor or descriptor matcher of given types" << endl;
        return -1;
    }
    InputHandler handler = InputHandler();
    handler.setInputSource(INPUT_CAM);
    handler.open();
    for (int i = 0; i < 5; i++) {
        handler.next();
    }
    cout << "< Reading the images..." << endl;
    Mat img1 = imread("/media/ertai/Data/cvStuff/Videos/Fist/POS-63.jpg"), img2;
    if (!isWarpPerspective)
        img2 = handler.getImage(); //imread("/home/ertai/Videos/POS1/pos1-0255.jpg");
    cout << ">" << endl;
    if (img1.empty() || (!isWarpPerspective && img2.empty())) {
        cout << "Can not read images" << endl;
        return -1;
    }

    cout << endl << "< Extracting keypoints from first image..." << endl;
    vector<KeyPoint> keypoints1;
    detector->detect(img1, keypoints1);
    cout << keypoints1.size() << " points" << endl << ">" << endl;

    cout << "< Computing descriptors for keypoints from first image..." << endl;
    Mat descriptors1;
    descriptorExtractor->compute(img1, keypoints1, descriptors1);
    cout << ">" << endl;

    namedWindow(winName, 1);
    RNG rng = theRNG();
    doIteration(img1, img2, isWarpPerspective, keypoints1, descriptors1,
            detector, descriptorExtractor, descriptorMatcher, mactherFilterType, eval,
            ransacReprojThreshold, rng);
    for (;;) {
        char c = (char) waitKey(0);
        if (c == '\x1b') // esc
        {
            cout << "Exiting ..." << endl;
            break;
        } else if (isWarpPerspective) {
            doIteration(img1, img2, isWarpPerspective, keypoints1, descriptors1,
                    detector, descriptorExtractor, descriptorMatcher, mactherFilterType, eval,
                    ransacReprojThreshold, rng);
        }
    }
    return 0;
}

#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Hybrid-Tracker">
#if /* Hybrid-Tracker */0


#include "contrib/hybridtracker.hpp"

using namespace cv;
using namespace std;

Mat frame, image;
Rect selection;
Point origin;
bool selectObject = false;
int trackObject = 0;
int live = 1;

void drawRectangle(Mat* image, Rect win) {
    rectangle(*image, Point(win.x, win.y), Point(win.x + win.width, win.y
            + win.height), Scalar(0, 255, 0), 2, CV_AA);
}

void onMouse(int event, int x, int y, int, void*) {
    if (selectObject) {
        selection.x = MIN(x, origin.x);
        selection.y = MIN(y, origin.y);
        selection.width = std::abs(x - origin.x);
        selection.height = std::abs(y - origin.y);
        selection &= Rect(0, 0, image.cols, image.rows);
    }

    switch (event) {
        case CV_EVENT_LBUTTONDOWN:
            origin = Point(x, y);
            selection = Rect(x, y, 0, 0);
            selectObject = true;
            break;
        case CV_EVENT_LBUTTONUP:
            selectObject = false;
            trackObject = -1;
            break;
    }
}

void help() {
    printf("Usage: ./hytrack live or ./hytrack <test_file> \n\
For Live View or Benchmarking. Read documentation is source code.\n\n");
}

int main(int argc, char** argv) {
    if (argc != 2) {
        help();
        return 1;
    }

    FILE* f = 0;
    VideoCapture cap;
    char test_file[20] = "";

    if (strcmp(argv[1], "live") != 0) {
        sprintf(test_file, "%s", argv[1]);
        f = fopen(test_file, "r");
        char vid[20];
        int values_read = fscanf(f, "%s\n", vid);
        CV_Assert(values_read == 1);
        cout << "Benchmarking against " << vid << endl;
        live = 0;
    } else {
        cap.open(0);
        if (!cap.isOpened()) {
            cout << "Failed to open camera" << endl;
            return 0;
        }
        cout << "Opened camera" << endl;
        cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
        cap >> frame;
    }

    HybridTrackerParams params;

    // motion model params
    params.motion_model = CvMotionModel::LOW_PASS_FILTER;
    params.low_pass_gain = 0.1f;
    // mean shift params
    params.ms_tracker_weight = 0.8f;
    params.ms_params.tracking_type = CvMeanShiftTrackerParams::HSV;
    // feature tracking params
    params.ft_tracker_weight = 0.2f;
    params.ft_params.feature_type = CvFeatureTrackerParams::SIFT;
    params.ft_params.window_size = 0;

    DBG("Parameter erstellt.");
    HybridTracker tracker(params);
    //params
    char img_file[20] = "seqG/0001.png";
    char img_file_num[10];
    namedWindow("Win", 1);

    setMouseCallback("Win", onMouse, 0);

    int i = 0;
    float w[4];
    for (;;) {
        i++;
        if (live) {
            cap >> frame;
            if (frame.empty())
                break;
            frame.copyTo(image);
        } else {
            int values_read = fscanf(f, "%d %f %f %f %f\n", &i, &w[0], &w[1], &w[2], &w[3]);
            CV_Assert(values_read == 5);
            sprintf(img_file, "seqG/%04d.png", i);
            image = imread(img_file, CV_LOAD_IMAGE_COLOR);
            if (image.empty())
                break;
            selection = Rect(cvRound(w[0] * image.cols), cvRound(w[1] * image.rows),
                    cvRound(w[2] * image.cols), cvRound(w[3] * image.rows));
        }

        sprintf(img_file_num, "Frame: %d", i);
        putText(image, img_file_num, Point(10, image.rows - 20), FONT_HERSHEY_PLAIN, 0.75, Scalar(255, 255, 255));
        if (!image.empty()) {

            if (trackObject < 0) {
                tracker.newTracker(image, selection);
                trackObject = 1;
            }

            if (trackObject) {
                tracker.updateTracker(image);
                drawRectangle(&image, tracker.getTrackingWindow());
            }

            if (selectObject && selection.width > 0 && selection.height > 0) {
                Mat roi(image, selection);
                bitwise_not(roi, roi);
            }

            drawRectangle(&image, Rect(cvRound(w[0] * image.cols), cvRound(w[1] * image.rows),
                    cvRound(w[2] * image.cols), cvRound(w[3] * image.rows)));
            imshow("Win", image);

            waitKey(100);
        } else
            i = 0;
    }

    fclose(f);
    return 0;
}
#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Backprojection">
#if /* Backprojection */0
using namespace cv;
using namespace std;

/// Global Variables
Mat src;
Mat hsv;
Mat mask;

int lo = 20;
int up = 20;
const char* window_image = String("Source image").c_str();

/// Function Headers
void Hist_and_Backproj();
void pickPoint(int event, int x, int y, int, void*);

/**
 * @function main
 */
int main(int argc, char** argv) {
    InputHandler handler = InputHandler();
    handler.setInputSource(INPUT_CAM);
    if (!handler.open()) {
        DBG("Konnte Eingabe nicht öffnen");
        return EXIT_FAILURE;
    }
    if (handler.requestFormat(r720p)) {
        DBG("Eingabe in 720p");
    }
    handler.next();
    Mat camSrc;
    src = handler.getImage();
    blur(src, src, Size(7, 7), Point(0, 0), CV_BLUR_NO_SCALE);

    /// Transform it to HSV
    cvtColor(src, hsv, CV_BGR2HSV);

    /// Show the image 
    namedWindow("Norm", CV_WINDOW_AUTOSIZE);
    imshow("Norm", src);
    namedWindow("HSV-Image");


    /// Set Trackbars for floodfill thresholds
    createTrackbar("Low thresh", "Norm", &lo, 255, 0);
    createTrackbar("High thresh", "Norm", &up, 255, 0);
    /// Set a Mouse Callback
    setMouseCallback("Norm", pickPoint, 0);

    while (true) {
        handler.next();
        if (!handler.reachesEndOfInput()) {
            src = handler.getImage();
            cvtColor(src, hsv, CV_BGR2HSV);
            blur(src, src, Size(7, 7), Point(0, 0), CV_BLUR_NO_SCALE);
        }
        imshow("Norm", src);

        if (cvWaitKey(500) != -1) {
            break;
        }
    }
    return 0;
}

/**
 * @function pickPoint
 */
void pickPoint(int event, int x, int y, int, void*) {
    if (event != CV_EVENT_LBUTTONDOWN) {
        return;
    }

    // Fill and get the mask
    Point seed = Point(x, y);
    Vec3i vec = src.at<Vec3i > (seed);

    DBG("Ausgewaehlter Punkt mit der Farbe: %i,%i,%i bei Lo=%i und High=%i", vec.val[0], vec.val[1], vec.val[2], lo, up);
    int newMaskVal = 255;
    Scalar newVal = Scalar(120, 120, 120);

    int connectivity = 8;
    int flags = connectivity + (newMaskVal << 8) + FLOODFILL_FIXED_RANGE /*+ FLOODFILL_MASK_ONLY*/;

    Mat mask2 = Mat::zeros(src.rows + 2, src.cols + 2, CV_8UC1);
    floodFill(src, mask2, seed, newVal, 0, Scalar(lo, lo, lo), Scalar(up, up, up), flags);
    mask = mask2(Range(1, mask2.rows - 1), Range(1, mask2.cols - 1));

    imshow("Mask", mask);

    Hist_and_Backproj();
}

/**
 * @function Hist_and_Backproj
 */
void Hist_and_Backproj() {
    MatND hist;
    int h_bins = 10;
    int s_bins = 10;
    int histSize[] = {h_bins, s_bins};

    float h_range[] = {0, 179};
    float s_range[] = {0, 255};
    const float* ranges[] = {h_range, s_range};
    Mat hs = Mat::zeros(hsv.size(), CV_8UC3);

    int ch[] = {0, 0, 1, 1};
    mixChannels(&hsv, 1, &hs, 1, ch, 2);
    imshow("HSV-Image", hs);
    int channels[] = {0, 1};


    /// Get the Histogram and normalize it
    calcHist(&hsv, 1, channels, mask, hist, 2, histSize, ranges, true, false);

    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
    imshow("Hist", hist);
    /// Get Backprojection
    MatND backproj;
    calcBackProject(&hsv, 1, channels, hist, backproj, ranges, 1, true);
    imshow("BackProj", backproj);

}
#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         ML">
#if  /* ML */ 0

using namespace cv;

int main(int, char** argv) {

    // Data for visual representation
    int width = 512, height = 512;
    Mat image = Mat::zeros(height, width, CV_8UC3);

    // Set up training data
    float labels[4] = {1.0, -1.0, -1.0, -1.0};
    Mat labelsMat(3, 1, CV_32FC1, labels);

    float trainingData[4][2] = {
        {501, 10},
        {255, 10},
        {501, 255},
        {10, 501}
    };
    Mat trainingDataMat(3, 2, CV_32FC1, trainingData);

    // Set up SVM's parameters
    CvSVMParams params;
    params.svm_type = CvSVM::C_SVC;
    params.kernel_type = CvSVM::LINEAR;
    params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);

    // Train the SVM
    CvSVM SVM;
    SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);

    Vec3b green(0, 255, 0), blue(255, 0, 0);
    // Show the decision regions given by the SVM
    for (int i = 0; i < image.rows; ++i)
        for (int j = 0; j < image.cols; ++j) {
            Mat sampleMat = (Mat_<float>(1, 2) << i, j);
            float response = SVM.predict(sampleMat);

            if (response == 1)
                image.at<Vec3b > (j, i) = green;
            else if (response == -1)
                image.at<Vec3b > (j, i) = blue;
        }

    // Show the training data
    int thickness = -1;
    int lineType = 8;
    circle(image, Point(501, 10), 5, Scalar(0, 0, 0), thickness, lineType);
    circle(image, Point(255, 10), 5, Scalar(255, 255, 255), thickness, lineType);
    circle(image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
    circle(image, Point(10, 501), 5, Scalar(255, 255, 255), thickness, lineType);

    // Show support vectors
    thickness = 2;
    lineType = 8;
    int c = SVM.get_support_vector_count();

    for (int i = 0; i < c; ++i) {
        const float* v = SVM.get_support_vector(i);
        circle(image, Point((int) v[0], (int) v[1]), 6, Scalar(128, 128, 128), thickness, lineType);
    }

    imwrite("result.png", image); // save the image 

    imshow("SVM Simple Example", image); // show it to the user
    waitKey(0);
    return EXIT_SUCCESS;
}

#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Einfacher (beliebiger Test)">
#if /* Einfacher (beliebiger Test) */0

int main(int, char** argv) {
    ATest* test = new CreatePositiveSamplesTest();
    // ATest* test = new CreateNegativeSamplesTest();
    if (test->testMain(StringArray()) == EXIT_SUCCESS) {
        cout << "Test erfolgreich! :-)" << endl;
        return EXIT_SUCCESS;
    } else {
        cout << "Test fehlgeschlagen! :-(" << endl;
        return EXIT_FAILURE;
    }


}
#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Video zu Bildsequenz">
#if /* Video zu Bildsequenz */0
using namespace cv;
using namespace std;

int main(int, char** argv) {
    InputHandler handler = InputHandler();
    //    handler.setInputSource(INPUT_VIDEO);
    //    handler.addVideo("/home/ertai/Videos/VIDEO0026.mp4");
    //    handler.addVideo("/home/ertai/Videos/VIDEO0027.mp4");
    //    handler.addVideo("/home/ertai/Videos/VIDEO0028.mp4");
    handler.setInputSource(INPUT_CAM);

    if (!handler.open()) {
        DBG("Konnte Eingabe nicht öffnen");
        return EXIT_FAILURE;
    }
    handler.requestFormat(r720p);
    DBG("Lese einige Bilder damit Kamera sich einstellen kann(Helligkeit,Fokus,...).");
    for (int i = 0; i <= 10; i++) {
        if (!handler.grabNext()) {
            DBG("Fehler beim lesen der Eingabe");
        }
    }

    CvVideoCapture* cap = new CvVideoCapture(handler);
    /*Positive*/
    Output* out = new ImageListOutput("/home/ertai/Videos/FourFingers/POS", "POS1-", ".jpg");
    BgFgSegmModificator mod = BgFgSegmModificator("/home/ertai/Videos/FourFingers/BG/BG-126.jpg");
    cap->setImageModifikator(&mod);
    cap->setTimeToRecord(1500);
    cap->setRecordingTime(150000);

    /*Negative*/
    //            Output* out = new ImageListOutput("/home/ertai/Videos/FourFingers/BG", "BG-", ".jpg");
    //            cap->setRecordingTime(10);

    cap->setOutput(out);
    WindowManager* man = WindowManager::getInstance();
    CvWindow* wnd = man->createWindow("Recording", 0, 0);
    Mat img = handler.getImage();
    wnd->showWindow();
    wnd->setCurrentImage(&img);

    cap->setWindow(wnd);
    cap->start();



    cap->joinThread();
    man->closeWindow("Recording");
    cap->release();
    handler.releaseAll();
    return EXIT_SUCCESS;
}
#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         BgfgSegmentierung">
#if /* BgfgSegmentierung */0

#include <X11/Xlib.h>
using namespace cv;
using namespace std;



Mat bgimage;
Mat testImage;

int main(int, char** argv) {
    /**
     * Falls nicht gerufen... 
     *  [xcb] Unknown request in queue while dequeuing
     *  [xcb] Most likely this is a multi-threaded client and XInitThreads has not been called
     *  [xcb] Aborting, sorry about that.
     */
    XInitThreads();

    InputHandler handler = InputHandler();
    CvHelper* helper = CvHelper::getInstance();
    handler.setInputSource(INPUT_FOLDER);
    handler.addImageFolder("/home/ertai/Videos/Bg1");


    if (!handler.open()) {
        cout << "Konnte Eingabe nicht öffnen. " << endl << "Ordner: /home/ertai/Videos/Bg1" << endl;
        return EXIT_FAILURE;
    }

    Mat single;
    while (!handler.reachesEndOfInput()) {

        handler.next();
        Mat current = handler.getImage();
        if (single.empty()) {
            DBG("Setzte einzelnes Sample");
            single = current;
            break;
        }

    }



    Mat testImage = imread("/home/ertai/Videos/POS/pos1-0138.jpg");


    WindowManager* manager = WindowManager::getInstance();


    manager->createWindow("TestImg");
    manager->updateWindowImage("TestImg", &testImage);
    manager->showWindow("TestImg");

    Mat testImgF64 = Mat(testImage.size(), CV_64FC3);
    testImage.copyTo(testImgF64);
    Mat singleF64 = Mat(single.size(), CV_64FC3);
    single.copyTo(singleF64);


    Mat sdiff = Mat::zeros(singleF64.size(), CV_64FC3);
    absdiff(testImgF64, singleF64, sdiff);

    manager->createWindow("Sdiff");
    manager->updateWindowImage("Sdiff", &sdiff);
    manager->showWindow("Sdiff");

    Mat sdiffGray = Mat(sdiff.size(), CV_64FC1);
    cvtColor(sdiff, sdiffGray, CV_BGR2GRAY);

    Mat erg;

    Canny(sdiffGray, erg, 45.0f, 3.0f * 45.0f);

    Mat kernel = Mat::ones(3, 3, CV_8U);
    dilate(erg, erg, kernel, Point(-1, -1), 2);
    erode(erg, erg, kernel, Point(-1, -1), 2);

    ContourArray contours0;
    vector<Vec4i> hierarchy;
    findContours(erg, contours0, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_TC89_L1, Point(0, 0));
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





    vector<Point> contour;

    for (vector < vector<Point> >::const_iterator root = cont.begin(); root != cont.end(); root++) {
        vector<Point> current = (*root);
        for (vector<Point>::const_iterator contX = current.begin(); contX != current.end(); contX++) {
            contour.push_back((*contX));
        }
    }

    DBG("Got: %i contourpoints.", (int) contour.size());

    // Add last point to beginning & first point to end
    contour.insert(contour.begin(), cont[0].back());
    contour.insert(contour.end(), cont[0].front());

    vector<Point> triangleNodes;
    Point maxX, minX;
    Point maxY, minY;
    for (vector<Point>::const_iterator it = contour.begin(); it != contour.end(); it++) {
        Point pb = *it; //before
        Point p = *(it + 1); //current
        Point pn = *(it + 2); //next

        DBG("Steigung zwischen letztem und nächsten Punkt: %f", MyMath::calcPitch(pb, pn));
        if (p.x <= erg.size().width && p.x > 0) {
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

    DBG("Extema: (%i/%i),(%i/%i),(%i/%i),(%i/%i)", minX.x, minX.y, maxX.x, maxX.y, minY.x, minY.y, maxY.x, maxY.y);


    Mat ergC3 = Mat(erg.size(), CV_64FC3);
    cvtColor(erg, ergC3, CV_GRAY2BGR);

    Point x1, x2, x3, x4;
    x1 = Point(minX.x, minY.y);
    x2 = Point(maxX.x, minY.y);
    x3 = Point(minX.x, ((minY.y + MyMath::abs(minX.y - minY.y)*3) > ergC3.size().height) ? ergC3.size().height : (minY.y + MyMath::abs(minX.y - minY.y)*3));
    x4 = Point(maxX.x, ((minY.y + MyMath::abs(minX.y - minY.y)*3) > ergC3.size().height) ? ergC3.size().height : minY.y + MyMath::abs(minX.y - minY.y)*3);
    circle(ergC3, x1, 20, Scalar(255, 0, 0), -1);
    circle(ergC3, x2, 20, Scalar(0, 255, 0), -1);
    circle(ergC3, x3, 20, Scalar(0, 0, 255), -1);
    circle(ergC3, x4, 20, Scalar(255, 255, 0), -1);
    manager->createWindow("HandDetect");
    manager->updateWindowImage("HandDetect", &ergC3);
    manager->showWindow("HandDetect");



    waitKey(0);

    manager->relesase();
    single.release();
    sdiff.release();
    bgimage.release();
    testImage.release();
    testImgF64.release();


    return (0);

}



#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         cornerDetector_Demo">
#if /* cornerDetector_Demo */0

/**
 * @function cornerDetector_Demo.cpp
 * @brief Demo code for detecting corners using OpenCV built-in functions
 * @author OpenCV team
 */
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat src, src_gray;
Mat myHarris_dst;
Mat myHarris_copy;
Mat Mc;
Mat myShiTomasi_dst;
Mat myShiTomasi_copy;

int myShiTomasi_qualityLevel = 50;
int myHarris_qualityLevel = 50;
int max_qualityLevel = 100;

double myHarris_minVal;
double myHarris_maxVal;
double myShiTomasi_minVal;
double myShiTomasi_maxVal;

RNG rng(12345);

const char* myHarris_window = "My Harris corner detector";
const char* myShiTomasi_window = "My Shi Tomasi corner detector";

/// Function headers
void myShiTomasi_function(int, void*);
void myHarris_function(int, void*);

/**
 * @function main
 */
int main(int, char** argv) {
    /// Load source image and convert it to gray
    src = imread("handscene-1.png", 1);
    cvtColor(src, src_gray, CV_BGR2GRAY);

    /// Set some parameters
    int blockSize = 3;
    int apertureSize = 3;

    /// My Harris matrix -- Using cornerEigenValsAndVecs
    myHarris_dst = Mat::zeros(src_gray.size(), CV_32FC(6));
    Mc = Mat::zeros(src_gray.size(), CV_32FC1);

    cornerEigenValsAndVecs(src_gray, myHarris_dst, blockSize, apertureSize, BORDER_DEFAULT);

    /* calculate Mc */
    for (int j = 0; j < src_gray.rows; j++) {
        for (int i = 0; i < src_gray.cols; i++) {
            float lambda_1 = myHarris_dst.at<Vec6f > (j, i)[0];
            float lambda_2 = myHarris_dst.at<Vec6f > (j, i)[1];
            Mc.at<float>(j, i) = lambda_1 * lambda_2 - 0.04f * pow((lambda_1 + lambda_2), 2);
        }
    }

    minMaxLoc(Mc, &myHarris_minVal, &myHarris_maxVal, 0, 0, Mat());

    /* Create Window and Trackbar */
    namedWindow(myHarris_window, CV_WINDOW_AUTOSIZE);
    createTrackbar(" Quality Level:", myHarris_window, &myHarris_qualityLevel, max_qualityLevel, myHarris_function);
    myHarris_function(0, 0);

    /// My Shi-Tomasi -- Using cornerMinEigenVal
    myShiTomasi_dst = Mat::zeros(src_gray.size(), CV_32FC1);
    cornerMinEigenVal(src_gray, myShiTomasi_dst, blockSize, apertureSize, BORDER_DEFAULT);

    minMaxLoc(myShiTomasi_dst, &myShiTomasi_minVal, &myShiTomasi_maxVal, 0, 0, Mat());

    /* Create Window and Trackbar */
    namedWindow(myShiTomasi_window, CV_WINDOW_AUTOSIZE);
    createTrackbar(" Quality Level:", myShiTomasi_window, &myShiTomasi_qualityLevel, max_qualityLevel, myShiTomasi_function);
    myShiTomasi_function(0, 0);

    waitKey(0);
    return (0);
}

/**
 * @function myShiTomasi_function
 */
void myShiTomasi_function(int, void*) {
    myShiTomasi_copy = src.clone();

    if (myShiTomasi_qualityLevel < 1) {
        myShiTomasi_qualityLevel = 1;
    }

    for (int j = 0; j < src_gray.rows; j++) {
        for (int i = 0; i < src_gray.cols; i++) {
            if (myShiTomasi_dst.at<float>(j, i) > myShiTomasi_minVal + (myShiTomasi_maxVal - myShiTomasi_minVal) * myShiTomasi_qualityLevel / max_qualityLevel) {
                circle(myShiTomasi_copy, Point(i, j), 4, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1, 8, 0);
            }
        }
    }
    imshow(myShiTomasi_window, myShiTomasi_copy);
}

/**
 * @function myHarris_function
 */
void myHarris_function(int, void*) {
    myHarris_copy = src.clone();

    if (myHarris_qualityLevel < 1) {
        myHarris_qualityLevel = 1;
    }

    for (int j = 0; j < src_gray.rows; j++) {
        for (int i = 0; i < src_gray.cols; i++) {
            if (Mc.at<float>(j, i) > myHarris_minVal + (myHarris_maxVal - myHarris_minVal) * myHarris_qualityLevel / max_qualityLevel) {
                circle(myHarris_copy, Point(i, j), 4, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1, 8, 0);
            }
        }
    }
    imshow(myHarris_window, myHarris_copy);
}



#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         SURF_FlannMatcher">
#if /* SURF_FlannMatcher */0
/**
 * @file SURF_FlannMatcher
 * @brief SURF detector + descriptor + FLANN Matcher
 * @author A. Huaman
 */

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"

using namespace cv;

void readme();

/**
 * @function main
 * @brief Main function
 */
int main(int argc, char** argv) {

    Mat img_1 = imread("handref.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img_2 = imread("handscene-1.png", CV_LOAD_IMAGE_GRAYSCALE);
    GaussianBlur(img_1, img_1, Size(7, 7), 0.1, 0.1);
    Canny(img_1, img_1, 100, 300);
    Canny(img_2, img_2, 100, 300);
    if (!img_1.data || !img_2.data) {
        std::cout << " --(!) Error reading images " << std::endl;
        return -1;
    }

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 2000;

    SurfFeatureDetector detector(minHessian);

    KeyPointArray keypoints_1, keypoints_2;

    detector.detect(img_1, keypoints_1);
    detector.detect(img_2, keypoints_2);

    //-- Step 2: Calculate descriptors (feature vectors)
    SurfDescriptorExtractor extractor;

    Mat descriptors_1, descriptors_2;

    extractor.compute(img_1, keypoints_1, descriptors_1);
    extractor.compute(img_2, keypoints_2, descriptors_2);

    //-- Step 3: Matching descriptor vectors using FLANN matcher
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match(descriptors_1, descriptors_2, matches);

    double max_dist = 0;
    double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for (int i = 0; i < descriptors_1.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist);
    printf("-- Min dist : %f \n", min_dist);

    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
    //-- PS.- radiusMatch can also be used here.
    std::vector< DMatch > good_matches;

    for (int i = 0; i < descriptors_1.rows; i++) {
        if (matches[i].distance < 2 * min_dist) {
            good_matches.push_back(matches[i]);
        }
    }

    //-- Draw only "good" matches
    Mat img_matches;
    drawMatches(img_1, keypoints_1, img_2, keypoints_2,
            good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
            vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS | DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    //-- Show detected matches
    imshow("Good Matches", img_matches);

    for (int i = 0; i < (int) good_matches.size(); i++) {
        printf("-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx);
    }

    waitKey(0);

    return 0;
}

/**
 * @function readme
 */
void readme() {
    std::cout << " Usage: ./SURF_FlannMatcher <img1> <img2>" << std::endl;
}


#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         SURF_detector">
#if /* SURF_detector */0
/**
 * @file SURF_detector
 * @brief SURF keypoint detection + keypoint drawing with OpenCV functions
 * @author A. Huaman
 */

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"

using namespace cv;

void readme();

/**
 * @function main
 * @brief Main function
 */
int main(int argc, char** argv) {

    Mat img_1 = imread("handref.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img_2 = imread("handscene-1.png", CV_LOAD_IMAGE_GRAYSCALE);



    if (!img_1.data || !img_2.data) {
        std::cout << " --(!) Error reading images " << std::endl;
        return -1;
    }

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 800;

    SurfFeatureDetector detector(minHessian);

    KeyPointArray keypoints_1, keypoints_2;

    detector.detect(img_1, keypoints_1);
    detector.detect(img_2, keypoints_2);

    //-- Draw keypoints
    Mat img_keypoints_1;
    Mat img_keypoints_2;

    drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    //-- Show detected (drawn) keypoints
    imshow("Keypoints 1", img_keypoints_1);
    imshow("Keypoints 2", img_keypoints_2);

    waitKey(0);

    return 0;
}

/**
 * @function readme
 */
void readme() {
    std::cout << " Usage: ./SURF_detector <img1> <img2>" << std::endl;
}

#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         SURF_Homography">
#if /* SURF_Homography */0
/**
 * @file SURF_Homography
 * @brief SURF detector + descriptor + FLANN Matcher + FindHomography
 * @author A. Huaman
 */

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/features2d.hpp"

using namespace cv;

void readme();

/**
 * @function main
 * @brief Main function
 */
int main(int argc, char** argv) {


    Mat img_object = imread("handref.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img_scene = imread("handscene-1.png", CV_LOAD_IMAGE_GRAYSCALE);

    if (!img_object.data || !img_scene.data) {
        std::cout << " --(!) Error reading images " << std::endl;
        return -1;
    }

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;

    SurfFeatureDetector detector(minHessian);

    KeyPointArray keypoints_object, keypoints_scene;

    detector.detect(img_object, keypoints_object);
    detector.detect(img_scene, keypoints_scene);

    //-- Step 2: Calculate descriptors (feature vectors)
    SurfDescriptorExtractor extractor;

    Mat descriptors_object, descriptors_scene;

    extractor.compute(img_object, keypoints_object, descriptors_object);
    extractor.compute(img_scene, keypoints_scene, descriptors_scene);

    //-- Step 3: Matching descriptor vectors using FLANN matcher
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match(descriptors_object, descriptors_scene, matches);

    double max_dist = 0;
    double min_dist = 20;


    //-- Quick calculation of max and min distances between keypoints
    for (int i = 0; i < descriptors_object.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist);
    printf("-- Min dist : %f \n", min_dist);

    //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
    std::vector< DMatch > good_matches;

    for (int i = 0; i < descriptors_object.rows; i++) {
        if (matches[i].distance < 3 * min_dist) {
            good_matches.push_back(matches[i]);
        }
    }

    Mat img_matches;
    drawMatches(img_object, keypoints_object, img_scene, keypoints_scene,
            good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
            vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);


    //-- Localize the object from img_1 in img_2
    std::vector<Point2f> obj;
    std::vector<Point2f> scene;

    for (size_t i = 0; i < good_matches.size(); i++) {
        //-- Get the keypoints from the good matches
        obj.push_back(keypoints_object[ good_matches[i].queryIdx ].pt);
        scene.push_back(keypoints_scene[ good_matches[i].trainIdx ].pt);
    }

    Mat H = findHomography(obj, scene, CV_RANSAC);

    //-- Get the corners from the image_1 ( the object to be "detected" )
    std::vector<Point2f> obj_corners(4);
    obj_corners[0] = cvPoint(0, 0);
    obj_corners[1] = cvPoint(img_object.cols, 0);
    obj_corners[2] = cvPoint(img_object.cols, img_object.rows);
    obj_corners[3] = cvPoint(0, img_object.rows);
    std::vector<Point2f> scene_corners(4);

    perspectiveTransform(obj_corners, scene_corners, H);


    //-- Draw lines between the corners (the mapped object in the scene - image_2 )
    Point2f offset((float) img_object.cols, 0);
    line(img_matches, scene_corners[0] + offset, scene_corners[1] + offset, Scalar(0, 255, 0), 4);
    line(img_matches, scene_corners[1] + offset, scene_corners[2] + offset, Scalar(0, 255, 0), 4);
    line(img_matches, scene_corners[2] + offset, scene_corners[3] + offset, Scalar(0, 255, 0), 4);
    line(img_matches, scene_corners[3] + offset, scene_corners[0] + offset, Scalar(0, 255, 0), 4);

    //-- Show detected matches
    imshow("Good Matches & Object detection", img_matches);

    waitKey(0);

    return 0;
}

/**
 * @function readme
 */
void readme() {
    std::cout << " Usage: ./SURF_Homography <img1> <img2>" << std::endl;
}
#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Kinect">
#if /*Kinect*/0
#ifdef TRY_KINECT
using namespace cv;
using namespace std;
using namespace Freenect;

#include <libfreenect.hpp>
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

class Mutex {
public:

    Mutex() {
        pthread_mutex_init(&m_mutex, NULL);
    }

    void lock() {
        pthread_mutex_lock(&m_mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&m_mutex);
    }
private:
    pthread_mutex_t m_mutex;
};

/* thanks to Yoda---- from IRC */
class MyFreenectDevice : public FreenectDevice {
public:
    //FreenectDevice(_ctx, _index), m_buffer_depth(FREENECT_DEPTH_11BIT), m_buffer_rgb(FREENECT_VIDEO_RGB), m_gamma(2048), m_new_rgb_frame(false), m_new_depth_frame(false), depthMat(Size(640, 480), CV_16UC1), rgbMat(Size(640, 480), CV_8UC3, Scalar(0)), ownMat(Size(640, 480), CV_8UC3, Scalar(0)

    MyFreenectDevice(freenect_context *_ctx, int _index)
    : FreenectDevice(_ctx, _index), m_buffer_depth(FREENECT_DEPTH_11BIT), m_buffer_video(FREENECT_VIDEO_RGB), m_gamma(2048), m_new_rgb_frame(false), m_new_depth_frame(false) {
        for (unsigned int i = 0; i < 2048; i++) {
            float v = i / 2048.0;
            v = std::pow(v, 3)* 6;
            m_gamma[i] = v * 6 * 256;
        }
    }
    // Do not call directly even in child

    void VideoCallback(void* _rgb, uint32_t timestamp) {
        std::cout << "RGB callback" << std::endl;
        m_rgb_mutex.lock();
        uint8_t* rgb = static_cast<uint8_t*> (_rgb);
        std::copy(rgb, rgb + FREENECT_VIDEO_RGB, m_buffer_video.begin());
        m_new_rgb_frame = true;
        m_rgb_mutex.unlock();
    };
    // Do not call directly even in child

    void DepthCallback(void* _depth, uint32_t timestamp) {
        std::cout << "Depth callback" << std::endl;
        m_depth_mutex.lock();
        uint16_t* depth = static_cast<uint16_t*> (_depth);
        for (unsigned int i = 0; i < FREENECT_DEPTH_11BIT; i++) {
            int pval = m_gamma[depth[i]];
            int lb = pval & 0xff;
            switch (pval >> 8) {
                case 0:
                    m_buffer_depth[3 * i + 0] = 255;
                    m_buffer_depth[3 * i + 1] = 255 - lb;
                    m_buffer_depth[3 * i + 2] = 255 - lb;
                    break;
                case 1:
                    m_buffer_depth[3 * i + 0] = 255;
                    m_buffer_depth[3 * i + 1] = lb;
                    m_buffer_depth[3 * i + 2] = 0;
                    break;
                case 2:
                    m_buffer_depth[3 * i + 0] = 255 - lb;
                    m_buffer_depth[3 * i + 1] = 255;
                    m_buffer_depth[3 * i + 2] = 0;
                    break;
                case 3:
                    m_buffer_depth[3 * i + 0] = 0;
                    m_buffer_depth[3 * i + 1] = 255;
                    m_buffer_depth[3 * i + 2] = lb;
                    break;
                case 4:
                    m_buffer_depth[3 * i + 0] = 0;
                    m_buffer_depth[3 * i + 1] = 255 - lb;
                    m_buffer_depth[3 * i + 2] = 255;
                    break;
                case 5:
                    m_buffer_depth[3 * i + 0] = 0;
                    m_buffer_depth[3 * i + 1] = 0;
                    m_buffer_depth[3 * i + 2] = 255 - lb;
                    break;
                default:
                    m_buffer_depth[3 * i + 0] = 0;
                    m_buffer_depth[3 * i + 1] = 0;
                    m_buffer_depth[3 * i + 2] = 0;
                    break;
            }
        }
        m_new_depth_frame = true;
        m_depth_mutex.unlock();
    }

    bool getRGB(std::vector<uint8_t> &buffer) {
        m_rgb_mutex.lock();
        if (m_new_rgb_frame) {
            buffer.swap(m_buffer_video);
            m_new_rgb_frame = false;
            m_rgb_mutex.unlock();
            return true;
        } else {
            m_rgb_mutex.unlock();
            return false;
        }
    }

    bool getDepth(std::vector<uint8_t> &buffer) {
        m_depth_mutex.lock();
        if (m_new_depth_frame) {
            buffer.swap(m_buffer_depth);
            m_new_depth_frame = false;
            m_depth_mutex.unlock();
            return true;
        } else {
            m_depth_mutex.unlock();
            return false;
        }
    }

private:
    std::vector<uint8_t> m_buffer_depth;
    std::vector<uint8_t> m_buffer_video;
    std::vector<uint16_t> m_gamma;
    Mutex m_rgb_mutex;
    Mutex m_depth_mutex;
    bool m_new_rgb_frame;
    bool m_new_depth_frame;
};

Freenect::Freenect freenect;
MyFreenectDevice* device;

GLuint gl_depth_tex;
GLuint gl_rgb_tex;

bool die;
double freenect_angle(0);
int got_frames(0), window(0);
int g_argc;
char **g_argv;

void DrawGLScene() {
    static std::vector<uint8_t> depth(640 * 480 * 4);
    static std::vector<uint8_t> rgb(640 * 480 * 4);

    device->getDepth(depth);
    device->getRGB(rgb);

    got_frames = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, &depth[0]);

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(640, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(640, 480, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 480, 0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, &rgb[0]);

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
    glTexCoord2f(0, 0);
    glVertex3f(640, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(1280, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(1280, 480, 0);
    glTexCoord2f(0, 1);
    glVertex3f(640, 480, 0);
    glEnd();

    glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y) {
    /*  FreenectDeviceState::getState() doesnt really work as expected */
    //double freenect_angle = device->getState().getTiltDegs();

    if (key == 27) {
        die = 1;
        glutDestroyWindow(window);
    }
    if (key == 'w') {
        freenect_angle++;
        if (freenect_angle > 30) {
            freenect_angle = 30;
        }
    }
    if (key == 's') {
        freenect_angle = 0;
    }
    if (key == 'x') {
        freenect_angle--;
        if (freenect_angle < -30) {
            freenect_angle = -30;
        }
    }
    if (key == '1') {
        device->setLed(LED_GREEN);
    }
    if (key == '2') {
        device->setLed(LED_RED);
    }
    if (key == '3') {
        device->setLed(LED_YELLOW);
    }
    if (key == '4') {
        device->setLed(LED_BLINK_GREEN);
    }
    if (key == '5') {
        device->setLed(LED_BLINK_GREEN);
    }
    if (key == '6') {
        device->setLed(LED_BLINK_RED_YELLOW);
    }
    if (key == '0') {
        device->setLed(LED_OFF);
    }
    device->setTiltDegrees(freenect_angle);
}

void ReSizeGLScene(int Width, int Height) {
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1280, 480, 0, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void InitGL(int Width, int Height) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glGenTextures(1, &gl_depth_tex);
    glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenTextures(1, &gl_rgb_tex);
    glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    ReSizeGLScene(Width, Height);
}

void *gl_threadfunc(void *arg) {
    printf("GL thread\n");

    glutInit(&g_argc, g_argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(1280, 480);
    glutInitWindowPosition(0, 0);

    window = glutCreateWindow("LibFreenect");

    glutDisplayFunc(&DrawGLScene);
    glutIdleFunc(&DrawGLScene);
    glutReshapeFunc(&ReSizeGLScene);
    glutKeyboardFunc(&keyPressed);

    InitGL(1280, 480);

    glutMainLoop();

    return NULL;
}

int main(int argc, char **argv) {
    device = &freenect.createDevice<MyFreenectDevice > (0);
    device->startVideo();
    device->startDepth();
    gl_threadfunc(NULL);
    device->stopVideo();
    device->stopDepth();
    return 0;
}
#endif

#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Test-Routinen">
#if /*Test-Routinen*/0

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    MainTest test = MainTest();
    StringArray argsVec;
    if (argc > 1) {
        String tmp;
        for (int i = 1; i < argc; i++) {
            tmp = String(argv[i]);
            argsVec.push_back(tmp);
        }
    }
    test.putTest(new WindowManagerTest());
    if (test.testMain(argsVec) == EXIT_SUCCESS) {
        DBG("Alle Tests erfolgreich");
    }

}


#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Histogram_Equalization">
#if /*Histogram_Equalization*/0

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {

    InputHandler input = InputHandler();
    input.setInputSource(INPUT_CAM);
    //input.addVideo("/home/ertai/Videos/VIDEO0023.mp4");
    input.open();

    if (input.requestFormat(r720p)) {
        DBG("Auflösung geändert");
    }
    //    CvVideoCapture cap(input);
    //    cap.setFramesToRecord(50000);
    //    cap.setTimeToRecord(15);
    //ImageListOutput out("/home/ertai/NetBeansProjects/OpenCvPraktikum/imgseq_out", "bg4");
    //    cap.setOutput(&out);
    //    RecorderCtl ctl = RecorderCtl("Test");
    //    ctl.setCapture(&cap);

    //    ctl.startGrabInput();
    //    sleep(1);
    //    ctl.startRecording();
    //    sleep(15);
    //    ctl.stopRecording();
    //    ctl.stopGrabbing();
    CvHelper* help = CvHelper::getInstance();
    Mat grid = Mat::zeros(Size(800, 600), CV_8UC3);
    Mat frame;
    StringArray tags = StringArray();
    tags.push_back("Normal");
    tags.push_back("Gauß");
    tags.push_back("Hist.Eq.");
    tags.push_back("Hist pre");
    tags.push_back("Hist post");

    while (true) {
        input.next();
        frame = input.getImage();
        vector<Mat*> images;
        grid = help->equalizeHistogram(frame, true, true);

    }

    return EXIT_SUCCESS;

}
#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Praktikum 3">
#if /*Praktikum 3*/0

Mat origImage;
int cannyLow = 1, cannyHigh = 350;

void doCanny() {
    Mat cannyImage, cannyImageInv;

    Canny(origImage, cannyImage, cannyLow, cannyHigh);
    threshold(cannyImage, cannyImageInv, 128, 255, THRESH_BINARY_INV);
    imshow("Canny", cannyImageInv);
}

void callbackCanny(int pos) {
    doCanny();
    DBG("canny erneut mit lowThreshold = %d, highThreshold = %d angewendet!", cannyLow, cannyHigh);
}

int main() {
    CvHelper *help = CvHelper::getInstance();

    origImage = imread("hands.png");
    Mat sobelX, sobelY, sobel;


    MatND histo;
    Mat histImg;
    namedWindow("Bild");
    namedWindow("BinBild");
    namedWindow("Histogram");
    namedWindow("SobelX");
    namedWindow("SobelY");
    namedWindow("Canny");
    namedWindow("Alle");

    cvCreateTrackbar("CannyTrack", "Canny",
            &cannyLow, 255, callbackCanny);
    cvCreateTrackbar("CannyTrackHigh", "Canny",
            &cannyHigh, 400, callbackCanny);



    Sobel(origImage, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
    Sobel(origImage, sobelY, CV_8U, 0, 1, 3, 0.4, 128);

    sobel = sobelX;
    double sobelMin, sobelMax;

    minMaxLoc(sobel, &sobelMin, &sobelMax);
    Mat image, binImage, all;
    sobel.convertTo(image, CV_8U, -255.0 / sobelMax, 255);
    threshold(image, binImage, 30, 255, cv::THRESH_BINARY);

    Mat cannyImage, cannyImageInv;

    Canny(origImage, cannyImage, 125, 350);
    threshold(cannyImage, cannyImageInv, 128, 255, THRESH_BINARY_INV);



    histo = help->makeHist(&image);
    histImg = help->makeHistImage(histo);


    DBG("Baue Vektoren");
    vector<Mat*> images = vector<Mat*>();
    images.push_back(&image);
    images.push_back(&binImage);
    images.push_back(&sobelX);
    images.push_back(&sobelY);
    images.push_back(&histImg);
    images.push_back(&cannyImageInv);
    StringArray tags = StringArray();
    tags.push_back("Bild");
    tags.push_back("BinBild");
    tags.push_back("SobelX");
    tags.push_back("SobelY");
    tags.push_back("Histogram");
    tags.push_back("Canny");

    all = help->buildImageGrid(images, tags, Scalar(0, 0, 255, 0), 3, 1280, 1024);
    imshow("Bild", image);
    imshow("BinBild", binImage);
    imshow("SobelX", sobelX);
    imshow("SobelY", sobelY);
    imshow("Histogram", histImg);
    imshow("Canny", cannyImageInv);
    imshow("Alle", all);
    waitKey(300);

    waitKey(0);

    printf("bin am ende !\n");

    return EXIT_SUCCESS;
}

#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         HS-Histogram">
#if /*HS-Histogram*/0



#include <cstdio>
#include <string>
#include <vector>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/nonfree/nonfree.hpp"


using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    int hesse = 400;

    Mat input1 = imread("bild1.png", CV_LOAD_IMAGE_GRAYSCALE);
    InputHandler* handler = new InputHandler();
    handler->setInputSource(INPUT_CAM);
    handler->requestFormat(INPUT_FORMAT::r720p);
    handler->open();
    handler->grabNext();
    Mat input2;

    if (input1.data == NULL) {
        DBG_EXIT(" --(!) Error reading images ");

    }



    CvHelper* help = CvHelper::getInstance();


    namedWindow("H-S Histogram");
    while (true) {
        handler->grabNext();
        input2 = handler->getImage();
        MatND histo = help->makeHSHist(input2);
        help->makeHSHistImage(histo);
        DBG("Histogram Erstellt")
        help->applySurfDetect(input1, input2, hesse, 10, 50);
        int c = waitKey(1);

        if (c != -1) {
            break;
        }
    }
    return EXIT_SUCCESS;







}

#endif
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="                         Harris_Eckendetektor">
#if /*Harris_Eckendetektor*/0 


using namespace cv;
using namespace std;

Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;
String source_window = "Source image";
String corners_window = "Corners detected";

void cornerHarris_demo(int, void*);

/** @function main */
int main(int argc, char** argv) {
    /// Load source image and convert it to gray
    src = imread("bild1.png", 1);
    cvtColor(src, src_gray, CV_BGR2GRAY);
    /// Create a window and a trackbar
    namedWindow(source_window, CV_WINDOW_AUTOSIZE);
    createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
    imshow(source_window, src);
    cornerHarris_demo(0, 0);
    waitKey(0);
    return (0);

}

/** @function cornerHarris_demo */
void cornerHarris_demo(int, void*) {
    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros(src.size(), CV_32FC1);
    /// Detector parameters
    int blockSize = 1;
    int apertureSize = 3;
    double k = 0.04;
    /// Detecting corners
    cornerHarris(src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);
    /// Normalizing
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);
    /// Drawing a circle around corners
    for (int j = 0; j < dst_norm.rows; j++) {
        for (int i = 0; i < dst_norm.cols; i++) {
            if ((int) dst_norm.at<float>(j, i) > thresh) {
                circle(dst_norm_scaled, Point(i, j), 5,
                        Scalar(0), 2, 8, 0);
            }
        }
    }
    /// Showing the result
    namedWindow(corners_window, CV_WINDOW_AUTOSIZE);
    imshow(corners_window, dst_norm_scaled);
}

#endif
// </editor-fold>





// Tipp: falls dir das Erstellen immer zu lange dauert, 
// gehe in den Projektordner und führe von dort 'make -j N' aus -> N anzahl der synchronen "JOBS" (Zeitersparniss auf meinem PhenomII ~ 1min zu 12sec)...


// Samples erstellen    
//                        Erstellte Textdatei mit Markierungen                   Ergebnisdatei                     Groesse der Samples      Zeigt die Samples an.
//opencv_createsamples -info /home/ertai/Videos/positives.dat -num 2500 -vec /home/ertai/Videos/train_plainHand.vec -w 50 -h 50                 (show)
// Training
//                           Ergebnis                positive Samples            negative       Anzahl der positiven und negativen     Anzahl der Stages       Performancewerte, je groesser desto besser        Erzeugter Typ     (wie bei Sampleerstellung)       Mindest Trefferqoute des Ergebnisses     Hoechste Fehlerrate des Ergebisses(!kleinere Werte können Laufzeit um Tage verlaengern.)                                                    
//opencv_traincascade -data Videos/cascade   -vec Videos/train_plainHand.vec  -bg Videos/bg.dat    -numPos 222 -numNeg 1500               -numStages 5      -precalcValBufSize 3096 -precalcIdxBufSize 3096    -featureType LBP         -w 64 -h 64                             -minHitRate 0.999               -maxFalseAlarmRate 0.1                                                                  -mode ALL