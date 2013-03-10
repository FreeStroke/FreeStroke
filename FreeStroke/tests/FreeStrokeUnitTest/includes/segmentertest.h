#ifndef SEGMENTERTEST_H
#define SEGMENTERTEST_H

#include "cppunit/extensions/HelperMacros.h"

class SegmenterTest : public CppUnit::TestCase
{
public:
    SegmenterTest(std::string name);
    void runTest();
};

#endif // SEGMENTERTEST_H
