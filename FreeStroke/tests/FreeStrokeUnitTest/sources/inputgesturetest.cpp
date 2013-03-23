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
#include "../includes/inputgesturetest.h"
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
#include "../../includes/gestures/data/inputgesture.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

InputGestureTest::InputGestureTest(std::string name) : CppUnit::TestCase(name) {}

void InputGestureTest::runTest()
{
    QString testing = QString("others/clap.log");
    QString testing2 = QString("others/jump.log");
    QList<RawJointState*> list = RawJointState::fromFile(testing);
    QString listStr = "";

    // Creating gestures from a list and from addJointState
    InputGesture *ig = new InputGesture();
    for(int i = 0; i < list.count(); i++)
    {
        ig->addJointState((RawJointState*)list.at(i));
        listStr.append(((RawJointState*)list.at(i))->toString() + "\n");
    }

    // Creating another gesture
    InputGesture *ig3 = new InputGesture();
    QList<RawJointState*> list3 = RawJointState::fromFile(testing2);
    for(int i = 0; i < list.count(); i++)
    {
        ig3->addJointState((RawJointState*)list3.at(i));
    }

    InputGesture *ig2 = new InputGesture(&list);
    CPPUNIT_ASSERT(ig->startTime == list.first()->timestamp);
    CPPUNIT_ASSERT(ig2->startTime == list.first()->timestamp);
    CPPUNIT_ASSERT(ig->totalTime() == ig2->totalTime());
    CPPUNIT_ASSERT(ig3->totalTime() != ig2->totalTime());
    for(int i = 0; i < ig->states->count(); i++)
    {
        CPPUNIT_ASSERT(ig->states->at(i)->toString().compare(ig2->states->at(i)->toString()) == 0);
    }

    Gesture * gest = Gesture::fromFile(testing);
    CPPUNIT_ASSERT(gest->toString().compare(InputGesture::toGesture(ig)->toString()) == 0);
    CPPUNIT_ASSERT(gest->toString().compare(InputGesture::toGesture(ig3)->toString()) != 0);
}
