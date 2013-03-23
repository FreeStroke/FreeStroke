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
#include "../includes/keytest.h"
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

#include <QtCore/QDebug>

KeyTest::KeyTest(std::string name) : CppUnit::TestCase(name) {}

void KeyTest::runTest()
{
    CPPUNIT_ASSERT(KeyConverter::keyFromText("A") == Qt::Key_A);
    CPPUNIT_ASSERT(KeyConverter::textFromKey(Qt::Key_A) == "A");

    CPPUNIT_ASSERT(KeyConverter::keyFromText("Shift") == Qt::Key_Shift);
    CPPUNIT_ASSERT(KeyConverter::textFromKey(Qt::Key_Shift) == "Shift");

    CPPUNIT_ASSERT(KeyConverter::keyFromText("Ctrl") == Qt::Key_Control);
    CPPUNIT_ASSERT(KeyConverter::textFromKey(Qt::Key_Control) == "Ctrl");

    CPPUNIT_ASSERT(KeyConverter::keyFromText(QString::fromUtf8("À")) == Qt::Key_Agrave);
    CPPUNIT_ASSERT(KeyConverter::textFromKey(Qt::Key_Agrave) == QString::fromUtf8("À"));

    bool shift = false;
    bool ctrl = false;
    bool meta = false;
    bool alt = false;
    bool altgr = false;
    int key = 0;

    CPPUNIT_ASSERT(KeyConverter::fromText(QString::fromUtf8("Shift\tAlt\tCtrl\tAltGr\tMeta\tA"), &key, &shift, &ctrl, &alt, &meta, &altgr));
    CPPUNIT_ASSERT(shift == true);
    CPPUNIT_ASSERT(ctrl == true);
    CPPUNIT_ASSERT(alt == true);
    CPPUNIT_ASSERT(altgr == true);
    CPPUNIT_ASSERT(meta == true);
    CPPUNIT_ASSERT(key == Qt::Key_A);
}
