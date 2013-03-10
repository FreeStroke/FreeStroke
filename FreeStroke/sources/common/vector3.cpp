#include "../../includes/common/vector3.h"
#include "../../includes/common/math.h"

#include <math.h>

Vector3::Vector3(float pX, float pY, float pZ)
{
    this->x = pX;
    this->y = pY;
    this->z = pZ;
}

float Vector3::length()
{
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vector3::comp(int pComp)
{
    if (pComp == 0)
    {
        return this->x;
    }
    else if (pComp == 1)
    {
        return this->y;
    }
    return this->z;
}

void Vector3::normalizeFast()
{
    float num = Math::inverseSqrtFast(this->x * this->x + this->y * this->y + this->z * this->z);
    this->x *= num;
    this->y *= num;
    this->z *= num;
}

float Vector3::lengthFast()
{
    return 1.0 / Math::inverseSqrtFast(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vector3::dot(Vector3 pLeft, Vector3 pRight)
{
    return (pLeft.x * pRight.x + pLeft.y * pRight.y + pLeft.z * pRight.z);
}

Vector3 Vector3::add(Vector3 pLeft, Vector3 pRight)
{
    Vector3 v;
    v.x = pLeft.x + pRight.x;
    v.y = pLeft.y + pRight.y;
    v.z = pLeft.z + pRight.z;
    return v;
}

Vector3 Vector3::substract(Vector3 pLeft, Vector3 pRight)
{
    Vector3 v;
    v.x = pLeft.x - pRight.x;
    v.y = pLeft.y - pRight.y;
    v.z = pLeft.z - pRight.z;
    return v;
}

Vector3 Vector3::divide(Vector3 pLeft, float pScale)
{
    Vector3 v;
    float num = 1.0f / pScale;
    v.x = pLeft.x * num;
    v.y = pLeft.y * num;
    v.z = pLeft.z * num;
    return v;
}
