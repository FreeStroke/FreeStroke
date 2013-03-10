#include "../../includes/gestures/algorithm/logisticregressionalgorithm.h"
#include "../../includes/gestures/data/inputgesture.h"

#include "../includes/logisticregressionalgorithmtest.h"

#include <QtCore/QDebug>
#include <QtCore/QHash>

LogisticRegressionAlgorithmTest::LogisticRegressionAlgorithmTest(std::string name) : CppUnit::TestCase(name) {}

void LogisticRegressionAlgorithmTest::runTest()
{
    // create gesture names file
    QList<QString> gestureNames = QList<QString>();
    gestureNames.append("track_clap");
    gestureNames.append("track_flick_left");
    gestureNames.append("track_flick_right");
    gestureNames.append("track_jump");
    gestureNames.append("track_kick_left");
    gestureNames.append("track_kick_right");
    gestureNames.append("track_punch_left");


    // create map of gestures for training
    QHash<Record*, QList<InputGesture*>*> *map = new QHash<Record*, QList<InputGesture*>*>();
    for(int i = 0; i < gestureNames.count(); i++)
    {
        QList<InputGesture*> *l = new QList<InputGesture*>();

        InputGesture *gesture0 = InputGesture::fromGesture(Gesture::fromFile("others/"+gestureNames.at(i) + "_01.log"));
        l->append(gesture0);


        InputGesture *gesture1 = InputGesture::fromGesture(Gesture::fromFile("others/"+gestureNames.at(i) + "_00.log"));
        l->append(gesture1);

        Record* record = new Record(gestureNames.at(i), NULL, NULL);
        map->insert(record, l);
    }


    LogisticRegressionAlgorithm *lra = new LogisticRegressionAlgorithm(0);

    // run train
    lra->train(map);

    while(!lra->wait()){}

    QList<Record*> *gestList = lra->getGestures();

    // tests results
    for(int j = 0; j < gestureNames.count(); j++)
    {
        QString testing = gestureNames.at(j);
        InputGesture *gesture = InputGesture::fromGesture(Gesture::fromFile("others/"+testing+"_00.log"));
        QList<QPair<Record*, double>* > *l = lra->recognizeSingleGesture(gesture);
        for(int i = 0; i < l->count(); i++)
        {
            CPPUNIT_ASSERT(gestList->contains(l->at(i)->first));
        }
        CPPUNIT_ASSERT((l->at(0)->first->getName().compare(testing)) == 0 && (l->at(0)->second > 0.7f));
    }
}


