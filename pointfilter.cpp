#include "pointfilter.h"


PointFilter::PointFilter()
{
    nextid = 0;


}

void PointFilter::resetFlags()
{

    for( int i = 0 ; i < pointList.size() ; i++ )
        pointList[i].released = true;
}

void PointFilter::mergeRects( RotatedRect &r1, RotatedRect &r2 )
{
    r1.angle = ( r1.angle + r2.angle )/2;
    r1.center.x = ( r1.center.x + r2.center.x )/2;
    r1.center.y = ( r1.center.y + r2.center.y )/2;
    r1.size.width = ( r1.size.width + r2.size.width )/2;
    r1.size.height = ( r1.size.height + r2.size.height )/2;
}


float PointFilter::getDistance(RotatedRect rect, TouchPoint tpoint)
{
    Point point = tpoint.point;
    float dist = sqrt( (point.x-rect.center.x)*(point.x-rect.center.x) +
                      (point.y-rect.center.y)*(point.y-rect.center.y) );

    return dist;
}

bool PointFilter::checkPoint(RotatedRect rect, TouchPoint tpoint)
{
    Point point = tpoint.point;

    float dist = sqrt( (point.x-rect.center.x)*(point.x-rect.center.x) +
                      (point.y-rect.center.y)*(point.y-rect.center.y) );

    float velocity = sqrt(tpoint.velocity.x*tpoint.velocity.x + tpoint.velocity.y*tpoint.velocity.y);
    float acceleration = sqrt(tpoint.acceleration.x*tpoint.acceleration.x + tpoint.acceleration.y*tpoint.acceleration.y);


    float radius = sqrt( rect.size.area() * (velocity+1) / 3.1416 );

    cout<<endl<<"Distance:"<<dist<<" Radius:"<<radius<<" Velocity:"<<velocity<<" Acceleration:"<<acceleration<<endl;

    if( dist < radius ) return true;
    else
        false;

}

void PointFilter::addPoint( vector < vector < Point > > &contours )
{

    time_t ctime = clock();

    vector < vector < Point > > ::iterator itr;

    for( itr = contours.begin() ; itr < contours.end() ; itr++ )
    {
        if( itr->size() > 100 )
            itr = contours.erase(itr);
        else                              //wont this anyway happen ?!?
            itr++;
    }

    vector<RotatedRect> minRect( contours.size() );
    vector<RotatedRect> minEllipse( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
    {

            minRect[i] = minAreaRect( Mat(contours[i]) );

            if( contours[i].size() > 5 )
            {
                minEllipse[i] = fitEllipse( Mat(contours[i]) );
            }

    }

    if( pointList.size() == 0 )
    {
        for( int i = 0 ; i < contours.size() ; i++ )   //How will there br contours when there are no touchpoints ?
        {
            TouchPoint tp;
            tp.point = minRect[i].center;
            tp.rect = minRect[i];
            tp.ellipse = minEllipse[i];
            tp.epoch = tp.current = tp.previous = ctime;
            tp.pressure = 100;
            tp.ID = i;
            tp.acceleration = tp.velocity = Point(0,0);
            tp.released = false;
            pointList.push_back(tp);
        }

        nextid = contours.size();
    }

    else
    {
        resetFlags();


        for( int i = 0 ; i < contours.size() ; i++ )
        {
                bool added = false;



            for( int j = 0; j < pointList.size() && !added ; j++ )
            {

                if( pointList[j].released &&  checkPoint(minRect[i],pointList[j]) )
                {

                    pointList[j].released = false;

                    Point prev_point = pointList[j].point;
                    Point prev_vel = pointList[j].velocity;

                    pointList[j].point.x = minRect[i].center.x/2 + pointList[j].point.x/2;
                    pointList[j].point.y = minRect[i].center.y/2 + pointList[j].point.y/2;

                    mergeRects(pointList[j].rect,minRect[i]);
                    mergeRects(pointList[j].ellipse,minEllipse[i]);

                    pointList[j].velocity = Point(prev_point - pointList[j].point);
                    pointList[j].acceleration = prev_vel - pointList[j].velocity;

                    pointList[i].previous = pointList[i].current;
                    pointList[i].current = ctime;

                    if( (minRect[i].size.height * minRect[i].size.width) > 250 )
                        pointList[j].nfingers = 2;
                    else
                        pointList[j].nfingers = 1;


                    float velocity = sqrt(pointList[j].velocity.x*pointList[j].velocity.x + pointList[j].velocity.y*pointList[j].velocity.y);
                    cout<<endl<<"Modified:"<<pointList[j].point<<" Velocity:"<<velocity<<endl;

                    added = true;

                }


          }


                if( !added )
                {
                    TouchPoint tp;
                    tp.point = minRect[i].center;
                    tp.rect = minRect[i];
                    tp.ellipse = minEllipse[i];
                    tp.epoch = tp.current = tp.previous = ctime;
                    tp.pressure = 100;
                    tp.ID = nextid;
                    tp.acceleration = tp.velocity = Point(0,0);
                    tp.released = false;
                    pointList.push_back(tp);
                    nextid++;

                    cout<<endl<<"**Added:"<<tp.point;

                }

        }

        for ( int i = 0; i < pointList.size() ; i++ )
        {

            if( pointList[i].released == true )
            {
                pointList.erase(pointList.begin() + i);
            }
        }

    }

}
