#include "../includes/inputgesturetest.h"

#include "../../includes/gestures/data/rawjointstate.h"
#include "../../includes/gestures/data/inputgesture.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

InputGestureTest::InputGestureTest(std::string name) : CppUnit::TestCase(name) {}

void InputGestureTest::runTest()
{
    QString testing = QString("others/clap.log");
    QString testing2 = QString("others/jump.log");
    QList<RawJointState*> list = RawJointState::fromFile(testing);
    QString listStr = "";

    // Creating gestures from a list and from addJointState
    InputGesture *ig = new InputGesture();
    for(int i = 0; i < list.count(); i++)
    {
        ig->addJointState((RawJointState*)list.at(i));
        listStr.append(((RawJointState*)list.at(i))->toString() + "\n");
    }

    // Creating another gesture
    InputGesture *ig3 = new InputGesture();
    QList<RawJointState*> list3 = RawJointState::fromFile(testing2);
    for(int i = 0; i < list.count(); i++)
    {
        ig3->addJointState((RawJointState*)list3.at(i));
    }

    InputGesture *ig2 = new InputGesture(&list);
    CPPUNIT_ASSERT(ig->startTime == list.first()->timestamp);
    CPPUNIT_ASSERT(ig2->startTime == list.first()->timestamp);
    CPPUNIT_ASSERT(ig->totalTime() == ig2->totalTime());
    CPPUNIT_ASSERT(ig3->totalTime() != ig2->totalTime());
    for(int i = 0; i < ig->states->count(); i++)
    {
        CPPUNIT_ASSERT(ig->states->at(i)->toString().compare(ig2->states->at(i)->toString()) == 0);
    }

    Gesture * gest = Gesture::fromFile(testing);
    CPPUNIT_ASSERT(gest->toString().compare(InputGesture::toGesture(ig)->toString()) == 0);
    CPPUNIT_ASSERT(gest->toString().compare(InputGesture::toGesture(ig3)->toString()) != 0);
}
