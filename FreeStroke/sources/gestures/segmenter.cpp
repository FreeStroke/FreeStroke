#include "../../includes/gestures/segmenter.h"
#include "../../includes/common/utils.h"
#include "../../includes/gestures/features/allfeatures.h"

Segmenter::Segmenter()
{
    this->lastGesture = NULL;
    this->minSegmentSize = 20;
    this->noiseTolerance = 2;
    this->numBufferFrames = 2;
    this->mCurrSegmentSize = 0;
    this->mCurrNeutral = 0;
    this->startGesture = false;
    this->mBuffer = new QQueue<RawJointState*>();
    this->mCurrGesture = new QList<RawJointState*>();
    this->role = S_RECOGNIZER;

    if (AllFeatures::loadNeutralFeature() == NULL)
    {
        this->loadFromRessources();
    }


}

void Segmenter::setRole(SegmenterRole pRole)
{
    this->role = pRole;
    this->clear();
}

SegmenterRole Segmenter::getRole()
{
    return this->role;
}

void Segmenter::addToBuffer(RawJointState *pRjs)
{
    this->mBuffer->enqueue(pRjs);
    if (mBuffer->count() > this->numBufferFrames)
    {
        delete this->mBuffer->dequeue();
    }
}

void Segmenter::clear()
{
    if (this->mCurrSegmentSize > 0)
    {
        /*for(int i=0; i < mCurrGesture->count(); i++)
        {
            delete mCurrGesture->at(i);
        }*/
        this->mCurrGesture->clear();
    }
    this->mCurrSegmentSize = 0;
    this->mCurrNeutral = 0;
    this->startGesture = false;
}

bool Segmenter::isNeutralStance(RawJointState *pRjs)
{
    float tolerance = 0.923;
    float damping = this->mCurrSegmentSize / 175.0;
    float final = 0;
    switch(this->role)
    {
    case S_RECOGNIZER:
        final = tolerance;// - damping * damping * damping;
        break;
    case S_RECORDER:
        final = tolerance;
        break;
    }

    float conf = AllFeatures::getNeutralFeature()->queryFrame(pRjs);
    //qDebug()<<conf<<" "<<final;
    return conf > final;
}

bool Segmenter::checkIfSegmented()
{
    bool res=false;
    switch(this->role)
    {
    case S_RECORDER:
        res=(this->mCurrNeutral >= this->noiseTolerance);
        break;
    case S_RECOGNIZER:
        res=(this->mCurrNeutral >= this->noiseTolerance);
        //res=(this->mCurrSegmentSize >= this->minSegmentSize);
        //res=(this->mCurrSegmentSize >= this->minSegmentSize && this->mCurrNeutral >= this->noiseTolerance);
        break;
    default:
        break;
    }

    if (res)
    {
        this->lastGesture = InputGesture::fromJointStates(this->mCurrGesture);
        if(this->lastGesture == NULL || this->lastGesture->states->count() == 0)
        {
            return false;
        }
        return true;
    }
    return false;
}

bool Segmenter::addState(RawJointState *pRjs)
{
    if (this->isNeutralStance(pRjs))
    {
        if(this->checkIfSegmented())
        {
            return true;
        }
        this->addToBuffer(pRjs);
        if (this->mCurrNeutral >= this->noiseTolerance)
        {
            this->mCurrGesture->clear();
            this->mCurrSegmentSize=0;
        }
        if (this->startGesture)
        {
            this->mCurrNeutral++;
        }
    }
    else
    {
        for(int i = 0; i < mBuffer->size(); i++)
        {
            this->mCurrGesture->append(mBuffer->at(i));
        }
        /*for(int i=0; i < mBuffer->count(); i++)
        {
            delete mBuffer->at(i);
        }*/
        this->mBuffer->clear();
        this->mCurrGesture->append(pRjs);
        this->mCurrSegmentSize++;
        if (this->mCurrSegmentSize > this->minSegmentSize)
        {
            this->mCurrNeutral=0;
            this->startGesture=true;
        }
    }
    return false;
}

InputGesture* Segmenter::getLastInputGesture()
{
    return lastGesture;
}

void Segmenter::loadFromRessources()
{
    QList<Gesture*> *neutralGestures = new QList<Gesture*>();
    for(int j = 0; j <= 2; j++)
    {
        QString fname;
        fname.append("ns_0");
        fname.append(QString::number(j));
        fname.append(".log");
        Gesture *gest = Gesture::fromFile(Utils::getResourcesDirectory()+"ns/" + fname);
        if (gest == NULL)
        {
            qDebug()<<"Segmenter::Segmenter() - Gesture NULL";
        }
        neutralGestures->append(gest);
    }

    // Save neutral feature data
    AllFeatures::saveNeutralFeature(neutralGestures);
    if(AllFeatures::loadNeutralFeature() == NULL)
    {
        qDebug()<<"neutrals could not be loaded as resources";
    }
}
