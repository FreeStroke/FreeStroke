#ifndef LRACONVERGEDTEST_H
#define LRACONVERGEDTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../includes/gestures/algorithm/logisticregressionalgorithm.h"

class LRAConvergedTest : public CppUnit::TestCase
{
public:
    friend class LogisticRegressionAlgorithm;
    LRAConvergedTest(std::string name);
    void runTest();
};

#endif // LRACONVERGEDTEST_H
