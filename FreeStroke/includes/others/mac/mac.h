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
 * \file mac.h
 * \brief Contains methods for generating key events on MacOSX systems
 * \author Sylvain Fay-Chatelard
 * \date 2013-02-20
 */
#ifndef MAC_H
#define MAC_H

#include <QtCore>
#include <QtWidgets>

class Mac : public QObject
{
	Q_OBJECT
public:
    Mac(QWidget* w = 0);

    /*!
     * \brief Dislays a notification in MacOSX environment
     * \param pTitle title of the popup
     * \param pMessage message displayed
     */
    void showNotification(char *pTitle, char *pMessage);

    /*!
     * \brief Converts a Qt keycode to MacOSX system keycode
     * \param keyCode QT keycode (Qt::Key)
     * \return the native MacOSX keycode
     */
    static int convertToCGKeyCode(short keyCode);

    /*!
     * \brief Simulates a key event and sends it to the system (on linux distributions only)
     * \param keyCode native code of the key to generate
     * \param shiftModifier modifier shift key
     * \param ctrlModifier modifier ctrl key
     * \param optionModifier modifier optn key
     * \param cmdModifier modifier cmd key
     */
    void static generateKeyEvent(unsigned short keyCode, bool shiftModifier, bool ctrlModifier, bool metaModifier, bool altModifier, bool altGrModifier);
};

#endif
