#include "../includes/networkclienttest.h"

NetworkClientTest::NetworkClientTest(std::string name) : CppUnit::TestCase(name) {}

void NetworkClientTest::runTest()
{
    CPPUNIT_ASSERT( 1 == 1);
    CPPUNIT_ASSERT( !(1 == 2));
}
