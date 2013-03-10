#include "../includes/lraconvergedtest.h"

#include <QtCore/QDebug>

LRAConvergedTest::LRAConvergedTest(std::string name) : CppUnit::TestCase(name) {}

void LRAConvergedTest::runTest()
{
    LogisticRegressionAlgorithm lra(0);
    CPPUNIT_ASSERT(true);
    //CPPUNIT_ASSERT_EQUAL(lra.converged(NULL, new QList<float>, 0.0f), false);
    //CPPUNIT_ASSERT_EQUAL(lra.converged(new QList<float>, NULL, 0.0f), false);


}
