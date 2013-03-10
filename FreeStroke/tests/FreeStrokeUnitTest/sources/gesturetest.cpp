#include "../includes/gesturetest.h"

#include "../../includes/gestures/data/rawjointstate.h"
#include "../../includes/common/gesture.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

GestureTest::GestureTest(std::string name) : CppUnit::TestCase(name) {}

void GestureTest::runTest()
{
    QList<RawJointState*> list = RawJointState::fromFile("others/clap.log");
    QList<RawJointState*> rjsList;
    for(int i = 0; i < list.count(); i++)
    {
        rjsList.append(list.at(i));
    }

    Gesture *gesture = Gesture::fromFile("others/clap.log");
    QList<SkeletonData*> *l = gesture->getFrames();
    for(int i = 0; i < l->count(); i++)
    {
         //qDebug() << ((SkeletonData)l->at(i)).toString() << "<=>"<< ((RawJointState)rjsList.at(i)).toString();
         CPPUNIT_ASSERT_EQUAL(((SkeletonData*)l->at(i))->toString().compare(((RawJointState*)rjsList.at(i))->toString()), 0) ;
    }

    Gesture *gesture2 = Gesture::fromFile("not_existing.log");
    CPPUNIT_ASSERT(gesture2 == NULL);
}
