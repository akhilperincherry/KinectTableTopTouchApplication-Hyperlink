#include "touchpoint.h"

TouchPoint::TouchPoint()
{
    this->point = Point(-1,-1);
    this->rect = RotatedRect();
    this->ellipse = RotatedRect();
    this->velocity = Point(0,0);
    this->acceleration = Point(0,0);
    this->nfingers = 1;
    this->released = true;

}
