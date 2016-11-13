#include "mousecontroller.h"
using namespace std;

MouseController::MouseController()
{
      MyDisplay = XOpenDisplay(NULL);

       if(MyDisplay == NULL)
       {
               cout<< "Error: Error inintialising the display\n";
               exit(EXIT_FAILURE);
       }

       memset(&MouseEvent, 0x00, sizeof(MouseEvent));

       state = UP;
       p_x = 0;
       p_y = 0;

}

MouseController::~MouseController()
{
     XCloseDisplay(MyDisplay);
}


void MouseController::MouseMoveBy(int dx , int dy)
{

        XWarpPointer(MyDisplay, None, None, 0, 0, 0, 0, dx, dy);
        p_x += dx;
        p_y += dy;
        XFlush(MyDisplay);


}

void MouseController::MouseMoveTo(int x , int y)
{

        Window Root = DefaultRootWindow(MyDisplay);

        XWarpPointer(MyDisplay, 0, Root, 0, 0, 0, 0, x, y);
        p_x = x;
        p_y = y;
        XFlush(MyDisplay);


}

void MouseController::ButtonDown(int Button_ID)
{

    MouseEvent.type = ButtonPress;
    MouseEvent.xbutton.button = Button_ID;
    MouseEvent.xbutton.same_screen = True;

    XQueryPointer(MyDisplay, RootWindow(MyDisplay, DefaultScreen(MyDisplay)),
                  &MouseEvent.xbutton.root, &MouseEvent.xbutton.window, &MouseEvent.xbutton.x_root,
                  &MouseEvent.xbutton.y_root, &MouseEvent.xbutton.x, &MouseEvent.xbutton.y,
                  &MouseEvent.xbutton.state);

    MouseEvent.xbutton.subwindow = MouseEvent.xbutton.window; //child win = event win

    while(MouseEvent.xbutton.subwindow)
    {
            MouseEvent.xbutton.window = MouseEvent.xbutton.subwindow; //event win = child win

            XQueryPointer(MyDisplay, MouseEvent.xbutton.window, &MouseEvent.xbutton.root,
                          &MouseEvent.xbutton.subwindow, &MouseEvent.xbutton.x_root,
                          &MouseEvent.xbutton.y_root, &MouseEvent.xbutton.x, &MouseEvent.xbutton.y,
                          &MouseEvent.xbutton.state);

    }


    int IsSuccess = XSendEvent(MyDisplay, PointerWindow, True, 0xfff, &MouseEvent);

    if(!IsSuccess) cout<< "Error: Could not complete Mouse Event\n";

    XFlush(MyDisplay);

    state = DOWN;

}

void MouseController::ButtonUp(int Button_ID)
{

    MouseEvent.type = ButtonRelease;
    MouseEvent.xbutton.button = Button_ID;
    MouseEvent.xbutton.same_screen = True;
    MouseEvent.xbutton.state = 0x100;

    XQueryPointer(MyDisplay, RootWindow(MyDisplay, DefaultScreen(MyDisplay)),
                  &MouseEvent.xbutton.root, &MouseEvent.xbutton.window, &MouseEvent.xbutton.x_root,
                  &MouseEvent.xbutton.y_root, &MouseEvent.xbutton.x, &MouseEvent.xbutton.y,
                  &MouseEvent.xbutton.state);

    MouseEvent.xbutton.subwindow = MouseEvent.xbutton.window;

    while(MouseEvent.xbutton.subwindow)
    {
            MouseEvent.xbutton.window = MouseEvent.xbutton.subwindow;

            XQueryPointer(MyDisplay, MouseEvent.xbutton.window, &MouseEvent.xbutton.root,
                          &MouseEvent.xbutton.subwindow, &MouseEvent.xbutton.x_root,
                          &MouseEvent.xbutton.y_root, &MouseEvent.xbutton.x, &MouseEvent.xbutton.y,
                          &MouseEvent.xbutton.state);

    }

    int IsSuccess = XSendEvent(MyDisplay, PointerWindow, True, 0xfff, &MouseEvent);

    if(!IsSuccess) cout<< "Error: Could not complete Mouse Event\n";

    XFlush(MyDisplay);

    state = UP;

}

