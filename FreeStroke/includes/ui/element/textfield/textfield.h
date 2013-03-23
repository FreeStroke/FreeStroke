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
 * \file textfield.h
 * \brief The TextField class is a QLineEdit with a custom skin
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef TEXTFIELDELEMENT_H
#define TEXTFIELDELEMENT_H

#include <QtGui/QLineEdit>

#include "../element.h"

/*!
 * \brief The TextField class is a QLineEdit with a custom skin
 */
class TextField : public QLineEdit, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief default TextField constructor
     * \param parent the container QWidget parent
     */
    TextField(QWidget *parent = 0);
    /*!
     * \brief set the position of the TextField
     * \param pX the desired x
     * \param pY the desired y
     */
    void setPosition(int pX, int pY);
    /*!
     * \brief set the text of the TextField
     * \param pText the desired text
     */
    void setText(QString pText);

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void paintEvent(QPaintEvent *e);
    void focusOutEvent(QFocusEvent *);

signals:
    /*!
     * \brief lostFocus is the signal sent when the focus has been lost
     */
    void lostFocus();
};

#endif // TEXTFIELDELEMENT_H
