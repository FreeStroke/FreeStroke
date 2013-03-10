#ifndef LOGGERTEST_H
#define LOGGERTEST_H

#include "cppunit/extensions/HelperMacros.h"

class LoggerTest : public CppUnit::TestCase
{
public:
    LoggerTest(std::string name);
    void runTest();
};

#endif // LOGGERTEST_H
