#include <iostream>
#include <vector>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <iomanip>
#include <locale>
#include <sstream>
#include <string>

#include "capture.h"
#include "setup.h"
#include "pointfilter.h"
#include "detector.h"
#include "mousecontroller.h"

#include <baseapi.h>
#include <allheaders.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h> //Contains image processing functions of tesseract

using namespace std;
using namespace cv;


int main()
{
    Capture capture;
    Setup setup;
    Detector detector;
    PointFilter pointFilter;
    //MouseController mc;

    capture.setH(setup.getHomography());



int ctr = 0;
int A,B,C;
A=B=C=0;
int frame_nos = 0;
int offset_x,offset_y;
offset_x=0;
offset_y=0;

double x_syn, y_syn, err_dist;
err_dist=0.0;

//namedWindow("mywindow",CV_WINDOW_AUTOSIZE);

//namedWindow("mywindow",CV_WINDOW_FULLSCREEN);

Mat img=imread("/home/msb/Desktop/Sample Images/phototest.tif");
Mat img_calib = imread("/home/msb/Desktop/Sample Images/phototest.tif");
int drag = 0, select_flag = 0;
Point point1, point2;


    int state = 0;
    int calib = 0;
    int exit =0;

    Scalar red = Scalar(0,0,255);
    Scalar green = Scalar(0,255,0);
    Scalar blue = Scalar(255,0,0);


    //Homography for synchronisation of cursor and finger

    CvPoint2D32f cpts[4],tpts[4];


    cpts[0].x=20;cpts[0].y=20; // Image relative coordinates
    cpts[1].x=620;cpts[1].y=20;
    cpts[2].x=620;cpts[2].y=460;
    cpts[3].x=20;cpts[3].y=460;

    tpts[0].x=60;tpts[0].y=86; // Image relative coordinates
    tpts[1].x=363;tpts[1].y=68;
    tpts[2].x=357;tpts[2].y=269;
    tpts[3].x=76;tpts[3].y=268;

/* CALIBRATION */

//    namedWindow("Calibration",CV_WINDOW_NORMAL);
//    cout<<"CALIBRATION PHASE STARTING......"<<endl;

//    while(calib!=4)
//    {
//       // waitKey();
//    capture.update();
//    detector.detect(capture.rect_depth);
//    pointFilter.addPoint(detector.contours);
//    circle(img_calib,Point(cpts[calib].x,cpts[calib].y),10,green,-1,8,0);
//    imshow("Calibration",img_calib);
//    waitKey(1501);

//    cout<<endl<<"Touch the coloured point !!"<<endl;

//    if(pointFilter.pointList.size() == 1 && !exit)
//    {

//      if(calib != 0 && pointFilter.pointList.size() == 1)
//      {
//          tpts[calib].x = pointFilter.pointList[0].point.x;
//          tpts[calib].y = pointFilter.pointList[0].point.y;

//        err_dist= sqrt(((tpts[calib].x-tpts[calib-1].x)*(tpts[calib].x-tpts[calib-1].x))
//                  +((tpts[calib].y-tpts[calib-1].y)*(tpts[calib].y-tpts[calib-1].y)));
//        cout<<"Eucl. Dist. "<<calib<<": "<<err_dist<<endl;
//      }


//    if(err_dist>125 || calib == 0 && pointFilter.pointList.size() == 1)
//    {
//        cout<<"Eucl. Dist. "<<calib<<": "<<err_dist<<endl;
//        tpts[calib].x = pointFilter.pointList[0].point.x;
//        tpts[calib].y = pointFilter.pointList[0].point.y;
//        exit = 1;
//        cout<<"Touch Point "<<calib<<": "<<tpts[calib].x<<" , "<<tpts[calib].y<<endl;
//         calib++;
//    }



//    }
//    exit = 0;
//    cout<<"Point Count so far: "<<calib<<endl;
//    }

//    cout<<"END OF CALIBRATION"<<endl;
//    cout<<endl<<"OBTAINED TOUCH POINTS...."<<endl;
//    for(int k=0;k<4;k++)
//        cout<<"Touch point "<<k<<" :" <<tpts[k].x<<","<<tpts[k].y<<endl;
//    cout<<"END !!"<<endl;

//    waitKey();

    /*END OF CALIBRATION*/

            CvMat *mapMatrix = cvCreateMat(3,3,CV_32FC1);
            cvGetPerspectiveTransform( tpts,cpts,mapMatrix );

            CvMat *Point1,*TransformedPoint;
            Point1=cvCreateMat(3,1,CV_32FC1);
            TransformedPoint=cvCreateMat(3,1,CV_32FC1);


    namedWindow("UI",CV_WINDOW_NORMAL);
    imshow("UI",img);

    while(1)
    {
        capture.update();
       // imshow("stream",capture.rect_rgb);
       // waitKey();
        //frame_nos++;
        //cout<<frame_nos<<endl;
        detector.detect(capture.rect_depth);
        pointFilter.addPoint(detector.contours);
                 waitKey(10);

     if(!select_flag)
       {
        if( state == 0 && pointFilter.pointList.size() == 1 && !drag)
        {
            A++;
            state = 1;

            cvmSet(Point1,0,0,pointFilter.pointList[0].point.x);
            cvmSet(Point1,1,0,pointFilter.pointList[0].point.y);
            cvmSet(Point1,2,0,1);

            cvMatMul(mapMatrix, Point1, TransformedPoint);

             x_syn=cvmGet(TransformedPoint,0,0)/cvmGet(TransformedPoint,2,0);
            y_syn=cvmGet(TransformedPoint,1,0)/cvmGet(TransformedPoint,2,0);

          // cout<<"X: "<< x_syn<<"   Y: "<<y_syn<<endl;

        point1 = Point(x_syn+offset_x,y_syn+offset_y);
                drag = 1;

                cout<<"Point 1 - state A: "<<point1.x<<","<<point1.y<<endl;

                circle(img,point1,8,red,-1,8,0);
                imshow("UI", img);
               // waitKey(500);

//&& ((++ctr)>30)
x_syn=y_syn=0;
for(int a=0;a<20;a++);

        }

        if( state == 1 && pointFilter.pointList.size() == 1 && drag )
        {
            B++;
            cout<<"ctr: "<<ctr<<endl;

            cout<<"A count:"<<A<<endl<<"B count:"<<B<<endl<<"C count:"<<C<<endl;
            cout<<"Frames:"<<frame_nos<<endl;

            cvmSet(Point1,0,0,pointFilter.pointList[0].point.x);
            cvmSet(Point1,1,0,pointFilter.pointList[0].point.y);
            cvmSet(Point1,2,0,1);

            cvMatMul(mapMatrix, Point1, TransformedPoint);

            x_syn=cvmGet(TransformedPoint,0,0)/cvmGet(TransformedPoint,2,0);
            y_syn=cvmGet(TransformedPoint,1,0)/cvmGet(TransformedPoint,2,0);


           point2 = Point(x_syn+offset_x,y_syn+offset_y);

        circle(img,point2,5,blue,-1,8,0);
        namedWindow("UI",CV_WINDOW_AUTOSIZE);
        imshow("UI", img);
        waitKey(500);

          drag=0;
          select_flag=1;

        }

        }


     if(select_flag)
        {

         cout<<"Inside OCR block"<<endl;
      //  waitKey(0);
       // select_flag=0;

        vector<float> tlx,tly;
        vector<int> width,height;


        int xt = point2.x;
        int yt = point2.y;

         int w =0;
        vector<float> xwvec, ywvec;

        int rect_x, rect_y, rect_width, rect_height ;

        double min=0, max=0;
        int minID=0, maxID=0;

          Pix *image = pixRead("/home/msb/Desktop/Sample Images/phototest.tif");
          tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
          api->Init(NULL, "eng");
          api->SetImage(image);
          Boxa* boxes1 = api->GetComponentImages(tesseract::RIL_WORD, true, NULL, NULL);
          Boxa* boxes2 = api->GetComponentImages(tesseract::RIL_TEXTLINE, true, NULL, NULL);

          int word_ctr = boxes1->n;
          int line_ctr = boxes2->n;

          for (int i = 0; i < word_ctr; i++)
          {
            BOX* box1 = boxaGetBox(boxes1, i, L_CLONE);
            api->SetRectangle(box1->x, box1->y, box1->w, box1->h);

            tlx.push_back(box1->x);
            tly.push_back(box1->y);
            width.push_back(box1->w);
            height.push_back(box1->h);

         }

          cout<<endl<<"LINES"<<endl;

          for (int j = 0; j < line_ctr; j++)
          {
            BOX* box2 = boxaGetBox(boxes2, j, L_CLONE);
            api->SetRectangle(box2->x, box2->y, box2->w, box2->h);
         }

         int line_nos = floor((yt-92)/34);

         cout<<endl<<"Line no.: "<<line_nos<<endl;

         BOX* box3 = boxaGetBox(boxes2, line_nos, L_CLONE);
         api->SetRectangle(box3->x, box3->y, box3->w, box3->h);
        int xl=box3->x;
        int yl=box3->y;

        cout <<"Line Cordinates: "<<xl<<","<<yl<<endl;

        for (int k = 0; k < word_ctr; k++)
        {
          BOX* box1 = boxaGetBox(boxes1, k, L_CLONE);
          api->SetRectangle(box1->x, box1->y, box1->w, box1->h);

          if(box1->y >=yl && box1->y < (yl+30))
          {

              xwvec.push_back(box1->x);
               ywvec.push_back(box1->y);

              w++;
           }

        }
         cout<<"count of words in that particular line: "<<w<<endl;

         Mat bxw = Mat(xwvec);    // vector -> Mat
          Mat byw = Mat(ywvec);
        Mat xtMat=Mat(w,1,CV_32FC1,xt);   // scalar -> Mat

            Mat diffx = xtMat - bxw;

            for (int matctr=0; matctr < w; matctr++)
            {
                if(diffx.at<float>(matctr)<0)
                diffx.at<float>(matctr)=1000;

            }


        //    cout<<"Abscissa of all words in the line: "<<bxw<<endl;
         //   cout<<"Ordinate of all words in the line: "<<byw<<endl;
         //   cout<<"Difference of touch point and all abscissas in the sentence: "<<diffx<<endl;

            minMaxIdx(diffx, &min, &max, &minID, &maxID, Mat());
         //   cout<<"Minimum element: "<<min<<","<<"Maximum element: "<<max<<"--"<<"Min Index: "<<minID<<","<<"Max Index: "<<maxID<<endl;

        int word_x = bxw.at<float>(minID);
        int word_y = byw.at<float>(minID);

        cout<<"Detected word at: "<<word_x<<","<<word_y<<endl;

        Mat word_xMat=Mat(word_ctr,1,CV_32FC1,word_x);
        Mat word_yMat=Mat(word_ctr,1,CV_32FC1,word_y);

        Mat tlx_mat = Mat(tlx);
        Mat tly_mat = Mat(tly);

        Mat fin_diffx = tlx_mat - word_xMat;
        Mat fin_diffy = tly_mat - word_yMat;

        for(int l =0; l<word_ctr; l++)
        {
            if (fin_diffx.at<float>(l) == 0 && fin_diffy.at<float>(l) == 0)
            {
                int final_index = l;
                cout<<final_index<<"nd word"<<endl;
                cout<<"X: "<<word_x<<" Y: "<<word_y<<" Width: "<<width[final_index]<<" Height: "<<height[final_index]<<endl;

                rect_x = word_x; rect_y = word_y; rect_width = width[final_index]; rect_height = height[final_index];

            }
        }

        api->SetRectangle(rect_x, rect_y, rect_width, rect_height);
        char *final_word = api->GetUTF8Text();
        cout<<"Selected Word: "<<final_word<<endl;
//


                       char domain[100] = "http://images.google.com/images?q=";
                       strcat(domain,final_word);

                 //  execl ("/usr/bin/chromium-browser","/usr/bin/chromium-browser",domain,(char*)0);
                     execl ("/usr/bin/espeak","/usr/bin/espeak",final_word,(char*)0);



    }
    select_flag=0;
     state =0;
    }
    return 0;
}






