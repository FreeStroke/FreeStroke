#ifndef EXECUTIONMGRTEST_H
#define EXECUTIONMGRTEST_H

#include "../../includes/common/gesture.h"
#include "../../includes/gestures/executionmanager.h"

#include <cppunit/extensions/HelperMacros.h>
#include <QtCore/QObject>

class ExecutionMgrTest : public QObject, public CppUnit::TestCase
{
    Q_OBJECT
public:
    ExecutionMgrTest(std::string name);
    void runTest();

public slots:
    void gestureConflict(Gesture* pGesture);
    void gestureRecognized(Gesture* pGesture);
    void gestureRecorded(Gesture* pGesture);
    void skeletonDataReceived(SkeletonData* pData);
    void trainingEnded();

private:
    bool gestureRecon, gestureConf, gestureRecord, trainingDone, dataReceived;
    /* Here it is assumed that the segmenter and the lra work as expected */
    void testNewDataSkeletonData(Role pRole);
    void testRecognizer();
    void testStartRecorder();
    void testStartTraining();
    void testRecordGesture();
    void testRecognizeGesture();
};

#endif // EXECUTIONMGRTEST_H
