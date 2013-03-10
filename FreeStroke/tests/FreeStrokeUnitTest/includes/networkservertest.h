#ifndef NETWORKSERVERTEST_H
#define NETWORKSERVERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class NetowkrServerTest : public CppUnit::TestCase
{
public:
    NetowkrServerTest(std::string name);
    void runTest();
};

#endif // NETWORKSERVERTEST_H
