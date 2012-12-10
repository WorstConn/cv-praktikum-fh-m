/* 
 * File:   Window.h
 * Author: julian
 *
 * Created on 10. Dezember 2012, 15:50
 */

#ifndef WINDOW_H
#define	WINDOW_H
#include "../header.h"

using namespace std;
using namespace cv;
class Window {
public:
    Window(String name,int width = 0, int height = 0);
    Window(const Window& orig);
    void setCurrentImage(Mat *current);
    void showWindow();
    virtual ~Window();
private:
    String name;
    int width, height;
    Mat *currentImage;
    

};

#endif	/* WINDOW_H */

