#ifndef COMMANDTEST_H
#define COMMANDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class CommandTest : public CppUnit::TestCase
{
public:
    CommandTest(std::string name);
    void runTest();
};

#endif // COMMANDTEST_H
