/*!
 * \file skeletondata.h
 * \author Guillaume Demurger
 * \brief Represents a basic skeleton object of the users body at a precise instant
 * \date 2013-02-14
 */
#ifndef SKELETONDATA_H
#define SKELETONDATA_H

#include <QtCore/QList>

#include "vector3.h"

/*!
 * \brief Represents a basic skeleton object of the users body
 * Composed by a list of joints (Vectors) of the body and a timestamp
 */
class SkeletonData
{
public:
    /*!
     * \brief Main constructor
     * \param pJointures joints representing the skeleton
     * \param pTimestamp timestamps in milliseconds when the skeleton is captured by the sensor
     */
    SkeletonData(QList<Vector3> *pJointures, unsigned long long pTimestamp);

    /*!
     * \brief Main destructor
     */
    ~SkeletonData();

    /*!
     * \brief Getter for the list of joints representing the skeleton
     * \return a list of Vector3 objects (joints)
     */
    QList<Vector3>* getJointures();

    /*!
     * \brief Getter for the timestamp of the skeleton
     * \return a timestamp in milliseconds
     */
    unsigned long long getTimestamp();

    /*!
     * \brief Enum of the joints position sent by the Kinect sensor
     */
    enum JointPosition {
        neck = 0,
        head,
        rightShoulder,
        rightElbow,
        rightWrist,
        rightPalm,
        leftShoulder,
        leftElbow,
        leftWrist,
        leftPalm,
        rightHip,
        rightKnee,
        rightAnkle,
        rightFoot,
        leftHip,
        leftKnee,
        leftAnkle,
        leftFoot,
        rightPelvis,
        leftPelvis
    };

    /*!
     * \brief Get a formal QString representing the object
     * \return QString representing the object
     */
    QString toString();

    /*!
     * \brief Parses a string line to build a skeleton data objecyt
     * \param line the line to get the skeleton from
     * \return a pointer on the skeleton data object
     */
    static SkeletonData *fromLine(QString line);

private:
    QList<Vector3> *jointures; /*!< List of joints representing the skeleton */
    unsigned long long timestamp; /*!< Timestamp of the skeleton capture in milliseconds */
};

#endif // SKELETONDATA_H
