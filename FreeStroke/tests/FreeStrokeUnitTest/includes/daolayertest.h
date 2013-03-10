#ifndef DAOLAYERTEST_H
#define DAOLAYERTEST_H
#include <cppunit/extensions/HelperMacros.h>

class DAOLayerTest : public CppUnit::TestCase
{
public:
    DAOLayerTest(std::string name);
    void runTest();
    void openTest();
    void closeTest();
    void gestureToCharTest();
    void gestureFromCharTest();
    void gesturesToCharTest();
    void gesturesFromCharTest();

    void insertTest();
    void updateTest();
    void deleteTest();
    void deleteExtendTest();
    void getTest();

    void insertHistoryTest();
    void deleteHistoryTest();
    void deleteExtendHistoryTest();
    void getHistoryTest();

    void insertNeutralGesture();
    void deleteNeutralGesture();
    void getNeutralGesture();

//    void failTest();
};

#endif // DAOLAYERTEST_H

