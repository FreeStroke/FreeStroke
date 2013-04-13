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
 * \file gesturefeature.h
 * \brief Abstract class for gesture-oriented features
 * \author Camille.D
 * \date 2013-02-12
 */
#ifndef GESTUREFEATURE_H
#define GESTUREFEATURE_H

#include "../../includes/gestures/data/inputgesture.h"

/*!
 * \class GestureFeature
 * \brief Abstract class for gesture-oriented features
 * Contains functions for querying and printing feature results
 */
class GestureFeature
{
public:
    /*!
     * \brief Executes the feature algo on an input gesture
     * \param pIg the input gesture used to compute the result
     * \return a float representing the result of the query
     */
    virtual float queryGesture(InputGesture *pIg) = 0;

    /*!
     * \brief Get a formal QString representing the object
     * \return QString representing the object
     */
    virtual QString toString(){return QString();}
};

#endif // GESTUREFEATURE_H
