#ifndef UITEST_H
#define UITEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../includes/mainwindow.h"

class UiTest : public CppUnit::TestCase
{
public:
    UiTest(std::string name, MainWindow * w);
    void runTest();

private:
    MainWindow * w;
};

#endif // UITEST_H
