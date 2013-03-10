#ifndef CONTROLLERTEST_H
#define CONTROLLERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ControllerTest : public CppUnit::TestCase
{
public:
    ControllerTest(std::string name);
    void runTest();
};

#endif // CONTROLLERTEST_H
