/*!
 * \file rawjointstate.h
 * \brief Represents state of joints in a skeleton
 * \author Camille.D
 * \date 2013-02-12
 */
#ifndef RAWJOINTSTATE_H
#define RAWJOINTSTATE_H

#include "../../common/vector3.h"
#include "../../common/skeletondata.h"

#include <QString>
#include <QHash>
#include <QList>

/*! \class RawJointState
   * \brief Represents state of joints in a skeleton
   * Contains functions to build a skeleton from an input string, compute relative angles and joints
   */
class RawJointState : public QObject
{
    Q_OBJECT
public:
    RawJointState();

    ~RawJointState();

    /*!
     * \enum JointComponent
     * Components of a skeleton joint
     */
    typedef enum _JointComponent_ { PosX = 0, PosY, PosZ, Angle } JointComponent;

    /*!
     * \brief Get a formal QString representing the object
     * \return QString representing the object
     */
    QString toString();

    /*!
     * \brief Computes the position of a joint in the skeleton
     * \param pName name of the joint
     * \return a Vector3 representing the position of the joint
     */
    Vector3 pos(QString pName);

    /*!
     * \brief Computes the angle of a joint in the skeleton
     * \param pName name of the joint
     * \return a float representing the angle of the joint
     */
    float angle(QString pName);

    /*!
     * \brief Get a specified component of a specified joint
     * \param pName name of the joint
     * \param jc enum value of the component
     * \return a float representing the value of the component (Vector3 value or angle)
     */
    float component(QString pName, JointComponent jc);

    /*!
     * \brief Get a static list of joint parents
     * \return the list of joint parents
     */
    static QList<int> jointParents();

    /*!
     * \brief  Get a static map of joints names/values
     * \return the map of joints names/values
     */
    static QHash<QString, int> namesToJoints();

    /*!
     * \brief Build a RawJointState from a string
     * \param pLine the litteral string representing the RawJointState
     * \return the RawJointState build from the QString
     */
    static RawJointState *fromInputLine(QString pLine);

    /*!
     * \brief Build a list of pointer to RawJointStates from a file content
     * \param filename
     * \return the list of pointers
     */
    static QList<RawJointState*> fromFile(QString filename);

    static RawJointState *fromSkeletonData(SkeletonData *pSk);

    static SkeletonData *toSkeletonData(RawJointState *pRjs);

    unsigned long long timestamp; /*!< timestamp of the joints state */
    Vector3 *joints; /*!< array of the joints state */
    int jointsCount; /*!< number of joints */
    int relativeJointsCount; /*!< number of relative joints */
    Vector3 neckPos; /*!< position of the neck */
    Vector3 *relativeJoints; /*!< array of the relative joints */
    float *relativeAngles; /*!< array of the relative angles */
private:
    static void initializeAngles(RawJointState *pRjs, int pAngleCount);
};

#endif // RAWJOINTSTATE_H
