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
 * \file executionmanager.h
 * \brief Execution thread managing switching between recording and recognizing mode of freestroke
 * \author Guillaume Demurger
 * \date 2013-02-12
 */
#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

#include "algorithm/logisticregressionalgorithm.h"
#include "segmenter.h"

/*!
 * \enum Role
 * \brief Defines the process to launch in the ExecutionManager.
 */
enum Role {
    INACTIVE,
    RECOGNIZER,
    RECORDER
};

/*!
 * \class ExecutionManager
 * \brief Launch processes required by the application. It is connected to the model to
 * receive new data from the sensor and proposes signal to announce events relatives
 * to the gesture recording and recognition.
 */
class ExecutionManager : public QThread
{
    Q_OBJECT
public:
    ExecutionManager();

    /*!
     * \brief return the running process.
     * \return Role the last running process.
     */
    Role getRole();

public slots:
    /*!
     * \brief Launch the recognition in background. It starts the process of listening new data announced by the model.
     * Don't call this method is a process is already running. Call standby() before.
     */
    void startRecognizer();

    /*!
     * \brief Launch the listening of the data for recording a new gesture.
     * Don't call this method is a process is already running. Call standby() before.
     */
    void startRecorder();

    /*!
     * \brief Stop the current process. It stops the listening of data from the model.
     */
    void standby();

    /*!
     * \brief Start the training of the LRA. This method must be called each time the model
     * changes to have the LRA take account of this change.
     * Make sure you have stop the current process by calling standby() before call this method.
     */
    void startTraining();

    /*!
     * \brief Add the SkeletonData to the segmenter and process the recognition or the recording
     * according to which process is currently running.
     * \param SkeletonData *pData the new skeleton data announced by the model.
     */
    void newSkeletonData(QString pData);

    /*!
     * \brief Emit the trainingEnded
     */
    void endTraining();

signals:
    /*!
     * \brief Notify the startTraining() method ended and the LRA is ready for recognition.
     */
    void trainingEnded();

    /*!
     * \brief Notify that the LRA detected the gesture pGesture to record
     * conflicts with another in the model.
     * \param the gesture trying to be recorded.
     */
    void gestureConflict(Gesture* pGesture);

    /*!
     * \brief Notify that the gesture pGesture recording ended.
     * \param the gesture trying to be recording.
     */
    void gestureRecorded(Gesture *pGesture);

    /*!
     * \brief Notify the model that a gesture pGesture has been recognized
     * by the LRA.
     * \param the gesture trying to be recording.
     */
    void gestureRecognized(Gesture *pGesture);

    /*!
     * \brief Notify the model that a gesture recorded is not compatible with a
     * previous try.
     * \param the gesture trying to be recorded.
     */
    #warning Problem: cannot preserve a list of gestures of the previous tries during a recording to make sure they are compatible.
    //void gestureNotCompatible(Gesture *pGesture);


private:

    /*!
     * \brief The instance of the LRA.
     *
     * It makes the recognition process, according recognize
     * gestures from a stream of skeletons (SkeletonData). It allows to detect conflict
     * in gesture recording if the new gesture is too near from an existing one.
     *
     * Furthermore if multiple tries of a gesture recording process diverge so far they
     * can't be recognized between them, LRA allows us to cancel the process.
     */
    LogisticRegressionAlgorithm *lra;

    /*!
     * \brief The instance of segmenter that stripes the stream of skeletons to get gestures.
     *
     */
    Segmenter *segmenter;

    /*!
     * \brief Defines the last running process.
     */
    Role role;
protected:
    /*!
     * \brief Start the process parsed in pRole. It connects the associated signals.
     * \param Role pRole
     */
    void startWithRole(Role pRole);

    /*!
     * \brief Execution method of the execution managers thread
     */
    void run();
};

#endif // EXECUTIONMANAGER_H
