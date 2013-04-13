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
#include <math.h>

#include "../../includes/gestures/features/gesturefeatures.h"
#include "../../includes/gestures/data/rawjointstate.h"

#include "../../includes/common/math.h"

/**
 * -----------------------------------------
 *
 * Internal gesture feature JointAmplitude
 *
 * -----------------------------------------
 */
JointAmplitude::JointAmplitude(QString jn, RawJointState::JointComponent jc, bool d)
{
    this->jointName = jn;
    this->jointComponent = jc;
    this->directional = d;
}

float JointAmplitude::queryGesture(InputGesture *pIg)
{
    float min = ((RawJointState*)pIg->states->at(0))->component(this->jointName, this->jointComponent);
    float max = min;
    int minIdx = 0, maxIdx = 0;


    for(int i = 0; i < pIg->states->count(); i++)
    {
        float current = (float)((RawJointState*)pIg->states->at(i))->component(this->jointName, this->jointComponent);
       // qDebug()<< "current="<<current<<"max="<<max<<" min="<<min;
        if(current < min)
        {
            min = current;
            minIdx = i;
        }
        if(current > max)
        {
            max = current;
            maxIdx = i;
        }
    }
        // qDebug()<<"max="<<max<<" min="<<min;
    if (this->directional)
    {
        bool before = (minIdx < maxIdx);
        return (before) ? (float)max - min : (float)min - max;
    }
    return (float)max - min;
}



/**
 * -----------------------------------------
 *
 * Internal gesture feature NeutralDeviation
 *
 * -----------------------------------------
 */
NeutralDeviation::NeutralDeviation(QString jn, RawJointState::JointComponent jc)
{
    jointName = jn;
    jointComponent = jc;
}

float NeutralDeviation::queryGesture(InputGesture *pIg)
{
    float np = ((RawJointState*)pIg->states->at(0))->component(this->jointName, this->jointComponent)
            +((RawJointState*)pIg->states->at(pIg->states->count() - 1))->component(this->jointName, this->jointComponent);
    np /=2.0f;
    float posd = 0;
    float negd = 0;
    int i;
    for(i = 0; i < pIg->states->count(); i++)
    {
        float current = ((RawJointState*)pIg->states->at(i))->component(this->jointName, this->jointComponent);
        if(current >= np)
        {
            posd += current - np;
        }
        else
        {
            negd += current - np;
        }
    }
    return posd + negd;
}




/**
 * -----------------------------------------
 *
 * Internal gesture feature NeckAmplitude
 *
 * -----------------------------------------
 */
float NeckAmplitude::queryGesture(InputGesture *pIg)
{
    float min = ((RawJointState*)pIg->states->at(0))->neckPos.y;
    float max = min;
    int i = 0;
    for(i = 0; i < pIg->states->count(); i++)
    {
        float current = ((RawJointState*)pIg->states->at(i))->neckPos.y;
        if(current < min)
        {
            min = current;
        }
    }

    for(i = 0; i < pIg->states->count(); i++)
    {
        float current = ((RawJointState*)pIg->states->at(i))->neckPos.y;
        if(current > max)
        {
            max = current;
        }
    }
    return max - min;
}


/**
 * -----------------------------------------
 *
 * Internal gesture feature ProportionChange
 *
 * -----------------------------------------
 */
ProportionChange::ProportionChange(QString jn, RawJointState::JointComponent jc)
{
    this->jointName = jn;
    this->jointComponent = jc;
}

float ProportionChange::queryGesture(InputGesture *pIg)
{
    float sum = 0.0f;
    int i;
    for(i = 1; i < pIg->states->count(); i++)
    {
        sum += (float) Math::abs(((RawJointState*)pIg->states->at(i))->component(this->jointName, this->jointComponent)
                           - ((RawJointState*)pIg->states->at(i - 1))->component(this->jointName, this->jointComponent));
    }

    return sum / pIg->states->count();
}


/**
 * -----------------------------------------
 *
 * Internal gesture feature NumberCriticalPoints
 *
 * -----------------------------------------
 */
NumberCriticalPoints::NumberCriticalPoints(QString jn, RawJointState::JointComponent jc)
{
    this->jointName = jn;
    this->jointComponent = jc;
}

