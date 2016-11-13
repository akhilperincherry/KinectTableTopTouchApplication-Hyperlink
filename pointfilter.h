#ifndef POINTFILTER_H
#define POINTFILTER_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <vector>
#include <time.h>

#include "touchpoint.h"
#include "mousecontroller.h"

using namespace std;
using namespace cv;

class PointFilter
{
public:

    vector < TouchPoint > pointList;
    PointFilter();
    void addPoint( vector < vector < Point > > &contours );
    void resetFlags();
    void mergeRects( RotatedRect &r1 , RotatedRect &r2 );
    bool checkPoint( RotatedRect rect, TouchPoint tpoint );
    float getDistance(RotatedRect rect, TouchPoint tpoint);
    int nextid;
};

#endif // POINTFILTER_H
