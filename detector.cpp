#include "detector.h"

Detector::Detector()
{
    erosion_type = cv::MORPH_RECT;
    erosion_size = 1;

    element = getStructuringElement( erosion_type,Size( 2*erosion_size+1, 2*erosion_size+1 ),
                                                               Point( erosion_size, erosion_size ) );

}

void Detector::detect( Mat depthImage)
{

    depthImage.copyTo(depth);

    Mat m1,m2,m3,m4;

//    threshold(depth,m1,85,255,CV_THRESH_BINARY);
//    threshold(depth,m2,84,255,CV_THRESH_BINARY);

    threshold(depth,m1,88,255,CV_THRESH_BINARY);
    threshold(depth,m2,87,255,CV_THRESH_BINARY);

//    threshold(depth,m1,88,255,CV_THRESH_BINARY);
//    threshold(depth,m2,87,255,CV_THRESH_BINARY);

    m3=m2-m1;

    erode(m3,m4,element,Point(-1,-1),1);
    dilate(m4,m4,element,Point(-1,-1),4);
    threshold(m4,m4,200,255,CV_THRESH_BINARY);

  //  imshow("m4",m4);

    findContours(m4,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);


}
