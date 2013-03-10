/*!
 * \file linux.h
 * \brief Contains methods for generating key events on Linux distributions
 * \author Camille.D
 * \date 2013-02-20
 */
#ifndef LINUX_H
#define LINUX_H

#include <QtCore/QObject>
#include <QtGui/QWidget>

#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <X11/keysym.h>


#define XK_SHIFT_MOD (1<<0)
#define XK_CTRL_MOD (1<<2)
#define XK_META_MOD (1<<2)
#define XK_ALT_MOD (1<<2)
#define XK_ALTGR_MOD (1<<2)

/*!
 * \brief Class providing key events generations on Linux.
 * Contains methods for generating key events on Linux distributions
 */
class Linux : public QObject
{
	Q_OBJECT
public:
    /*!
     * \brief Creates XKeyEvent structure from X11 API
     * \param display the window configuration
     * \param win the window object
     * \param winRoot the focussed window
     * \param press flag for key pressed / released
     * \param keycode code of the key to generate in the event
     * \param modifiers code of key modifiers (shift / ctrl)
     * \return a configured key event
     */
    static XKeyEvent createKeyEvent(Display *display, Window &win,
                               Window &winRoot, bool press,
                               int keycode, int modifiers);

    /*!
     * \brief Simulates a key event and sends it to the system (on linux distributions only)
     * \param keyCode native code of the key to generate
     * \param shiftModifier modifier shift key
     * \param ctrlModifier modifier ctrl key
     * \param optionModifier modifier optn key
     * \param cmdModifier modifier cmd key
     */
    static void generateKeyEvent(unsigned short keyCode, bool shiftModifier, bool ctrlModifier, bool metaModifier, bool altModifier, bool altGrModifier);
};

#endif // LINUX_H
