#ifndef KEYTEST_H
#define KEYTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include <../../includes/ui/element/keylistener/keyconverter.h>

class KeyTest : public CppUnit::TestCase
{
public:
    KeyTest(std::string name);
    void runTest();
};

#endif // KEYTEST_H
