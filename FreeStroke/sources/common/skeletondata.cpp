#include "../../includes/common/skeletondata.h"

#include <QtCore/QStringList>

#include <QtCore/QDebug>

SkeletonData::SkeletonData(QList<Vector3> *pJointures, unsigned long long pTimestamp)
{
    this->timestamp = pTimestamp;
    this->jointures = pJointures;
}

SkeletonData::~SkeletonData()
{
    if (this->jointures != NULL)
    {
        this->jointures->clear();
        delete this->jointures;
    }
}

QList<Vector3>* SkeletonData::getJointures()
{
    return this->jointures;
}

unsigned long long SkeletonData::getTimestamp()
{
    return this->timestamp;
}

SkeletonData* SkeletonData::fromLine(QString line)
{
    QStringList l = line.split(" ", QString::SkipEmptyParts);
    QList<Vector3> *jointures = new QList<Vector3>();
    for(int i=1; i+3<=l.count(); i+=3)
    {
        Vector3 v;
        v.x = l.at(i).toFloat();
        v.y = l.at(i+1).toFloat();
        v.z = l.at(i+2).toFloat();
        jointures->append(v);
    }
    return new SkeletonData(jointures, l.at(0).toLongLong());
}

QString SkeletonData::toString()
{
    QString str;
    //qDebug() << this->timestamp ;
    str.append(QString::number(this->timestamp));
    for(int i=0; i<this->jointures->count(); i++)
    {
        str.append(" " + QString::number(this->jointures->at(i).x) + " " + QString::number(this->jointures->at(i).y) + " " + QString::number(this->jointures->at(i).z));
    }
    return str;
}
