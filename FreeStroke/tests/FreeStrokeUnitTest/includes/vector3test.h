#ifndef VECTOR3TEST_H
#define VECTOR3TEST_H

#include "cppunit/extensions/HelperMacros.h"

class Vector3Test : public CppUnit::TestCase
{
public:
    Vector3Test(std::string name);
    void runTest();

    void lengthTest();
    void dotLength();
};

#endif // VECTOR3TEST_H
