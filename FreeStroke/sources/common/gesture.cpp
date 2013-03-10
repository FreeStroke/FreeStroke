#include "../../includes/common/gesture.h"

#include <QtCore/QFile>

#include <QtCore/QDebug>

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
        frames->append(SkeletonData::fromLine(QString::fromAscii(buffer, size)));
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
