#include "../../includes/gestures/features/allfeatures.h"
#include "../../includes/gestures/features/gesturefeatures.h"
#include "../../includes/gestures/data/rawjointstate.h"
#include "../../includes/daolayer/daolayer.h"

static NeutralFeature* neutralFeature = NULL;

QList<GestureFeature*> AllFeatures::allFeatures()
{
    static QList<GestureFeature*> gestureFeatures = QList<GestureFeature*>();

    if (gestureFeatures.count() > 0)
    {
        return gestureFeatures;
    }
    gestureFeatures.append(new JointAmplitude("right-wrist", RawJointState::PosX, false));
    gestureFeatures.append(new JointAmplitude("right-wrist", RawJointState::PosY, false));
    gestureFeatures.append(new JointAmplitude("right-wrist", RawJointState::PosZ, false));

    //
    gestureFeatures.append(new JointAmplitude("left-wrist", RawJointState::PosX, false));
    gestureFeatures.append(new JointAmplitude("left-wrist", RawJointState::PosY, false));
    gestureFeatures.append(new JointAmplitude("left-wrist", RawJointState::PosZ, false));

    gestureFeatures.append(new JointAmplitude("right-elbow", RawJointState::PosX, false));
    gestureFeatures.append(new JointAmplitude("right-elbow", RawJointState::PosY, false));
    gestureFeatures.append(new JointAmplitude("right-elbow", RawJointState::PosZ, false));

    gestureFeatures.append(new JointAmplitude("left-elbow", RawJointState::PosX, false));
    gestureFeatures.append(new JointAmplitude("left-elbow", RawJointState::PosY, false));
    gestureFeatures.append(new JointAmplitude("left-elbow", RawJointState::PosZ, false));

    gestureFeatures.append(new JointAmplitude("right-knee", RawJointState::PosX, false));
    gestureFeatures.append(new JointAmplitude("right-knee", RawJointState::PosY, false));
    gestureFeatures.append(new JointAmplitude("right-knee", RawJointState::PosZ, false));

    gestureFeatures.append(new JointAmplitude("left-knee", RawJointState::PosX, false));
    gestureFeatures.append(new JointAmplitude("left-knee", RawJointState::PosY, false));
    gestureFeatures.append(new JointAmplitude("left-knee", RawJointState::PosZ, false));

    gestureFeatures.append(new JointAmplitude("right-foot", RawJointState::PosX, false));
    gestureFeatures.append(new JointAmplitude("right-foot", RawJointState::PosY, false));
    gestureFeatures.append(new JointAmplitude("right-foot", RawJointState::PosZ, false));

    gestureFeatures.append(new JointAmplitude("left-foot", RawJointState::PosX, false));
    gestureFeatures.append(new JointAmplitude("left-foot", RawJointState::PosY, false));
    gestureFeatures.append(new JointAmplitude("left-foot", RawJointState::PosZ, false));

    gestureFeatures.append(new ProportionChange("right-wrist", RawJointState::Angle));
    gestureFeatures.append(new ProportionChange("left-wrist", RawJointState::Angle));

    gestureFeatures.append(new ProportionChange("right-foot", RawJointState::Angle));
    gestureFeatures.append(new ProportionChange("left-foot", RawJointState::Angle));

    gestureFeatures.append(new NeckAmplitude());
    gestureFeatures.append(new MinDistance("left-wrist", "right-wrist"));
    gestureFeatures.append(new MaxDistance("left-wrist", "right-wrist"));

    /*gestureFeatures.append(new NumberCriticalPoints("left-palm", RawJointState::PosX));
    gestureFeatures.append(new NumberCriticalPoints("left-palm", RawJointState::PosY));
    gestureFeatures.append(new NumberCriticalPoints("left-palm", RawJointState::PosZ));

    gestureFeatures.append(new NumberCriticalPoints("right-palm", RawJointState::PosX));
    gestureFeatures.append(new NumberCriticalPoints("right-palm", RawJointState::PosY));
    gestureFeatures.append(new NumberCriticalPoints("right-palm", RawJointState::PosZ));*/
    //

    /*gestureFeatures.append(new JointAmplitude("left-palm", RawJointState::PosX, false));
    gestureFeatures.append(new ProportionChange("right-palm", RawJointState::PosX));

    gestureFeatures.append(new JointAmplitude("right-wrist", RawJointState::Angle, false));
    gestureFeatures.append(new ProportionChange("right-wrist", RawJointState::Angle));
    gestureFeatures.append(new ProportionChange("left-wrist", RawJointState::Angle));

    gestureFeatures.append(new JointAmplitude("right-foot", RawJointState::PosY, false));
    gestureFeatures.append(new ProportionChange("right-foot", RawJointState::Angle));

    gestureFeatures.append(new MinDistance("left-palm", "right-palm"));
    gestureFeatures.append(new MaxDistance("left-palm", "right-palm"));

    gestureFeatures.append(new NeckAmplitude());
    gestureFeatures.append(new ProportionFrames(new RHighFoot()));
    gestureFeatures.append(new ProportionFrames(new RHPastNeck()));
    gestureFeatures.append(new ProportionFrames(new RHandForward()));
    gestureFeatures.append(new NeutralDeviation("right-wrist", RawJointState::PosX));
    gestureFeatures.append(new NeutralDeviation("left-wrist", RawJointState::PosX));
    gestureFeatures.append(new NumberCriticalPoints("right-palm", RawJointState::PosX));
    gestureFeatures.append(new DerivativeSum("right-palm", RawJointState::PosX));
    gestureFeatures.append(new AxisCoincidence("right-palm", RawJointState::PosX, RawJointState::PosZ));*/



    //append
    /*gestureFeatures.append(new JointAmplitude("left-palm", RawJointState::PosY, false));
    gestureFeatures.append(new JointAmplitude("left-palm", RawJointState::PosZ, false));
    gestureFeatures.append(new JointAmplitude("left-wrist", RawJointState::Angle, false));
    gestureFeatures.append(new NeutralDeviation("left-palm", RawJointState::PosX));
    gestureFeatures.append(new NumberCriticalPoints("left-palm", RawJointState::PosX));
    gestureFeatures.append(new DerivativeSum("left-palm", RawJointState::PosX));
    gestureFeatures.append(new AxisCoincidence("left-palm", RawJointState::PosX, RawJointState::PosZ));
    gestureFeatures.append(new JointAmplitude("left-foot", RawJointState::PosY, false));
    gestureFeatures.append(new ProportionChange("left-foot", RawJointState::Angle));*/

    return gestureFeatures;
}

