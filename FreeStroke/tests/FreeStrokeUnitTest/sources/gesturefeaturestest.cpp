#include "../includes/gesturefeaturestest.h"

#include "../../includes/gestures/data/rawjointstate.h"
#include "../../includes/gestures/data/inputgesture.h"

#include "../../includes/gestures/features/gesturefeatures.h"

#include <QtCore/QDebug>

GestureFeaturesTest::GestureFeaturesTest(std::string name) : CppUnit::TestCase(name) {}

void GestureFeaturesTest::runTest()
{
    QList<RawJointState*> list = RawJointState::fromFile("others/clap.log");
    QList<RawJointState*> *rjsList = new QList<RawJointState*>();
    for(int i = 0; i < list.count(); i++)
    {
        rjsList->append(list.at(i));
    }

    // Testing with clap gesture
    InputGesture *gesture = InputGesture::fromJointStates(rjsList);


    // Creating features
    JointAmplitude jam = JointAmplitude("right-palm", RawJointState::PosX, false);
    JointAmplitude jam2 = JointAmplitude("right-wrist", RawJointState::Angle, false);
    ProportionChange pch = ProportionChange("right-palm", RawJointState::PosX);
    NeutralDeviation nde = NeutralDeviation("right-palm", RawJointState::PosX);
    NeckAmplitude nam = NeckAmplitude();
    NumberCriticalPoints ncp = NumberCriticalPoints("right-palm", RawJointState::PosX);
    DerivativeSum dsu = DerivativeSum("right-palm", RawJointState::PosX);
    AxisCoincidence aco = AxisCoincidence("right-palm", RawJointState::PosX, RawJointState::PosZ);
    MinDistance min = MinDistance("left-palm", "right-palm");
    MaxDistance max = MaxDistance("left-palm", "right-palm");


    // Asserts to test features
    CPPUNIT_ASSERT_DOUBLES_EQUAL( jam.queryGesture(gesture), 0.5299032, 0.00001 );

    // Should be min=-1,55355 max=-1,522327 for clap
    CPPUNIT_ASSERT_DOUBLES_EQUAL( jam2.queryGesture(gesture),  0.988183, 0.00001 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( pch.queryGesture(gesture), 0.01967496, 0.00001 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( nde.queryGesture(gesture), -1.495665, 0.00001 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( nam.queryGesture(gesture), 0.0310263, 0.00001 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( ncp.queryGesture(gesture), 0.025, 0.00001 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( dsu.queryGesture(gesture), 0, 0.00001 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( aco.queryGesture(gesture), -0.8658663, 0.00001 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( min.queryGesture(gesture), 0.04877752, 0.00001 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( max.queryGesture(gesture), 0.9441665, 0.00001 );
}
