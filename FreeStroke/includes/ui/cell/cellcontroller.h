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
 * \file cellcontroller.h
 * \brief The Cell controller class represent a specific cell used to display available controllers
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */
#ifndef CELLCONTROLLER_H
#define CELLCONTROLLER_H

#include "../../includes/ui/cell/cell.h"
#include "../../includes/common/controller.h"

/*!
 * \brief The Cell controller class represent a specific cell used to display available controllers
 */
class CellController : public Cell
{
public:
    /*!
     * \brief Main controller
     * \param pList list of available controllers
     */
    explicit CellController(void* pList);

    /*!
     * \brief Setter for controller association to the ell
     * \param pController the controller to associate
     */
    void setController(Controller* pController);

private:
    Label* labelController; /*!< The label used to display the controllers name */
    QLabel* iconChoose;  /*!< The icon used displayed next to the controllers name */

protected:
    void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent *e);
};

#endif // CELLCONTROLLER_H
