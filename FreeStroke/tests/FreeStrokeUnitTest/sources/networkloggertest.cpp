#include "../includes/networkloggertest.h"

NetworkLoggerTest::NetworkLoggerTest(std::string name) : CppUnit::TestCase(name) {}

void NetworkLoggerTest::runTest()
{
    Logger* logger = new Logger("uniteTest.txt", false);
    try {
        logger->log((const char*) NULL,"test",INFO);
    }
    catch (int x)
    {
        CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(true);
}
