#ifndef ALLFEATURESTEST_H
#define ALLFEATURESTEST_H

#include <cppunit/extensions/HelperMacros.h>

class AllFeaturesTest : public CppUnit::TestCase
{
public:
    AllFeaturesTest(std::string name);
    void runTest();
};

#endif // ALLFEATURESTEST_H
