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
 * \file gesture.h
 * \author Guillaume Demurger
 * \brief Represents a basic gesture object
 * \date 2013-02-14
 */
#ifndef GESTURE_H
#define GESTURE_H

#include "skeletondata.h"

/*!
 * \brief Represents a basic gesture object
 * A gesture is composed by some skeleton frames and can be built from a file or a list of frames
 * It is basically a sequence of skeleton states / frames
 */
class Gesture
{
public:
    /*!
     * \brief Main constructor
     * \param pFrames frames representing the gesture
     */
    Gesture(QList<SkeletonData*> *pFrames);

    /*!
     * \brief getter for frames of the gesture
     * \return the frames composing the gesture
     */
    QList<SkeletonData*>* getFrames();

    /*!
     * \brief String representation of the gesture
     */
    QString toString();

    /*!
     * \brief Used to build a gesture from a file content
     * \param filename name of the file containing the sequence of frames
     * \return a pointer on the created gesture object
     */
    static Gesture* fromFile(QString filename);

private:
    QList<SkeletonData*> *frames; /*!< List of frames representing the gesture */
};

#endif // GESTURE_H
