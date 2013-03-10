#include <QtGui/QApplication>

#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "../../includes/mainwindow.h"

#include "../includes/test.h"
#include "../includes/daolayertest.h"
#include "../includes/rawjointstatetest.h"
#include "../includes/vector3test.h"
#include "../includes/inputgesturetest.h"
#include "../includes/gesturefeaturestest.h"
#include "../includes/allfeaturestest.h"
#include "../includes/skeletondatatest.h"
#include "../includes/gesturetest.h"
#include "../includes/logisticregressionalgorithmtest.h"
#include "../includes/segmentertest.h"
#include "../includes/keytest.h"
#include "../includes/recognizertest.h"
#include "../includes/xmltest.h"
#include "../includes/historyrecordtest.h"
#include "../includes/xmlconfigtest.h"
#include "../includes/executionmgrtest.h"
#include "../includes/controllertest.h"
#include "../includes/utilstest.h"
#include "../includes/commandtest.h"
#include "../includes/recordtest.h"
#include "../includes/networkloggertest.h"

#ifdef UNITTEST
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //--- Create the event manager and test controller
    CppUnit::TestResult controller;

    //--- Add a listener that colllects test result
    CppUnit::TestResultCollector result;
    controller.addListener(&result);

    //--- Add a listener that print dots as test run.
    CppUnit::BriefTestProgressListener progress;
    controller.addListener(&progress);

    //--- Create the application
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();*/


    /*
     *  Test DAOLayer
     **/

    //--- Add the top suite to the test runner
    CppUnit::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    runner.addTest(new Test("Test de base"));
    runner.addTest(new DAOLayerTest("DAOLayer test"));
    runner.addTest(new XmlTest("Xml class test"));
    runner.addTest(new XmlConfigTest("Xml config class test"));
    runner.addTest(new HistoryRecordTest("HistoryRecord class test"));
    runner.addTest(new CommandTest("Command class test"));

    /*
     *  Test Gestures
     **/

    runner.addTest(new RawJointStateTest("RawJointTest class test"));
    runner.addTest(new Vector3Test("Vector3 class test"));
    runner.addTest(new InputGestureTest("InputGesture class test"));
    runner.addTest(new GestureFeaturesTest("GestureFeatures class test"));
    runner.addTest(new AllFeaturesTest("AllFeatures class test"));
    runner.addTest(new SkeletonDataTest("SkeletonDataTest class test"));
    runner.addTest(new GestureTest("GestureTest class test"));
    runner.addTest(new LogisticRegressionAlgorithmTest("LogisticRegressionAlgorithmTest class test"));
    runner.addTest(new SegmenterTest("SegmenterTest class test"));
    runner.addTest(new ExecutionMgrTest("ExecutionManager class test"));
    /*
     *  Test Common
     **/

    runner.addTest(new ControllerTest("Controller class test"));
    runner.addTest(new UtilsTest("Utils class test"));
    runner.addTest(new RecordTest("Record class test"));

    /*
     *  Network
     *
     *------------ATTENTION! rebuild fakeserver or update KControllerCopy for networktest
     */
    runner.addTest(new NetworkLoggerTest("NetworkLogger class test"));

    /*
     * Test Key Event
    */
    //runner.addTest(new KeyTest("KeyTest class test"));

    runner.run(controller);

    std::ofstream xmlout("../../reports/cppunit.xml");
    CppUnit::XmlOutputter xmlOutputter(&result, xmlout);
    xmlOutputter.write();

    //a.quit();
    return result.wasSuccessful() ? 0 : 1;

    /*
#include <cppunit/ui/qt/TestRunner.h>
#include <cppunit/ui/qt/QtTestRunner.h>

    QApplication a(argc, argv);
    CppUnit::QtUi::TestRunner runner;

    MainWindow w;
    w.show();

    //runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    runner.addTest(new Test("Test de base"));
    runner.addTest(new UiTest("Test method of ui object", &w));
    runner.run();
    return a.exec();*/
}
#endif
