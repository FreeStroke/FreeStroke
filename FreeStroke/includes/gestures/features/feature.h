#ifndef FEATURE_H
#define FEATURE_H

#include "../data/inputgesture.h"

#include <QtCore/QList>
#include <QtCore/QString>

class Feature
{
public:
    virtual void train(QList<InputGesture> pStates){Q_UNUSED(pStates);}
    virtual void saveModel(QString pFilename){Q_UNUSED(pFilename);}
    virtual void loadModel(QString pFilename){Q_UNUSED(pFilename);}
};

#endif // FEATURE_H
