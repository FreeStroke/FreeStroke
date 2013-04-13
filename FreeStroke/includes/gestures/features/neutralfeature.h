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
 * \file neutralfeature.h
 * \brief Defines the neutral stance feature model
 * \author Camille.D
 * \date 2013-02-12
 */
#ifndef NEUTRALFEATURE_H
#define NEUTRALFEATURE_H

#include "../data/rawjointstate.h"

#include "../../common/vector3.h"

#include "feature.h"

/*!
 * \class NeutralFeature
 * \brief Defines the neutral stance feature model
 * Contains functions for querying, saving, loading and training the neutral stance model
 * Neutral stance model is used to detect if a suite of skeletons represents a movement
 */
class NeutralFeature : public Feature
{
public:
    /*!
     * \brief Main constructor of neutral stance feature
     */
    NeutralFeature();

    /*!
     * \brief Determines the position of the parent of a joint
     * \param pRjs the joint state to test
     * \param pI the enum value of the joint
     * \return a Vector3 position of the parent
     */
    Vector3 parent(RawJointState *pRjs, int pI);

    /*!
     * \brief Computes if the joint state is neutral
     * \param pRjs the joint state to test
     * \return a float representing the distance from neutral position
     */
    float queryFrame (RawJointState *pRjs);

    /*!
     * \brief Training function of th e neutral stance model
     * \param pStates joint states representing neutral position
     * \return variances of neutral stance model
     */
    QList<float> *train(QList<RawJointState *> *pStates);

    /*!
     * @brief Save the neutral stance joint states in database
     * @param pFilename
     */
    void saveModel();

    /*!
     * \brief Load the neutral stance joint states from database
     * \param pFlename
     */
    void loadModel();

    QList<float> *variance; /*!< Variances of neutral model */
    QList<Vector3> average; /*!< Average vectors of neutral model */
    float varianceSum; /*!< Sum of variances */
    float weightsSum; /*!< Sum of weights */
    QList<float> *weights;  /*!< Weights of each joint in the model */
};

#endif // NEUTRALFEATURE_H
