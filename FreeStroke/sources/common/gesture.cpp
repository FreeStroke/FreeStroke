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
#include "../../includes/common/gesture.h"

Gesture::Gesture(QList<SkeletonData*> *pFrames)
{
    this->frames = pFrames;
}

QList<SkeletonData*>* Gesture::getFrames()
{
    return this->frames;
}

Gesture* Gesture::fromFile(QString filename)
{
    QFile f(filename);
    if(!f.open(QFile::ReadOnly))
    {
        qDebug() << "Cannot open file";
        return NULL;
    }

    QList<SkeletonData*> *frames = new QList<SkeletonData*>();
    char buffer[1024];
    int size = -1;
    while((size = f.readLine(buffer, 1024)) > 0)
    {
        frames->append(SkeletonData::fromLine(QString::fromLatin1(buffer, size)));
    }

    Gesture *gesture = new Gesture(frames);
    return gesture;
}

QString Gesture::toString()
{
    QString str;
    for(int i=0; i<this->frames->count(); i++)
    {
        str.append(" " + this->frames->at(i)->toString()+"\n");
    }
    return str;
}
