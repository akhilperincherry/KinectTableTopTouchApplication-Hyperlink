#include "setup.h"

Setup::Setup()
{

}


Mat Setup::getHomography()
{
/*

192 116
508 120
508 352
192 346

*/

    std::vector < cv::Point2f > pts;
    pts.push_back(cv::Point2f(180, 222));
    pts.push_back(cv::Point2f(488, 234));
    pts.push_back(cv::Point2f(486, 466));
    pts.push_back(cv::Point2f(164, 454));

    std::vector < cv::Point2f > disp;
    disp.push_back(cv::Point2f(0,0));
    disp.push_back(cv::Point2f(SCREEN_WIDTH,0));
    disp.push_back(cv::Point2f(SCREEN_WIDTH,SCREEN_HEIGHT));
    disp.push_back(cv::Point2f(0,SCREEN_HEIGHT));


    homography = cv::findHomography(pts,disp,CV_RANSAC);



    return homography;
}
