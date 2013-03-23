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
#include "../includes/gesturetest.h"
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
 * Copyright (C) 2010 Université Paris-Est Marne-la-Vallée 
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
 *
 */

#include "../../includes/gestures/data/rawjointstate.h"
#include "../../includes/common/gesture.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

GestureTest::GestureTest(std::string name) : CppUnit::TestCase(name) {}

void GestureTest::runTest()
{
    QList<RawJointState*> list = RawJointState::fromFile("others/clap.log");
    QList<RawJointState*> rjsList;
    for(int i = 0; i < list.count(); i++)
    {
        rjsList.append(list.at(i));
    }

    Gesture *gesture = Gesture::fromFile("others/clap.log");
    QList<SkeletonData*> *l = gesture->getFrames();
    for(int i = 0; i < l->count(); i++)
    {
         //qDebug() << ((SkeletonData)l->at(i)).toString() << "<=>"<< ((RawJointState)rjsList.at(i)).toString();
         CPPUNIT_ASSERT_EQUAL(((SkeletonData*)l->at(i))->toString().compare(((RawJointState*)rjsList.at(i))->toString()), 0) ;
    }

    Gesture *gesture2 = Gesture::fromFile("not_existing.log");
    CPPUNIT_ASSERT(gesture2 == NULL);
}
