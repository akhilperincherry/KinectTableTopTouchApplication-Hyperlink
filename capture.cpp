#include "capture.h"

Capture::Capture()
{
    capture = VideoCapture( CV_CAP_OPENNI );

     if( !capture.isOpened() )
     {
         cout << "Can not open a capture object." << endl;
         exit(1);
     }

     capture.set( CV_CAP_OPENNI_IMAGE_GENERATOR_OUTPUT_MODE, CV_CAP_OPENNI_VGA_30HZ );

     if( !capture.grab() )
     {
         cout << "Can not grab images." << endl;
         exit(1);
     }

     isSetH = false;
     isDepthDone = false;
}

void Capture::update()
{

    if( !capture.grab() )
    {
       // cout << "Can not grab images." << endl;
        exit(1);
    }

    capture.retrieve( openni_disparity_map_32F, CV_CAP_OPENNI_DISPARITY_MAP_32F );
    capture.retrieve( openni_bgr_image, CV_CAP_OPENNI_BGR_IMAGE );
    openni_disparity_map_32F.convertTo(openni_depth_8U,CV_8UC1,2.0f);

    //cout<<"HERE I AM 2"<<endl;

    if(isSetH)
    {

        cv::warpPerspective(openni_depth_8U,rect_depth,H,cv::Size(SCREEN_WIDTH,SCREEN_HEIGHT));
        cv::warpPerspective(openni_bgr_image,rect_rgb,H,cv::Size(SCREEN_WIDTH,SCREEN_HEIGHT));
    }
    if(isDepthDone)
    {
        capture.retrieve( openni_depth_map_32F, CV_CAP_OPENNI_DEPTH_MAP);
        int histSize = 256;

        float range[] = { 200, 2500 } ;
        const float* histRange = { range };


        calcHist(&openni_depth_map_32F,1,0,Mat(),histogram,1,&histSize,&histRange,true,false);
        int hist_w = histSize;
        int hist_h = 400;
        int bin_w = cvRound( (double) hist_w/histSize );

        histDisp=Mat::zeros(hist_h,hist_w,CV_8UC3);
        cv::normalize(histogram,histogram,0,histDisp.rows,NORM_MINMAX,-1,Mat());

        double maxVal=0,minVal=0;
        Point maxPt,minPt;

        minMaxLoc(histogram,&minVal,&maxVal,&minPt,&maxPt);

        float avgDist=0;
        avgDist=(range[1]-range[0])/histSize;
        avgDist*=maxPt.y;
        avgDist+=range[0];
        cout<<"Average Distance= "<<avgDist<<" mm"<<endl;
        RNG rng1;
        for( int i = 1; i < histSize; i++ )
        {


            int r=rng1.uniform(0,255);
            int g=rng1.uniform(0,255);
            int b=rng1.uniform(0,255);

            rectangle(histDisp,Point( bin_w*(i-1), hist_h - cvRound(histogram.at<float>(i-1)) ) ,
                      Point( bin_w*(i), hist_h - cvRound(histogram.at<float>(i)) ),
                      cv::Scalar(r,g,b),8);
        }
        imshow("DepthCalibration",histDisp);
        waitKey();
        isDepthDone=true;
    }

}

void Capture::setH(Mat _H)
{
    if( !isSetH )
    {
        H = _H;
        isSetH = true;
    }

}