QList<float> AllFeatures::gestureFeatureResults(InputGesture *pGest)
{
    QList<float> fList = QList<float>();
    QList<GestureFeature*> features = AllFeatures::allFeatures();
    for(int i = 0; i < features.count(); i++)
    {
        fList.append(((GestureFeature*)features.at(i))->queryGesture(pGest));
    }
    return fList;
}

NeutralFeature* AllFeatures::getNeutralFeature()
{
    if (neutralFeature == NULL)
    {
        neutralFeature = new NeutralFeature();
    }
    return neutralFeature;
}

void AllFeatures::saveNeutralFeature(QList<Gesture*> *neurals)
{
    // For testing : SAVE ns sample files (ns_00.log to ns_02.log)
    DAOLayer *dao = DAOLayer::getInstance();
    if(dao == NULL)
    {
        qDebug()<<"saveNeutralFeature error";
        return;
    }
    dao->removeNeutralGesture();
    for(int i = 0; i < neurals->count(); i++)
    {
        if(dao->addNeutralGesture(neurals->at(i)) != 0)
        {
            qDebug()<< "error adding neutral";
        }
    }
}



QList<float> * AllFeatures::loadNeutralFeature()
{
    QList<RawJointState*> *nsList = new QList<RawJointState*>();
    DAOLayer *dao = DAOLayer::getInstance();
    if(dao == NULL)
    {
        qDebug()<<"loadNeutralFeature error";
        return NULL;
    }

    QList<Gesture*> *list =  dao->getNeutralGestures();
    if(list == NULL)
    {
        return NULL;
    }
    for(int i = 0; i < list->count(); i++)
    {
        for(int j = 0; j < list->at(i)->getFrames()->count(); j++)
        {
            nsList->append(RawJointState::fromSkeletonData(list->at(i)->getFrames()->at(j)));
        }
    }

    if(nsList->count() > 0)
    {
        return AllFeatures::getNeutralFeature()->train(nsList);
    }
    return NULL;
}

