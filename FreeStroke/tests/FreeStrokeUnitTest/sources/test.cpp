#include "../includes/test.h"

Test::Test(std::string name) : CppUnit::TestCase(name) {}

void Test::runTest()
{
    CPPUNIT_ASSERT( 1 == 1);
    CPPUNIT_ASSERT( !(1 == 2));
}
