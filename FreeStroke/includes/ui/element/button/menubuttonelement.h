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
 * \file menubuttonelement.h
 * \brief The MenuButtonElement class represent a custom button that is either selected or not and has a different look
 *  dependant to its state. Such buttons are made to be placed in a menu side by side.
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef MENUBUTTONELEMENT_H
#define MENUBUTTONELEMENT_H

#include "../element.h"

/*!
 * \brief The MenuButtonElement class represent a custom button that is either selected or not and has a different look
 *  dependant to its state. Such buttons are made to be placed in a TopBar side by side.
 */
class MenuButtonElement : public QAbstractButton, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief the default MenuButtonElement constructor
     * \param pIcon the icon of the MenuButtonElement while not selected
     * \param pIconSelected the icon of the MenuButtonElement while selected
     * \param parent the container QWidget parent
     */
    MenuButtonElement(QPixmap pIcon, QPixmap pIconSelected, QWidget *parent = 0);
    /*!
     * \brief set the position of the MenuButtonElement
     * \param pX the desired x
     * \param pY the desired y
     */
    void setPosition(int pX, int pY);
    /*!
     * \brief set whether or not the MenuButtonElement is selected
     * \param pSelected boolean that set whether or not the MenuButtonElement is selected
     */
    void setSelected(bool pSelected);
    /*!
     * \brief set the MenuButtonElement as the last one of the menu which add a line of pixel to its right border
     * \param pLast boolean which set the MenuButtonElement as the last one of the menu
     */
    void setLast(bool pLast);

private:
    /*!
     * \brief boolean which hold the value of wether or not the MenuButtonElement is the last one of the menu
     */
    bool isLast;
    /*!
     * \brief the icon of the MenuButtonElement while not selected
     */
    QPixmap *pixmap;
    /*!
     * \brief the icon of the MenuButtonElement while selected
     */
    QPixmap *pixmapSelected;
    /*!
     * \brief the background of the MenuButtonElement while selected
     */
    QPixmap *pixmapBackgroundSelected;

protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
};

#endif // MENUBUTTONELEMENT_H
