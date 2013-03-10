#ifndef RECOGNIZERTEST_H
#define RECOGNIZERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class RecognizerTest : public CppUnit::TestCase
{
public:
    RecognizerTest(std::string name);
    void runTest();
};

#endif // RECOGNIZERTEST_H
