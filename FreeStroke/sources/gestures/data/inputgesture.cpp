#include "../../includes/gestures/data/inputgesture.h"

#include "../../includes/gestures/data/rawjointstate.h"

#include "QtCore/QDebug"

InputGesture::InputGesture()
{
    this->startTime = 0;
    this->states = new QList<RawJointState*>();
}

InputGesture::InputGesture(QList<RawJointState*> *pStates)
{
    this->startTime = pStates->first()->timestamp;
    this->states = new QList<RawJointState*>(*pStates);
}

float InputGesture::totalTime()
{
    return this->states->at(this->states->count() - 1)->timestamp - startTime;
}

void InputGesture::addJointState(RawJointState *pState)
{
    this->states->append(pState);
    if (this->states->count() == 1)
    {
        this->startTime = this->states->at(0)->timestamp;
    }
}

Gesture *InputGesture::toGesture(InputGesture *pIg)
{
    QList<SkeletonData*> *skeletons = new QList<SkeletonData*>();

    for (int i = 0; i < pIg->states->count(); i++)
    {
        skeletons->append(RawJointState::toSkeletonData(pIg->states->at(i)));
    }

    return new Gesture(skeletons);
}

InputGesture *InputGesture::fromJointStates(QList<RawJointState*> *pStates)
{
    InputGesture *ig = new InputGesture();
    ig->states = pStates;
    if ( ig->states->count() > 0 )
    {
        ig->startTime = ig->states->at(0)->timestamp;
    }
    return ig;
}

InputGesture *InputGesture::fromGesture(Gesture *pGesture)
{
    InputGesture *ig = new InputGesture();
    ig->states = new QList<RawJointState*>();
    for (int i = 0; i < pGesture->getFrames()->count(); i++)
    {
        ig->states->append(RawJointState::fromSkeletonData(pGesture->getFrames()->at(i)));
    }
    if ( ig->states->count() > 0 )
    {
        ig->startTime = ig->states->at(0)->timestamp;
    }

    return ig;
}
