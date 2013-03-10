#include "../includes/vector3test.h"

#include "../../includes/common/vector3.h"

Vector3Test::Vector3Test(std::string name) : CppUnit::TestCase(name) {}

void Vector3Test::runTest()
{
    this->lengthTest();
    this->dotLength();
}


void Vector3Test::lengthTest()
{
    Vector3 v(10, 10, 10);
    Vector3 v2(10, 10, 10);

    CPPUNIT_ASSERT_EQUAL((float)17.32050808, v.length());
    CPPUNIT_ASSERT_EQUAL(v.length(), v2.length());
}

void Vector3Test::dotLength()
{
    Vector3 v(10, 10, 10);
    Vector3 v2(10, 10, 10);

    CPPUNIT_ASSERT_EQUAL((float)300, Vector3::dot(v, v2));
}
