#ifndef TOUCHPOINT_H
#define TOUCHPOINT_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
using namespace cv;

class TouchPoint
{

public:

    Point point;
    RotatedRect rect;
    RotatedRect ellipse;
    Point velocity;
    Point acceleration;
    int ID;
    int nfingers;
    int pressure;
    time_t epoch;
    time_t current;
    time_t previous;
    bool released;

    TouchPoint();
};

#endif // TOUCHPOINT_H
