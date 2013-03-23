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
