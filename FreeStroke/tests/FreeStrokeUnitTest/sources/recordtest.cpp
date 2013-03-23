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
#include "../includes/recordtest.h"
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
#include "../../includes/common/gesture.h"
#include "../../includes/daolayer/record.h"

#include <QtCore/QDate>
RecordTest::RecordTest(std::string name) : CppUnit::TestCase(name) {}

void RecordTest::runTest()
{
    QString name = QString("testRecord");
    QList<Gesture*> *gestList = new QList<Gesture*>();
    QList<Gesture*> *gestList2 = new QList<Gesture*>();
    gestList->append(Gesture::fromFile("others/clap.log"));
    Command *c = new Command("CTRL  Q", KEYSTROKE);
    Command *c2 = new Command("CTRL  R", KEYSTROKE);
    Record *r = new Record(name, gestList, c);
    r->setName("plop");
    r->setCreationDate(QDate().currentDate().addDays(2).toString("yyyy-MM-dd"));
    r->setCommand(c2);
    r->setGestures(gestList2);
    r->setGestureActive(false);
    CPPUNIT_ASSERT(r->getName().compare("plop") == 0);
    CPPUNIT_ASSERT(r->getCreationDate().compare(QDate().currentDate().addDays(2).toString("yyyy-MM-dd")) == 0);
    CPPUNIT_ASSERT(r->getCommand()->getDefinition().compare(c2->getDefinition()) == 0);
    CPPUNIT_ASSERT(r->getCommand()->getType() == c2->getType());
    CPPUNIT_ASSERT(!r->isGestureActive());


}
