#ifndef RECORDTEST_H
#define RECORDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class RecordTest : public CppUnit::TestCase
{
public:
    RecordTest(std::string name);
    void runTest();
};

#endif // RECORDTEST_H
