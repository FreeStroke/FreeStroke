#include "../includes/commandtest.h"
#include "../../includes/daolayer/command.h"
#include "../../includes/daolayer/commandtype.h"

CommandTest::CommandTest(std::string name) : CppUnit::TestCase(name) {}

void CommandTest::runTest()
{
    Command *c  = new Command("Ctrl t", KEYSTROKE);
    QHash<QString, int> map = Command::specialKeysMap();
    CPPUNIT_ASSERT(map.count() > 0);
    c->executeCommand();
}