float NumberCriticalPoints::queryGesture(InputGesture *pIg)
{

    float min = ((RawJointState*)pIg->states->at(0))->component(this->jointName, this->jointComponent);
    float max = min;
    int i = 0;

    for(i = 0; i < pIg->states->count(); i++)
    {
        float current = ((RawJointState*)pIg->states->at(i))->component(this->jointName, this->jointComponent);
        if(current < min)
        {
            min = current;
        }
    }

    for(i = 0; i < pIg->states->count(); i++)
    {
        float current = ((RawJointState*)pIg->states->at(i))->component(this->jointName, this->jointComponent);
        if(current > max)
        {
            max = current;
        }
    }

    float center = (max + min) / 2.0f;
    float dist_threshold = 0.5f;

    bool dir = ((((RawJointState*)pIg->states->at(1))->component(this->jointName, this->jointComponent) -
                 ((RawJointState*)pIg->states->at(0))->component(this->jointName, this->jointComponent)) > 0.0f);
    int count = 0;
    int sinceLast = 100;

    for (int i = 1; i < pIg->states->count(); i++)
    {
        float maxthres = (max - center) * dist_threshold;
        float minthres = (min - center) * dist_threshold;

        float current = ((RawJointState*)pIg->states->at(i))->component(this->jointName, this->jointComponent);
        float previous = ((RawJointState*)pIg->states->at(i - 1))->component(this->jointName, this->jointComponent);

        bool newdir = ((current - previous) > 0.0f);

        if ( newdir != dir && sinceLast > 10 )
        {
            float relpos = current - center;
            if ( relpos > maxthres || relpos < minthres )
            {
                count++;
            }
            sinceLast = 0;
        }
        dir = newdir;
        sinceLast++;
    }

    return (float)count / (float)pIg->states->count();
}

/**
 * -----------------------------------------
 *
 * Internal gesture feature DerivativeSum
 *
 * -----------------------------------------
 */
DerivativeSum::DerivativeSum(QString jn, RawJointState::JointComponent jc)
{
    this->jointName = jn;
    this->jointComponent = jc;
}

float DerivativeSum::queryGesture(InputGesture *pIg)
{
    float count = 0.0f;
    float sum = 0.0f;
    for (int i = 1; i < pIg->states->count(); i++)
    {
        //WARNING : INITIALLY ->  x => x.Component("right-palm", JointState.JointComponent.PosZ) > 0.15f
        float currentRightPalm = ((RawJointState*)pIg->states->at(i))->component(QString("right-palm"), RawJointState::PosZ);
        float currentComponent = ((RawJointState*)pIg->states->at(i))->component(this->jointName, this->jointComponent);
        float previousComponent = ((RawJointState*)pIg->states->at(i - 1))->component(this->jointName, this->jointComponent);

        if (currentRightPalm > 0.15f)
        {
            sum += currentComponent - previousComponent;
            count += 1.0f;
        }
    }

    return (count == 0.0f) ? 0.0f : sum / count;
}

/**
 * -----------------------------------------
 *
 * Internal gesture feature AxisCoincidence
 *
 * -----------------------------------------
 */
AxisCoincidence::AxisCoincidence(QString jn, RawJointState::JointComponent ja, RawJointState::JointComponent jb)
{
    this->jointName = jn;
    this->jointComponentA = ja;
    this->jointComponentB = jb;
}

float AxisCoincidence::queryGesture(InputGesture *pIg)
{
    double sum = 0.0f;
    for (int i = 1; i < pIg->states->count(); i++)
    {
        RawJointState *state = ((RawJointState*)pIg->states->at(i));
        RawJointState *pstate = ((RawJointState*)pIg->states->at(i - 1));

        float componentA = state->component(this->jointName, this->jointComponentA) - pstate->component(this->jointName, this->jointComponentA);
        float componentB = state->component(this->jointName, this->jointComponentB) - pstate->component(this->jointName, this->jointComponentB);

        if (componentA > 0.0f)
        {
            sum += componentB;
        }
        else
        {
            sum -= componentB;
        }
    }

    return (float)(sum * 100.0) / (float)pIg->states->count();
}

/**
 * -----------------------------------------
 *
 * Internal gesture feature MinDistance
 *
 * -----------------------------------------
 */
MinDistance::MinDistance(QString jnA, QString jnB)
{
    this->jointNameA = jnA;
    this->jointNameB = jnB;
}

float MinDistance::queryGesture(InputGesture *pIg)
{
    float min = Vector3::substract(((RawJointState*)pIg->states->at(0))->pos(this->jointNameA), ((RawJointState*)pIg->states->at(0))->pos(this->jointNameB)).lengthFast();
    int i;
    for(i = 0; i < pIg->states->count(); i++)
    {
        float current = Vector3::substract(((RawJointState*)pIg->states->at(i))->pos(this->jointNameA), ((RawJointState*)pIg->states->at(i))->pos(this->jointNameB)).lengthFast();
        if(current < min)
        {
            min = current;
        }
    }
    return min;
}

/**
 * -----------------------------------------
 *
 * Internal gesture feature MaxDistance
 *
 * -----------------------------------------
 */
MaxDistance::MaxDistance(QString jnA, QString jnB)
{
    this->jointNameA = jnA;
    this->jointNameB = jnB;
}

float MaxDistance::queryGesture(InputGesture *pIg)
{
    float max = Vector3::substract(((RawJointState*)pIg->states->at(0))->pos(this->jointNameA), ((RawJointState*)pIg->states->at(0))->pos(this->jointNameB)).lengthFast();
    for(int i = 0; i < pIg->states->count(); i++)
    {
        float current = Vector3::substract(((RawJointState*)pIg->states->at(i))->pos(this->jointNameA), ((RawJointState*)pIg->states->at(i))->pos(this->jointNameB)).lengthFast();
        if(current > max)
        {
            max = current;
        }
    }
    return max;
}

