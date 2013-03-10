#include "../../includes/common/math.h"

#include <math.h>

#include <QtCore/QDebug>

float Math::sigmoid(float pInput)
{
    return 1.0f / (1.0f + expf(-pInput));
}

float Math::calculateAngle (Vector3 pFirst, Vector3 pSecond)
{
    return acos(Vector3::dot(pFirst, pSecond) / (pFirst.length() * pSecond.length()));
}

float Math::inverseSqrtFast(float x)
{
    float num = 0.5f * x;
    int num2 = *(int*)(&x);
    num2 = 1597463174 - (num2 >> 1);
    x = *(float*)(&num2);
    x *= 1.5f - num * x * x;
    return x;
}

float Math::abs(float pValue)
{
    return (pValue >= 0.0f) ? pValue : (-pValue);
}

double Math::sigmoidD(double pInput)
{
    return 1.0 / (1.0 + exp(-pInput));
}

double Math::absD(double pValue)
{
    return (pValue >= 0.0) ? pValue : (-pValue);
}

int Math::max(int pFirst, int pSecond)
{
    return pFirst>pSecond?pFirst:pSecond;
}
