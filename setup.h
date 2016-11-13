#ifndef SETUP_H
#define SETUP_H


#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

#define USE_GUI 0
#define USE_DEF 1

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300

class Setup
{
private:

    int mode;
    Mat homography;


public:
    Setup();
    Mat getHomography();
};

#endif // SETUP_H
