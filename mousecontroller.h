#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

#include <time.h>


#define LEFT_BUTTON 1
#define RIGHT_BUTTON 3
#define MID_BUTTON 2

#define SCROLL_UP 4
#define SU_STATE 0x810

#define SCROLL_DOWN 5
#define SD_STATE 0x1010

#define UP 1
#define DOWN 2




class MouseController
{
public:
    MouseController();
    ~MouseController();
    void ButtonDown(int Button_ID);
    void ButtonUp(int Button_ID);
    void MouseSingleClick(int Button_ID);
    void MouseMoveTo(int x, int y);
    void MouseMoveBy(int dx, int dy);
    void MouseDoubleClick(int Button_ID);
    void MouseHoldAndDrag(int Button_ID, int x, int y);
    void MouseScroll(int Button_ID , int Button_State);

    Display *MyDisplay;
    XEvent MouseEvent;
    int state;
    int p_x,p_y;
};

#endif // MOUSECONTROLLER_H
