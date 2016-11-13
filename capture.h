#ifndef CAPTURE_H
#define CAPTURE_H


#ifndef LIB_INCLUDE
#define LIB_INCLUDE

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300

#endif // LIB_INCLUDE


class Capture
{


public:

    Capture();
    void update();
    void setH(Mat _H);
    VideoCapture capture;

    Mat openni_disparity_map_32F,openni_bgr_image,openni_depth_8U,openni_depth_map_32F;
    Mat histogram;
    Mat histDisp;
    Mat rect_rgb,rect_depth;
    Mat H;
    bool isSetH;
    bool isDepthDone;
};

#endif // CAPTURE_H
