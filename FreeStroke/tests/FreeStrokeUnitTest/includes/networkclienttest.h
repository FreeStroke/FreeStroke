#ifndef NETWORKCLIENTTEST_H
#define NETWORKCLIENTTEST_H

#include <cppunit/extensions/HelperMacros.h>

class NetworkClientTest : public CppUnit::TestCase
{
public:
    NetworkClientTest(std::string name);
    void runTest();
};

#endif // NETWORKCLIENTTEST_H
