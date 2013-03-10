#ifndef XMLTEST_H
#define XMLTEST_H
#include <cppunit/extensions/HelperMacros.h>

class XmlTest : public CppUnit::TestCase
{
public:
    XmlTest(std::string name);
    void runTest();

    void exportTest();
    void importTest();
    void exportImportTest();
};
#endif // XMLTEST_H
