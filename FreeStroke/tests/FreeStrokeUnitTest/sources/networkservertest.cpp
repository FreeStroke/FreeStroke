#include "../includes/networkservertest.h"

NetowkrServerTest::NetowkrServerTest(std::string name) : CppUnit::TestCase(name) {}

void NetowkrServerTest::runTest()
{
    CPPUNIT_ASSERT( 1 == 1);
    CPPUNIT_ASSERT( !(1 == 2));
}
