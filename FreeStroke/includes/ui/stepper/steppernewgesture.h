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
 * \file stepperwengesture.h
 * \brief The Stepper class is a Stepper used for adding a new Gesture.
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef STEPPERNEWGESTURE_H
#define STEPPERNEWGESTURE_H

#include "stepper.h"
#include "../../includes/common/gesture.h"
#include "../../includes/daolayer/record.h"
#include "../../includes/daolayer/command.h"
#include "../../includes/gestures/executionmanager.h"
#include "../../includes/ui/commandchooser/commandchooser.h"

#include <QtCore/QList>
#include <QtCore/QTime>

/*!
 * \brief The Stepper class is a Stepper used for adding a new Gesture.
 */
class StepperNewGesture : public Stepper
{
    Q_OBJECT
public:
    /*!
     * \brief The StepAction enum defines the action to take depending on the current Step
     */
    enum StepAction
    {
        First,
        StartTimer,
        StartRecording,
        VisualizeRecording,
        ConfigureAction,
        SaveRecord,
        Close
    };

    /*!
     * \brief StepperNewGesture default constructor
     * \param pExecutionManager the ExecutionManager which will be used to recognize Gesture
     * \param pCommandChooser the CommandChooser which will be used to choose the Command
     * \param pNumberOfGesture the desired number of Gesture to do to train the model
     * \param parent the QWidget parent
     */
    explicit StepperNewGesture(ExecutionManager* pExecutionManager, CommandChooser* pCommandChooser, int pNumberOfGesture, QWidget *parent = 0);
    /*!
     * \brief addStep add a Step to the stepper
     * \param pTitle the title of the Step
     * \param pNextVisible defines whether or not the next DialogButton is visible for the step
     * \param pPreviousVisible defines whether or not the previous DialogButton is visible for the step
     * \param pCancelVisible defines whether or not the cancel DialogButton is visible for the step
     * \param pAction the action of the Step
     * \param pWidget the QWidget which will be displayed
     */
    void addStep(QString pTitle, bool pNextVisible, bool pPreviousVisible, bool pCancelVisible, StepperNewGesture::StepAction pAction, QWidget* pWidget);

private:
    /*!
     * \brief stepDependantAction choose the action to do depending on the current Step
     * \param offset defines which Step will be used depending on the current Step
     */
    void stepDependantAction(int offset);
    /*!
     * \brief stepActions the QList of StepAction
     */
    QList<StepAction>* stepActions;
    /*!
     * \brief time a QTime used to do singleshot timer
     */
    QTime* time;
    /*!
     * \brief timer a QTimer used to do singleshot timer
     */
    QTimer* timer;
    /*!
     * \brief executionManager the ExecutionManager which will be used to recognize Gesture
     */
    ExecutionManager* executionManager;
    /*!
     * \brief numberOfGesture the desired number of Gesture to do to train the model
     */
    int numberOfGesture;
    /*!
     * \brief record the Record to save in the DAOLayer once the Gesture is added
     */
    Record* record;
    /*!
     * \brief gestures the QList of Gesture recorded used to train the model
     */
    QList<Gesture*>* gestures;
    /*!
     * \brief stepLoop determine if it is necessary to loop for adding a new Gesture (depending on the current number of
     * Gesture in gestures and numberOfGesture)
     * \return
     */
    bool stepLoop();
    /*!
     * \brief recordName the name of the Record
     */
    QString recordName;
    /*!
     * \brief command the Command of the Gesture
     */
    Command* command;
    /*!
     * \brief commandChooser the CommandChooser used to choose the Command of the Gesture
     */
    CommandChooser* commandChooser;
    /*!
     * \brief recordSaved defines if the Record have been saved in the DAOLayer or not
     */
    bool recordSaved;


public slots:
    /*!
     * \brief nextStep slot is called to go to the next Step.
     */
    void nextStep();
    /*!
     * \brief previousStep slot is called to go to the previous Step.
     */
    void previousStep();

private slots:
    /*!
     * \brief trainingEnded slot is called when the ExecutionManager has finished training the model. It go to the
     * next Step.
     */
    void trainingEnded();
    /*!
     * \brief startTimer slot is called before recording a Gesture. It allow the user to place himself in front of the
     * Controller.
     */
    void startTimer();
    /*!
     * \brief endOfRecord slot is called when the Controller has finished recording a Gesture. It go to the nect step.
     */
    void endOfRecord(Gesture*);
    /*!
     * \brief conflictWhileRecording slot is called if the ExecutionManager detect a conflict while recording a new
     * Gesture. It restarts the recording
     */
    void conflictWhileRecording(Gesture*);
};

#endif // STEPPERNEWGESTURE_H
