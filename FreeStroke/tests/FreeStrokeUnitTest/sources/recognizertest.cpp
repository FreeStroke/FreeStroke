#include "../includes/recognizertest.h"

#include "../../includes/gestures/segmenter.h"
#include "../../includes/gestures/features/allfeatures.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

RecognizerTest::RecognizerTest(std::string name) : CppUnit::TestCase(name) {}

void RecognizerTest::runTest()
{

    /*Recognizer *rec = xnew Recognizer();
    // Get testing data
    Gesture *testing = Gesture::fromFile("others/clap.log");
    DAOLayer *dao = DAOLayer::getInstance();
    CPPUNIT_ASSERT(dao != NULL);
    // Start and train recognizer
    rec->start();
    for(int i = 0; i < testing->getFrames()->count(); i++)
    {
        dao->dataFromCommunication(testing->getFrames()->at(i)->toString());
    }
*/


}
