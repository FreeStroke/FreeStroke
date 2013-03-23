/*
* Projet de fin d'études LastProject de
* Adrien Broussolle
* Camille Darcy
* Guillaume Demurger
* Sylvain Fay-Chatelard
* Anthony Fourneau
* Aurèle Lenfant
* Adrien Madouasse
*
* Copyright (C) 2013 Université Paris-Est Marne-la-Vallée
*
* FreeStroke is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
*/
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
