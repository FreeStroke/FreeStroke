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
 * \file stepsnewgesture.h
 * \brief The StepsNewGesture class contains all the Step to add a new Gesture with the StepperNewGesture
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef STEPSNEWGESTURE_H
#define STEPSNEWGESTURE_H

#include "stepper.h"
#include "steppernewgesture.h"

#include "../../includes/daolayer/record.h"
#include "../../includes/common/gesture.h"
#include "../../includes/gestures/executionmanager.h"
#include "../../includes/ui/glview/glview.h"
#include "../../includes/ui/commandchooser/commandchooser.h"

/*!
 * \brief The StepsNewGesture class contains all the Step to add a new Gesture with the StepperNewGesture
 */
class StepsNewGesture : QObject
{
    Q_OBJECT
public:
    /*!
     * \brief StepsNewGesture default constructor
     * \param pExecutionManager the ExecutionManager which will be used to recognize Gesture
     * \param pNumberOfGesture the desired number of Gesture to do to train the model
     * \param parent the QWidget parent
     */
    explicit StepsNewGesture(ExecutionManager *pExecutionManager, int pNumberOfGesture, QWidget *parent = 0);
    /*!
     * \brief show display the StepperNewGesture
     * \return a QDialogCode result
     */
    int show();

private:
    /*!
     * \brief stepper the StepperNewGesture which will be displayed
     */
    StepperNewGesture* stepper;
    /*!
     * \brief executionManager the ExecutionManager which will be used to recognize Gesture
     */
    ExecutionManager* executionManager;
    /*!
     * \brief glViewStep4 the GLView of the forth Step
     */
    GlView* glViewStep4;
    /*!
     * \brief commandChooser the CommandChooser which will be used to choose the Command
     */
    CommandChooser* commandChooser;

private slots:
    /*!
     * \brief gestureReceived slot called when a Gesture is received by the ExecutionManager. It set the Gesture to the
     * GLView of the forth Step to display it.
     * \param pGesture the Gesture received.
     */
    void gestureReceived(Gesture *pGesture);

};

#endif // STEPSNEWGESTURE_H
