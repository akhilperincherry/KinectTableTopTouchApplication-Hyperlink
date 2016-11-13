#ifndef DETECTOR_H
#define DETECTOR_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

#include "capture.h"

using namespace cv;
using namespace std;



class Detector
{
private:
    int erosion_type;
    int erosion_size;
    Mat element;
    Mat depth;

public:
    Detector();
    void detect( Mat depthImage );
    vector < vector < Point > > contours;
};

#endif // DETECTOR_H
