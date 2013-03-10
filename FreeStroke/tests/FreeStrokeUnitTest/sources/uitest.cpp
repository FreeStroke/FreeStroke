#include "uitest.h"

UiTest::UiTest(std::string name, MainWindow * w) : CppUnit::TestCase(name)
{
    this->w = w;
}

void UiTest::runTest()
{
    CPPUNIT_ASSERT(10.f == this->w->testMethod(10.f));
}
