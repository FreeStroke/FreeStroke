#include "../../includes/gestures/data/rawjointstate.h"
#include "../../includes/common/skeletondata.h"

#include "../../includes/common/math.h"
#include "../../includes/common/utils.h"

#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QStringList>
#include <QtCore/QFile>

#include <QtCore/QDebug>

RawJointState::RawJointState()
{
    this->timestamp = -1;
    this->joints = NULL;
    this->jointsCount = -1;
    this->relativeJointsCount = -1;
    this->neckPos = Vector3::zero();
    this->relativeJoints = NULL;
    this->relativeAngles = NULL;
}

RawJointState::~RawJointState()
{
    Utils::secureFree(this->joints);
    Utils::secureFree(this->relativeJoints);
    Utils::secureFree(this->relativeAngles);
}

QList<int> RawJointState::jointParents()
{
    static QList<int> l = QList<int>();
    if (l.count() == 0)
    {
        l << -1 << 0 << 0 << 2 << 3 << 4 <<
             0 << 6 << 7 << 8 <<
             18 << 10 << 11 << 12 <<
             19 << 14 << 15 << 16 <<
             0 << 0 ;
    }
    return l;
}

QHash<QString, int> RawJointState::namesToJoints()
{
    static QHash<QString, int> l = QHash<QString, int>();
    if (l.count() == 0)
    {
        l.insert("neck", 0);
        l.insert("head", 1);
        l.insert("right-shoulder", 2);
        l.insert("left-shoulder", 6);
        l.insert("right-elbow", 3);
        l.insert("left-elbow", 7);
        l.insert("right-wrist", 4);
        l.insert("right-pelvis", 18); //Spine
        l.insert("left-pelvis", 19); //HipCenter
        l.insert("left-wrist", 8);
        l.insert("right-palm", 5);
        l.insert("right-hip", 10);
        l.insert("left-hip", 14);
        l.insert("left-palm", 9);
        l.insert("right-knee", 11);
        l.insert("left-knee", 15);
        l.insert("right-ankle", 12);
        l.insert("right-foot", 13);
        l.insert("left-ankle", 16);
        l.insert("left-foot", 17);
    }
    return l;
}

Vector3 RawJointState::pos(QString pName)
{
    return this->relativeJoints[namesToJoints()[pName]];
}

float RawJointState::angle(QString pName)
{
    return this->relativeAngles[namesToJoints()[pName]];
}

QString RawJointState::toString()
{
    QString str;
    str.append(QString::number(this->timestamp));
    for(int i=0; i<jointsCount; i++)
    {
        str.append(" " + QString::number(this->joints[i].x) + " " + QString::number(this->joints[i].y) + " " + QString::number(this->joints[i].z));
    }
    return str;
}

float RawJointState::component(QString pName, JointComponent jc)
{
    if ( jc == Angle)
    {
        return this->angle(pName);
    }
    else
    {
        return this->pos(pName).comp((int)jc);
    }
}

RawJointState* RawJointState::fromInputLine(QString pLine)
{
    QStringList words = pLine.split(" ");

    int num = (words.count()-1) / 3;
    if(num != 20)
    {
        qDebug() << "invalid joints number : " << pLine;
        return NULL;
    }
    RawJointState *rjs = new RawJointState();
    rjs->joints = new Vector3[num];
    rjs->relativeJoints = new Vector3[num];
    rjs->relativeAngles = new float[num];
    rjs->jointsCount = num;
    bool result = true;
    rjs->timestamp = words[0].toLongLong();

    // Initialize joints
    for (int i = 0; i < num; i++)
    {
        int ri = (i*3) + 1;

        rjs->joints[i].x = words[ri].toFloat(&result);
        if (!result)
        {
            delete rjs;
            return NULL;
        }
        rjs->joints[i].y = words[ri+1].toFloat(&result);
        if (!result)
        {
            delete rjs;
            return NULL;
        }
        rjs->joints[i].z = words[ri+2].toFloat(&result);
        if (!result)
        {
            delete rjs;
            return NULL;
        }
    }


    // Initialize neckPos
    rjs->neckPos = rjs->joints[0];

    // Initialize relativeJoints
    for (int i = 0; i < num; i++)
    {
        rjs->relativeJoints[i] = Vector3::substract(rjs->joints[i], rjs->neckPos);
        rjs->relativeJointsCount++;
    }

    initializeAngles(rjs, num);
    return rjs;
}

QList<RawJointState*> RawJointState::fromFile(QString filename)
{
    QFile f(filename);
    if(!f.open(QFile::ReadOnly))
    {
        qDebug()<<"Cannot open file";
        return QList<RawJointState*>();
    }
    QList<RawJointState*> rjsList = QList<RawJointState*>();
    char buffer[1024];
    while(f.readLine(buffer, 1024) > 0)
    {
        rjsList.append(RawJointState::fromInputLine(QString::fromUtf8(buffer)));
    }
    return rjsList;
}

RawJointState *RawJointState::fromSkeletonData(SkeletonData *pData)
{
    RawJointState *rjs = new RawJointState();
    rjs->timestamp = pData->getTimestamp();
    rjs->neckPos = pData->getJointures()->at(0);
    rjs->relativeJoints = new Vector3[pData->getJointures()->count()];
    rjs->relativeJointsCount = pData->getJointures()->count();
    rjs->relativeAngles = new float[pData->getJointures()->count()];

    // Initialize relativeJoints
    for (int i = 0; i < pData->getJointures()->count(); i++)
    {
        rjs->relativeJoints[i] = Vector3::substract(pData->getJointures()->at(i), rjs->neckPos);
    }

    initializeAngles(rjs, pData->getJointures()->count());
    return rjs;
}

SkeletonData *RawJointState::toSkeletonData(RawJointState *pRjs)
{
    QList<Vector3> *jointsList = new QList<Vector3>();
    for (int i = 0; i < pRjs->jointsCount; i++)
    {
        jointsList->append(pRjs->joints[i]);
    }
    return new SkeletonData(jointsList, pRjs->timestamp);
}

void RawJointState::initializeAngles(RawJointState *pRjs, int pAngleCount)
{
    // Initialize relativeAngles
    for (int i = 1; i < pAngleCount; i++)
    {
        Vector3 thisVec = Vector3::substract(pRjs->relativeJoints[i], pRjs->relativeJoints[jointParents().at(i)]);
        Vector3 parentVec;
        if(jointParents()[jointParents()[i]] == -1)
        {
            parentVec = Vector3::unitY();
        }
        else
        {
            parentVec = Vector3::substract(pRjs->relativeJoints[jointParents().at(i)], pRjs->relativeJoints[jointParents()[jointParents().at(i)]]);
        }
        pRjs->relativeAngles[i] = Math::calculateAngle(thisVec, parentVec);
    }
}
