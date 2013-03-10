#ifndef GESTURETEST_H
#define GESTURETEST_H

#include "cppunit/extensions/HelperMacros.h"

class GestureTest : public CppUnit::TestCase
{
public:
    GestureTest(std::string name);
    void runTest();
};

#endif // GESTURETEST_H