void MouseController::MouseScroll(int Button_ID , int Button_State)
{

    MouseEvent.type = ButtonRelease;
    MouseEvent.xbutton.button = Button_ID;
    MouseEvent.xbutton.same_screen = True;
    MouseEvent.xbutton.state = Button_State;

    XQueryPointer(MyDisplay, RootWindow(MyDisplay, DefaultScreen(MyDisplay)),
                  &MouseEvent.xbutton.root, &MouseEvent.xbutton.window, &MouseEvent.xbutton.x_root,
                  &MouseEvent.xbutton.y_root, &MouseEvent.xbutton.x, &MouseEvent.xbutton.y,
                  &MouseEvent.xbutton.state);

    MouseEvent.xbutton.subwindow = MouseEvent.xbutton.window;

    while(MouseEvent.xbutton.subwindow)
    {
            MouseEvent.xbutton.window = MouseEvent.xbutton.subwindow;

            XQueryPointer(MyDisplay, MouseEvent.xbutton.window, &MouseEvent.xbutton.root,
                          &MouseEvent.xbutton.subwindow, &MouseEvent.xbutton.x_root,
                          &MouseEvent.xbutton.y_root, &MouseEvent.xbutton.x, &MouseEvent.xbutton.y,
                          &MouseEvent.xbutton.state);

    }

    int IsSuccess = XSendEvent(MyDisplay, PointerWindow, True, 0xfff, &MouseEvent);

    if(!IsSuccess) cout<< "Error: Could not complete Mouse Event\n";

    XFlush(MyDisplay);

    state = UP;

}

void MouseController::MouseSingleClick(int Button_ID)
{

       MouseEvent.type = ButtonPress;
       MouseEvent.xbutton.button = Button_ID;
       MouseEvent.xbutton.same_screen = True;

       XQueryPointer(MyDisplay, RootWindow(MyDisplay, DefaultScreen(MyDisplay)),
                     &MouseEvent.xbutton.root, &MouseEvent.xbutton.window, &MouseEvent.xbutton.x_root,
                     &MouseEvent.xbutton.y_root, &MouseEvent.xbutton.x, &MouseEvent.xbutton.y,
                     &MouseEvent.xbutton.state);

       MouseEvent.xbutton.subwindow = MouseEvent.xbutton.window;

       while(MouseEvent.xbutton.subwindow)
       {
               MouseEvent.xbutton.window = MouseEvent.xbutton.subwindow;

               XQueryPointer(MyDisplay, MouseEvent.xbutton.window, &MouseEvent.xbutton.root,
                             &MouseEvent.xbutton.subwindow, &MouseEvent.xbutton.x_root,
                             &MouseEvent.xbutton.y_root, &MouseEvent.xbutton.x, &MouseEvent.xbutton.y,
                             &MouseEvent.xbutton.state);

       }


       int IsSuccess = XSendEvent(MyDisplay, PointerWindow, True, 0xfff, &MouseEvent);

       if(!IsSuccess) cout<< "Error: Could not complete Mouse Event\n";

       XFlush(MyDisplay);

       usleep(100000);


       MouseEvent.type = ButtonRelease;
       MouseEvent.xbutton.state = 0x100;

       IsSuccess = XSendEvent(MyDisplay, PointerWindow,True, 0xfff, &MouseEvent);

       if(!IsSuccess) cout<< "Error: Could not complete Mouse Event \n";

       XFlush(MyDisplay);

}

void MouseController::MouseDoubleClick(int Button_ID)
{

    MouseSingleClick(Button_ID);
    usleep(100000);
    MouseSingleClick(Button_ID);

}

void MouseController::MouseHoldAndDrag(int Button_ID, int x, int y)
{


        Window root = DefaultRootWindow(MyDisplay);


        MouseEvent.type = ButtonPress;
        MouseEvent.xbutton.button = Button_ID;
        MouseEvent.xbutton.same_screen = True;



        XQueryPointer(MyDisplay, RootWindow(MyDisplay, DefaultScreen(MyDisplay)),
                      &MouseEvent.xbutton.root, &MouseEvent.xbutton.window, &MouseEvent.xbutton.x_root,
                      &MouseEvent.xbutton.y_root, &MouseEvent.xbutton.x, &MouseEvent.xbutton.y, &MouseEvent.xbutton.state);

        MouseEvent.xbutton.subwindow = MouseEvent.xbutton.window;

        while(MouseEvent.xbutton.subwindow)
        {
                MouseEvent.xbutton.window = MouseEvent.xbutton.subwindow;

                XQueryPointer(MyDisplay, MouseEvent.xbutton.window, &MouseEvent.xbutton.root,
                              &MouseEvent.xbutton.subwindow, &MouseEvent.xbutton.x_root,
                              &MouseEvent.xbutton.y_root, &MouseEvent.xbutton.x, &MouseEvent.xbutton.y, &MouseEvent.xbutton.state);

        }



        int IsSuccess = XSendEvent(MyDisplay, PointerWindow, True, 0xfff, &MouseEvent);

        if(!IsSuccess) printf("Error: Could not complete Mouse Event\n");



        XWarpPointer(MyDisplay,0,root, 0, 0, 0, 0, x, y);


        MouseEvent.type = ButtonRelease;
        MouseEvent.xbutton.state = 0x100;

        IsSuccess = XSendEvent(MyDisplay, PointerWindow, True, 0xfff, &MouseEvent);

        if(!IsSuccess) printf("Error: Could not complete Mouse Event \n");

        XFlush(MyDisplay);



}
