/*!
 * \file framefeatures.h
 * \brief Internal classes querying gesture features
 * \author Camille.D
 * \date 2013-02-12
 */
#ifndef GESTUREFEATURES_H
#define GESTUREFEATURES_H

#include "gesturefeature.h"
#include "../data/rawjointstate.h"

/*!
 * \class JointAmplitude
 * \brief Calculation of joint amplitude on a entire input gesture
 */
class JointAmplitude : public GestureFeature
{
public:
    JointAmplitude(QString jn, RawJointState::JointComponent jc, bool d);
    float queryGesture(InputGesture *pIg);
private:
    QString jointName;
    RawJointState::JointComponent jointComponent;
    bool directional;
};

/*!
 * \class NeutralDeviation
 * \brief Calculation of deviation of the gesture from the neutral stance
 */
class NeutralDeviation : public GestureFeature
{
public:
    NeutralDeviation(QString jn, RawJointState::JointComponent jc);
    float queryGesture(InputGesture *pIg);
private:
    QString jointName;
    RawJointState::JointComponent jointComponent;
};

/*!
 * \class NeckAmplitude
 * \brief Calculation of the neck amplitude from head
 */
class NeckAmplitude : public GestureFeature
{
public:
    float queryGesture(InputGesture *pIg);
};

/*!
 * \class ProportionChange
 * \brief Calculation of the gesture to normalize space between joints
 */
class ProportionChange : public GestureFeature
{
public:
    ProportionChange(QString jn, RawJointState::JointComponent jc);
    float queryGesture(InputGesture *pIg);
private:
    QString jointName;
    RawJointState::JointComponent jointComponent;
};


/*!
 * \class NumberCriticalPoints
 * \brief Calculation of critical points of a joint component in a gesture
 */
class NumberCriticalPoints : public GestureFeature
{
public:
    NumberCriticalPoints(QString jn, RawJointState::JointComponent jc);
    float queryGesture(InputGesture *pIg);
private:
    QString jointName;
    RawJointState::JointComponent jointComponent;
};

/*!
 * \class DerivativeSum
 * \brief Calculation of derivative sum
 */
class DerivativeSum : public GestureFeature
{
public:
    DerivativeSum(QString jn, RawJointState::JointComponent jc);
    float queryGesture(InputGesture *pIg);
private:
    QString jointName;
    RawJointState::JointComponent jointComponent;
};

/*!
 * \class DerivativeSum
 * \brief Calculation of axis coincidence between two joint components in a gesture
 */
class AxisCoincidence : public GestureFeature
{
public:
    AxisCoincidence(QString jn, RawJointState::JointComponent ja, RawJointState::JointComponent jb);
    float queryGesture(InputGesture *pIg);
private:
    QString jointName;
    RawJointState::JointComponent jointComponentA;
    RawJointState::JointComponent jointComponentB;
};

/*!
 * \class MinDistance
 * \brief Calculation of the minimal distance between two joints in a gesture
 */
class MinDistance : public GestureFeature
{
public:
    MinDistance(QString jnA, QString jnB);
    float queryGesture(InputGesture *pIg);
private:
    QString jointNameA;
    QString jointNameB;
};

/*!
 * \class MaxDistance
 * \brief Calculation of the maximal distance between two joints in a gesture
 */
class MaxDistance : public GestureFeature
{
public:
    MaxDistance(QString jnA, QString jnB);
    float queryGesture(InputGesture *pIg);
private:
    QString jointNameA;
    QString jointNameB;
};

#endif // GESTUREFEATURES_H
