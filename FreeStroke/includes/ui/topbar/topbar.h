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
 * \file topbar.h
 * \brief The TopBar class is a QWidget with no margin and no spacing which is made to hold MenuButtonElement.
 * Its height is fixed to 50. It uses a QButtonGroup so that only one MenuButtonElement can be selected at a time
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef TOPBAR_H
#define TOPBAR_H

#include <QtGui/QWidget>
#include <QtGui/QButtonGroup>

#include "../element/button/menubuttonelement.h"
/*!
 * \brief The TopBar class is a QWidget with no margin and no spacing which is made to hold MenuButtonElement.
 * Its height is fixed to 50. It uses a QButtonGroup so that only one MenuButtonElement can be selected at a time
 */
class TopBar : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief default TopBar constructor
     * \param parent the container QWidget parent
     */
    TopBar(QWidget *parent = 0);
    /*!
     * \brief add a MenuButtonElement to the TopBar
     * \param pButton the desired MenuButtonElement
     */
    void addButton(MenuButtonElement * pButton);

protected:
    void paintEvent(QPaintEvent *e);

private:
    /*!
     * \brief the QButtonGroup used to be able to select only one MenuButtonElement at a time
     */
      QButtonGroup *group;
};

#endif // TOPBAR_H
