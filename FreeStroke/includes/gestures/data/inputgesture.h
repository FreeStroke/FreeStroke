/*!
 * \file inputgesture.h
 * \brief Represents a gesture used to compute recognition and recording
 * \author Camille.D
 * \date 2013-02-12
 */
#ifndef INPUTGESTURE_H
#define INPUTGESTURE_H

#include "rawjointstate.h"
#include "../../common/gesture.h"

#include <QtCore/QList>

/*! \class InputGesture
   * \brief Represents a gesture used to compute recognition and recording
   * Contains functions to build a gesture and to use it
   */
class InputGesture
{
public:
    /*!
     * \brief Main constructor
     */
    InputGesture();

    /*!
     * \brief Constructs an InputGesture from a list of RawJointStates
     * \param pStates pointer to the list of RawJointState
     */
    InputGesture(QList<RawJointState*> *pStates);

    /*!
     * \brief Get the total time of the gesture
     * \return the total time of the gesture (end-start)
     */
    float totalTime();

    /*!
     * \brief Add a joint state to the gesture
     * \param pState the joint state to add
     */
    void addJointState(RawJointState *pState);

    /*!
     * \brief Build an Gesture from a InputGesture object
     * \return a pointer to the input gesture created
     */
    static Gesture *toGesture(InputGesture *pIg);

    /*!
     * \brief Build an InputGesture from a list of RawJointState
     * \param pStates list of RawJointStates
     * \return a pointer to the input gesture created
     */
    static InputGesture *fromJointStates(QList<RawJointState *> *pStates);

    /*!
     * \brief Build an InputGesture from a Gesture object
     * \param pGesture gesture to compute
     * \return a pointer to the input gesture created
     */
    static InputGesture *fromGesture(Gesture *pGesture);

    float startTime; /*! start timestamp of the gesture */
    QList<RawJointState*> *states;  /*! pointer to the list of states */
};

#endif // INPUTGESTURE_H
