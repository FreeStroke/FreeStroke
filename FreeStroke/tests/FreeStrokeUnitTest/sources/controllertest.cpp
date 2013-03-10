#include "../includes/controllertest.h"
#include "../../includes/common/controller.h"

ControllerTest::ControllerTest(std::string name) : CppUnit::TestCase(name) {}

void ControllerTest::runTest()
{
    // Test controller object consistency
    Controller *c = new Controller("111.222.333.444", 12345, "TestController");
    CPPUNIT_ASSERT(c->getIpAddr().compare("111.222.333.444") == 0);
    CPPUNIT_ASSERT(c->getName().compare("TestController") == 0);
    CPPUNIT_ASSERT(c->getPort() == 12345);
}
