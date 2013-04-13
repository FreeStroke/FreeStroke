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
#include "../../includes/gestures/features/neutralfeature.h"
#include "../../includes/gestures/features/allfeatures.h"

#include <math.h>

NeutralFeature::NeutralFeature()
{
    this->weights = new QList<float>;
    this->weights->append(0.1f); // Neck
    this->weights->append(0.1f); // Head
    this->weights->append(1.0f); // R shoulder
    this->weights->append(3.0f);
    this->weights->append(4.0f);
    this->weights->append(5.0f);
    this->weights->append(1.0f); // L shoulder
    this->weights->append(3.0f);
    this->weights->append(4.0f);
    this->weights->append(5.0f);
    this->weights->append(1.0f); // R hip
    this->weights->append(2.0f);
    this->weights->append(3.0f);
    this->weights->append(4.0f);
    this->weights->append(1.0f); // L hip
    this->weights->append(2.0f);
    this->weights->append(3.0f);
    this->weights->append(4.0f);
    this->weights->append(0.1f); // R pelvis
    this->weights->append(0.1f);
    this->weightsSum = 0;

    for(int i = 0; i < this->weights->count(); i++)
    {
        this->weightsSum += this->weights->at(i);
    }
}

Vector3 NeutralFeature::parent(RawJointState *pRjs, int pI)
{
    if ( pI >= 3 && pI <= 5 ) return pRjs->pos("right-shoulder");
    else if ( pI >= 7 && pI <= 9 ) return pRjs->pos("left-shoulder");
    else if ( pI >= 11 && pI <= 13 ) return pRjs->pos("right-hip");
    else if ( pI >= 15 && pI <= 17 ) return pRjs->pos("left-hip");
    return pRjs->neckPos;
}

float NeutralFeature::queryFrame (RawJointState *pRjs)
{
    float error_sum = 0.0f;
    for ( int i = 0; i < this->average.length(); i++ )
    {

        Vector3 reljoint = Vector3::substract(pRjs->relativeJoints[i], parent(pRjs, i));
        reljoint.normalizeFast();
        float error = Vector3::substract(reljoint, this->average.at(i)).lengthFast() / 2.0f;
        error_sum += (float)pow(error, 1.0f / this->weights->at(i));

    }

    float conf = 1.0f - error_sum / this->varianceSum / this->weightsSum;

    return conf;
}


QList<float> * NeutralFeature::train(QList<RawJointState*> *pStates)
{

    QList<RawJointState*> *sList = pStates;

    this->variance = new QList<float>();
    this->average = QList<Vector3>();
    for(int i=0; i<sList->at(0)->relativeJointsCount; i++)
    {
        this->average.append(sList->at(0)->relativeJoints[i]);
    }

    for(int i=0; i<this->average.length(); i++)
    {
        QList<Vector3> *relposes = new QList<Vector3>();

        for(int j=0; j<sList->count(); j++)
        {
            relposes->append(Vector3::substract(sList->at(j)->relativeJoints[i], parent(sList->at(j), i)));
            relposes->replace(j, Vector3::divide(relposes->at(j), ((Vector3)relposes->at(j)).lengthFast()));
        }

        this->average.replace(i, Vector3::zero());

        for (int j=0; j<relposes->count(); j++)
        {
            this->average.replace(i, Vector3::add(this->average.at(i), relposes->at(j)));
        }

        this->average.replace(i, Vector3::divide(this->average.at(i), (float)relposes->count()));

        float sum = 0;
        for (int j=0; j<relposes->count(); j++)
        {
            float f1 = Vector3::substract(relposes->at(j), this->average[i]).lengthFast();
            sum += f1*f1;

            if (this->variance->count() <= i)
            {
                this->variance->append(sum);
            }
            else
            {
                this->variance->replace(i, sum);
            }
        }
    }
    //qDebug()<<"Variances : ";
    this->varianceSum = 0;
    for(int i=0; i<this->variance->count(); i++)
    {
      //  qDebug()<<this->variance->at(i);
        this->varianceSum += this->variance->at(i);
    }
    return this->variance;
}


