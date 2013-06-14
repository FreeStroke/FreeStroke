/*
* Projet de fin d'études LastProject de
* Adrien Broussolle
* Camille Darcy
* Guillaume Demurger
* Sylvain Fay-Chatelard
* Anthony Fourneau
* Aurèle Lenfant
* Adrien Madouasse
*
* Copyright (C) 2013 Université Paris-Est Marne-la-Vallée
*
* FreeStroke is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
*/
/*!
 * \file linux.h
 * \brief Contains methods for generating key events on Linux distributions
 * \author Camille.D
 * \date 2013-02-20
 */
#ifndef LINUX_H
#define LINUX_H

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
class Linux
{
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
