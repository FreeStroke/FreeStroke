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
 * \file allfeatures.h
 * \brief Access point to all gesture features and neutral stance feature
 * \author Camille.D
 * \date 2013-02-12
 */
#ifndef ALLFEATURES_H
#define ALLFEATURES_H

#include "../data/inputgesture.h"
#include "gesturefeature.h"
#include "neutralfeature.h"

/*! \class AllFeatures
   * \brief Access point to all gesture features and neutral stance feature
   * Contains functions to access features, load and save neutral stance model and to compute gesture feature results
   */
class AllFeatures
{
public:
    /*!
     * \brief Access all static gesture features
     * \return a pointer to the list of all gesture features used
     */
    static QList<GestureFeature*> allFeatures();


    /*!
     * \brief Computes all gesture feature query results on an input gesture
     * \param pGest inpute gesture to execute queries functions
     * \return  a list containing all the feature results for the gesture
     */
    static QList<float> gestureFeatureResults(InputGesture *pGest);

    /*!
     * \brief Access to the neutral stance feature
     * \return a pointer on the neutral feature
     */
    static NeutralFeature* getNeutralFeature();

    /*!
     * \brief Loads neutral feature from database (Dao)
     * \return the list of weights returned after neutral stance model training
     */
    static QList<float> * loadNeutralFeature();

    /*!
     * \brief Saves neutral stances in database (Dao)
     * \param neutrals neutral stances gestures to save in database
     */
    static void saveNeutralFeature(QList<Gesture *> *neurals);


};


#endif // ALLFEATURES_H
