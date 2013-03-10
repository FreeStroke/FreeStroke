#include "../includes/segmentertest.h"

#include "../../includes/gestures/segmenter.h"
#include "../../includes/gestures/features/allfeatures.h"
#include "../../includes/daolayer/daolayer.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

SegmenterTest::SegmenterTest(std::string name) : CppUnit::TestCase(name) {}

void SegmenterTest::runTest()
{
    //return;
    // create gesture names file
    QList<QString> gestureNames = QList<QString>();
#warning Must change test files to final generated files
    gestureNames.append("track_flick_left");
    gestureNames.append("track_flick_right");
    gestureNames.append("track_jump");
    gestureNames.append("track_clap");
    gestureNames.append("track_kick_left");
    gestureNames.append("track_kick_right");
    gestureNames.append("track_punch_left");


    Segmenter *seg = new Segmenter();

    for(int j = 0; j < gestureNames.count(); j++)
    {

        QString testing = gestureNames.at(j);

        InputGesture *gesture = InputGesture::fromGesture(Gesture::fromFile("others/"+testing+"_00.log"));
        CPPUNIT_ASSERT(gesture != NULL);
        int i = 0;
        for(i = 0; i < gesture->states->count(); i++)
        {
            CPPUNIT_ASSERT(gesture->states->at(i) != NULL);
            if(seg->addState(gesture->states->at(i)))
            {
                break;
            }

        }
        if(testing.compare("track_clap") == 0)
        {
            CPPUNIT_ASSERT(i >= gesture->states->count());
        }
        else
        {
            CPPUNIT_ASSERT(i < gesture->states->count());

            InputGesture *segmented = seg->getLastInputGesture();
            CPPUNIT_ASSERT(segmented != NULL);
            CPPUNIT_ASSERT(segmented->totalTime() <= gesture->totalTime());
            seg->clear();
        }
    }

    seg->setRole(S_INACTIVE);
    CPPUNIT_ASSERT(seg->getRole() == S_INACTIVE);

    DAOLayer *dao = DAOLayer::getInstance();
    CPPUNIT_ASSERT(dao != NULL);
    CPPUNIT_ASSERT(dao->removeNeutralGesture() == 0);

    Segmenter *seg2 = new Segmenter();
    CPPUNIT_ASSERT(dao->getNeutralGestures() != NULL);


}
