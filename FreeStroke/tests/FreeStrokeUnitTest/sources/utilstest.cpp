#include "../includes/utilstest.h"
#include "../../includes/common/utils.h"

#include <QtCore/QDir>
UtilsTest::UtilsTest(std::string name) : CppUnit::TestCase(name) {}

void UtilsTest::runTest()
{
    // test font
    QFont f("Arial");
    f.setPixelSize(12);
    CPPUNIT_ASSERT(Utils::getFont().family().compare(f.family()) == 0);
    CPPUNIT_ASSERT(Utils::getFont().pixelSize() == f.pixelSize());

    // test conf file
    QString conf = QDir::toNativeSeparators(Utils::getDatabaseDirectoryLocation() + "config.xml");
    CPPUNIT_ASSERT(Utils::getConfigLocation().compare(conf) == 0);

    // test conf dir
    QString dir = QString(":/");
    CPPUNIT_ASSERT(Utils::getResourcesDirectory().compare(dir) == 0);

    // test secure malloc
    char* str = (char*)Utils::secureMalloc(5);
    str = "helo\0";
    CPPUNIT_ASSERT(strcmp(str, "helo\0") == 0);

}
