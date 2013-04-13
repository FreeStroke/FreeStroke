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
 * \file bottombar.h
 * \author Sylvain Fay-Châtelard
 * \date 2013/03/07
 * \brief The BottomBar class represent a container for Element and BottomBarSeparator of 52 pixels heights.
 *  It has no external margin and contents margin of 10,0,10,0 (left, top, right, bottom).
 *
 */
#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include "../element/element.h"
#include "../bottombar/bottombarseparator.h"

/*!
 * \brief The BottomBar class represent a container for Element and BottomBarSeparator of 52 pixels heights.
 *  It has no external margin and contents margin of 10,0,10,0 (left, top, right, bottom).
 */
class BottomBar : public QWidget
{

    Q_OBJECT
public:
    /*!
     * \brief The BottomBar default constructor
     * \param parent the parent container QWidget
     */
    BottomBar(QWidget *parent = 0);
    /**
     * @brief add an Element to the BottomBar
     */
    void addElement(Element *);
    /**
     * @brief add a BottomBarSeparator to the BottomBar
     */
    void addSeparator();

    /*!
     * \brief defines whether or not the BottomBar will have a line painted to its right border
     * \param pPrint the boolean defining whether or not the BottomBar will have a line painted to its right border
     */
    void addLeftLine(bool pPrint);
    /*!
     * \brief defines whether or not the BottomBar will have a line painted to its right border
     * \param pPrint the boolean defining whether or not the BottomBar will have a line painted to its right border
     */
    void addRightLine(bool pPrint);

    /*!
     * \brief defines whether or not the BottomBar's bottom border will be painted to its top border instead
     * \param pSetTopBar the boolean defining whether or not the BottomBar's bottom border will be painted to its top border instead
     */
    void setTopBar(bool pSetTopBar);

protected:
    void paintEvent(QPaintEvent *);

private:
    bool printLeft; /*!< the boolean defining whether or not the BottomBar will have a line painted to its right border*/
    bool printRight; /*!< the boolean defining whether or not the BottomBar will have a line painted to its left border*/
    bool isTopBar; /*!< the boolean defining whether or not the BottomBar's bottom border will be painted to its top border instead*/
};

#endif // BOTTOMBAR_H
