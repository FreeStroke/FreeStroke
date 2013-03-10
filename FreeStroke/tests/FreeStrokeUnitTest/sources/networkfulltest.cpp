#include "../includes/networkfulltest.h"

NetworkFullTest::NetworkFullTest(std::string name) : CppUnit::TestCase(name) {}

void NetworkFullTest::runTest()
{
    CPPUNIT_ASSERT( 1 == 1);
    CPPUNIT_ASSERT( !(1 == 2));
}
