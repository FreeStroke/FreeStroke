#include <QtCore/QDebug>

#include "../../includes/others/linux/linux.h"

#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <X11/keysym.h>


void Linux::generateKeyEvent(unsigned short keyCode, bool shiftModifier, bool ctrlModifier, bool metaModifier, bool altModifier, bool altGrModifier)
{

    // Obtain the X11 display.
       Display *display = XOpenDisplay(0);
       if(display == NULL)
          return;

    // Get the root window for the current display.
       Window winRoot = XDefaultRootWindow(display);

    // Find the window which has the current keyboard focus.
       Window winFocus;
       int    revert;
       XGetInputFocus(display, &winFocus, &revert);

    // Modifiers
       int modifiers=0;
       if (shiftModifier)
       {
           modifiers |= XK_SHIFT_MOD;
       }
       if (ctrlModifier)
       {
           modifiers |= XK_CTRL_MOD;
       }
       if (metaModifier)
       {
           modifiers |= XK_CTRL_MOD;
       }
       if (altModifier)
       {
           modifiers |= XK_CTRL_MOD;
       }
       if (altGrModifier)
       {
           modifiers |= XK_CTRL_MOD;
       }

    // Send a fake key press event to the window.
       XKeyEvent event = Linux::createKeyEvent(display, winFocus, winRoot, true, keyCode, modifiers);
       XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    // Send a fake key release event to the window.
       event = createKeyEvent(display, winFocus, winRoot, false, keyCode, modifiers);
       XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    // Done.
       XCloseDisplay(display);

}

// Function to create a keyboard event
XKeyEvent Linux::createKeyEvent(Display *display, Window &win,
                           Window &winRoot, bool press,
                           int keycode, int modifiers)
{
   XKeyEvent event;

   event.display     = display;
   event.window      = win;
   event.root        = winRoot;
   event.subwindow   = None;
   event.time        = CurrentTime;
   event.x           = 1;
   event.y           = 1;
   event.x_root      = 1;
   event.y_root      = 1;
   event.same_screen = True;
   event.keycode     = XKeysymToKeycode(display, keycode);
   event.state       = modifiers;

   if(press)
      event.type = KeyPress;
   else
      event.type = KeyRelease;

   return event;
}
