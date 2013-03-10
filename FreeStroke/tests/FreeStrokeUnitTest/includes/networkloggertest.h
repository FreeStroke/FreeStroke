#ifndef NETWORKCLIENTTEST_H
#define NETWORKCLIENTTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../../tools/FakeServer/KControllerCopy/logger.h"

class NetworkLoggerTest : public CppUnit::TestCase
{
public:
    NetworkLoggerTest(std::string name);
    void runTest();
};

#endif // NETWORKCLIENTTEST_H
