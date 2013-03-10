#ifndef TEST_H
#define TEST_H

#include <cppunit/extensions/HelperMacros.h>

class Test : public CppUnit::TestCase
{
public:
    Test(std::string name);
    void runTest();
};

#endif // TEST_H
