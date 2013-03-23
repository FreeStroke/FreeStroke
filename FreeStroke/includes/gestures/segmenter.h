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
 * \file segmenter.h
 * \brief Process that builds InputGesture objects computed from NeutralStance model distance
 * \author Camille.D
 * \date 2013-02-12
 */
#ifndef SEGMENTER_H
#define SEGMENTER_H

#include "data/inputgesture.h"
#include "data/rawjointstate.h"

#include <QtCore/QObject>
#include <QtCore/QQueue>
#include <QtCore/QList>

/*!
 * \enum SegmenterRole
 * \brief Defines the process to launch in the ExecutionManager.
 */
enum SegmenterRole {
    S_INACTIVE,
    S_RECOGNIZER,
    S_RECORDER
};

/*! \class Segmenter
   * \brief Process that builds InputGesture objects computed from NeutralStance model distance
   * Contains methods to buffer a flow of RawJointState objects and to build an inputgesture
   * if the sequence of RawJointState is enough distant from neutral postion.
   * It uses the neutral feature from features package to check if the sequence is a non-static gesture
   */
class Segmenter : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Main constructor
     */
    Segmenter();

    /*!
     * \brief setRole change role to RECOGNIZER, INACTIVE or RECORDER
     * \param pRole new role
     */
    void setRole(SegmenterRole pRole);

    /*!
     * \brief get the current role of the recognizer
     * \param pRole new role
     */
    SegmenterRole getRole();

    /*!
     * \brief Clears mCurrGesture buffer and resets mCurrSegmentSize
     */
    void clear();

    /*!
     * \brief Add a raw joint state in the mCurrGesture buffer if the state of the buffered sequence is not neutral and returns false
     * Otherwise, sets the lastGesture InputGesture if a gesture could be segmented, clears the buffer and returns true.
     * \param pRjs the RawJointState to add in the segmenting buffer
     * \return true if a gesture have been segmented, or false if not
     */
    bool addState(RawJointState *pRjs);

    /*!
     * \brief Getter for the last InputGesture segmented
     * \return a pointer on the InputGesture object
     */
    InputGesture* getLastInputGesture();

private:
    int minSegmentSize; /*!< Minimum number of RawJointState to segment the buffer */
    int noiseTolerance; /*!< Number of neutral RawJointStates to consider the end of each gesture */
    int numBufferFrames; /*!< Number of neutral RawJointStates accepted before each gesture */
    int mCurrSegmentSize; /*!< Counter of number of RawJointState in the mCurrGesture buffer */
    int mCurrNeutral; /*!< Counter of number of consecutive neutral */
    bool startGesture; /*!< Define if the gesture has started */
    SegmenterRole role; /*!< Current role of the segmenter */
    QQueue<RawJointState*> *mBuffer; /*!< Global buffer of input RawJointState */
    QList<RawJointState*> *mCurrGesture; /*!< List of RawJointState used to be segmented (not including neutrals)*/
    InputGesture *lastGesture; /*!< Last gesture computed by the segmenter */

    /*!
     * \brief Add a RawJointState in the queue for gesture segmenting
     * \param pRjs the RawJointState to add in the queue
     */
    void addToBuffer(RawJointState *pRjs);

    /*!
     * \brief Checks if the RawJointState is close enough to the neutral position
     * \param pRjs the RawJointState to check
     * \return true if the RawJointState corresponds to a neutral position
     */
    bool isNeutralStance(RawJointState *pRjs);

    /*!
     * \brief Checks if the conditions are required to segment the buffer and sets the lastGesture if possible
     * \return true if the buffer have been successfully segmented
     */
    bool checkIfSegmented();

    /*!
     *  \brief Load neutral stance gestures from internal application Ressources
     *  3 ns files are added to the segmenter to perform segmentation
     */
    void loadFromRessources();

};

#endif // SEGMENTER_H
