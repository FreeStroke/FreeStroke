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
 * \file combobox.h
 * \brief The ComboBox class is a QComboBox with a custom skin
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "../element.h"

/*!
 * \brief The ComboBox class is a QComboBox with a custom skin
 */
class ComboBox : public QComboBox, public Element
{
	Q_OBJECT
public:
    /*!
     * \brief the default ComboBox constructor
     * \param w the container QWidget parent
     */
	ComboBox(QWidget * w = 0);
protected:
	void paintEvent(QPaintEvent * e);

private:
    QPixmap *pixmap;

};

#endif
