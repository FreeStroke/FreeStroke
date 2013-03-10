#include "../includes/executionmgrtest.h"
#include "../../includes/daolayer/daolayer.h"
#include "../../includes/gestures/features/allfeatures.h"

#include <QtCore/QDebug>

ExecutionMgrTest::ExecutionMgrTest(std::string name) : QObject(), CppUnit::TestCase(name)
{
}

void ExecutionMgrTest::runTest()
{
    //this->testNewDataSkeletonData(RECOGNIZER);
    //this->testNewDataSkeletonData(RECORDER);
   // this->testStartRecorder();
   // this->testStartTraining();
   // this->testRecordGesture();
   // this->testRecognizer();*/
}

void ExecutionMgrTest::gestureConflict(Gesture* pGesture)
{
    gestureConf = true;
}

void ExecutionMgrTest::gestureRecognized(Gesture* pGesture)
{
    gestureRecon = true;
}

void ExecutionMgrTest::gestureRecorded(Gesture* pGesture)
{
    gestureRecord = true;
}

void ExecutionMgrTest::trainingEnded()
{
    trainingDone = true;
}

void ExecutionMgrTest::skeletonDataReceived(SkeletonData *pData) {
    CPPUNIT_ASSERT(pData->getJointures()->count() == 0);
    CPPUNIT_ASSERT(pData->getTimestamp() == 0);
    dataReceived = true;
}

void ExecutionMgrTest::testNewDataSkeletonData(Role pRole)
{
    ExecutionManager *execMgr = new ExecutionManager();

    QObject::connect(execMgr, SIGNAL(gestureConflict(Gesture*)), this, SLOT(gestureConflict(Gesture*)));
    QObject::connect(execMgr, SIGNAL(gestureRecorded(Gesture*)), this, SLOT(gestureRecorded(Gesture*)));
    QObject::connect(execMgr, SIGNAL(gestureRecognized(Gesture*)), this, SLOT(gestureRecognized(Gesture*)));
    QObject::connect(execMgr, SIGNAL(trainingEnded()), this, SLOT(trainingEnded()));

    QList<QString> gestureNames = QList<QString>();
#warning Must change test files to final generated files
    gestureNames.append("track_flick_left");
    gestureNames.append("track_flick_right");
    gestureNames.append("track_jump");
    gestureNames.append("track_hello");
    gestureNames.append("track_kick_left");
    gestureNames.append("track_kick_right");
    gestureNames.append("track_low_kick_right");
    gestureNames.append("track_punch_left");
    gestureNames.append("track_punch_right");

    QList<Gesture*> *neutralGestures = new QList<Gesture*>();
    // For testing : Save ns sample files (ns_00.log to ns_02.log)
    int count = 0;
    for(int j = 0; j < 3; j++)
    {
        QString fname;
        fname.append("ns_0");
        fname.append(QString::number(j));
        fname.append(".log");
        Gesture *gest = Gesture::fromFile("others/" + fname);
        neutralGestures->append(gest);
        count += gest->getFrames()->count();
    }

    // Save neutral feature data
    AllFeatures::saveNeutralFeature(neutralGestures);

    switch(pRole)
    {
    case RECORDER: execMgr->startRecorder();
    case RECOGNIZER: execMgr->startRecognizer();
    }

    Gesture *gesture = Gesture::fromFile("others/track_punch_right_00.log");

   /* for(int j = 0; j < gestureNames.count(); j++)
    {
        QString testing = gestureNames.at(j);
        Gesture *gesture = Gesture::fromFile("others/"+testing+"_00.log");
*/
        for(int i = 0; i < gesture->getFrames()->count(); i++)
        {
            qDebug() << "i "<<i;
            execMgr->newSkeletonData(gesture->getFrames()->at(i)->toString());
        }
        gestureRecon = false;
    //}
}

void ExecutionMgrTest::testRecognizer()
{
    DAOLayer *daoLayer = DAOLayer::getInstance();
    if(daoLayer == NULL)
    {
        return;
    }
    ExecutionManager * execMgr = new ExecutionManager();
    QObject::connect(daoLayer, SIGNAL(skeletonDataReceived(SkeletonData*)), this, SLOT(skeletonDataReceived(SkeletonData*)));
    execMgr->startRecognizer();
    CPPUNIT_ASSERT(execMgr->getRole()==RECOGNIZER);
    SkeletonData *skeleton = new SkeletonData(new QList<Vector3>, 0);
    daoLayer->dataFromCommunication(skeleton->toString());
    CPPUNIT_ASSERT(dataReceived == true);
    dataReceived = false;
}

void ExecutionMgrTest::testStartRecorder()
{
    DAOLayer *daoLayer = DAOLayer::getInstance();
    if(daoLayer == NULL)
    {
        return;
    }
    ExecutionManager * execMgr = new ExecutionManager();
    execMgr->startRecognizer();
    execMgr->startRecorder();
    Gesture *gesture = Gesture::fromFile("others/track_flick_right_00.log");
    QList<SkeletonData*> *frames = gesture->getFrames();
    for(int i=0; i < frames->count(); i++)
    {
        daoLayer->dataFromCommunication(frames->at(i)->toString());
    }
    CPPUNIT_ASSERT(gestureRecord == false);
}

void ExecutionMgrTest::testStartTraining()
{
    ExecutionManager * execMgr = new ExecutionManager();
    execMgr->startTraining();
    CPPUNIT_ASSERT(trainingDone==true);
}

void ExecutionMgrTest::testRecordGesture()
{

    ExecutionManager * execMgr = new ExecutionManager();
    execMgr->startRecognizer();
    execMgr->startRecorder();
    Gesture *gesture = Gesture::fromFile("others/track_flick_right_00.log");
    QList<SkeletonData*> *frames = gesture->getFrames();
    for(int i=0; i < frames->count(); i++)
    {
      //  execMgr->getDao()->dataFromCommunication(frames->at(i)->toString());
    }
    qDebug() << "plop";
    //CPPUNIT_ASSERT(gestureRecon == true);
    //gestureRecon = true;
    QList<Gesture*> *gestures = new QList<Gesture*>();
    gestures->append(gesture);
    //execMgr->getDao()->addRecord(new Record("Test", gestures, new Command("Ctrt+v", KEYSTROKE)));
    execMgr->startTraining();

    CPPUNIT_ASSERT(trainingDone == true);
    trainingDone = false;

    execMgr->startRecorder();
    for(int i=0; i < frames->count(); i++)
    {
     //   execMgr->getDao()->dataFromCommunication(frames->at(i)->toString());
    }
    CPPUNIT_ASSERT(gestureRecon == true);
}
