#ifndef XMLCONFIGTEST_H
#define XMLCONFIGTEST_H
#include <cppunit/extensions/HelperMacros.h>

class XmlConfigTest : public CppUnit::TestCase
{
public:
    XmlConfigTest(std::string name);
    void runTest();

    void exportConfigTest();
    void importConfigTest();
};
#endif // XMLCONFIGTEST_H
