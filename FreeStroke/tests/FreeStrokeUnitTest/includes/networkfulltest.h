#ifndef NETWORKFULLTEST_H
#define NETWORKFULLTEST_H

#include <cppunit/extensions/HelperMacros.h>

class NetworkFullTest : public CppUnit::TestCase
{
public:
    NetworkFullTest(std::string name);
    void runTest();
};

#endif // NETWORKFULLTEST_H
