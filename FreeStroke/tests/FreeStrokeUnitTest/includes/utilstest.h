#ifndef UTILSTEST_H
#define UTILSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class UtilsTest : public CppUnit::TestCase
{
public:
    UtilsTest(std::string name);
    void runTest();
};

#endif // UTILSTEST_H
