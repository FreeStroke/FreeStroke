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
 * \file windows.h
 * \brief Contains methods for generating key events on Windows 7 system
 * \author Anthony Fourneau
 * \date 2013-02-20
 */
#ifndef WINDOWS_H
#define WINDOWS_H

class Windows : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief main constructor
     * \param w
     */
    Windows(QWidget* w = 0);

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

#endif // WINDOWS_H
