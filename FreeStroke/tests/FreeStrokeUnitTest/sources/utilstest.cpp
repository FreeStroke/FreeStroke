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
#include "../includes/utilstest.h"
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
#include "../../includes/common/utils.h"

#include <QtCore/QDir>
UtilsTest::UtilsTest(std::string name) : CppUnit::TestCase(name) {}

void UtilsTest::runTest()
{
    // test font
    QFont f("Arial");
    f.setPixelSize(12);
    CPPUNIT_ASSERT(Utils::getFont().family().compare(f.family()) == 0);
    CPPUNIT_ASSERT(Utils::getFont().pixelSize() == f.pixelSize());

    // test conf file
    QString conf = QDir::toNativeSeparators(Utils::getDatabaseDirectoryLocation() + "config.xml");
    CPPUNIT_ASSERT(Utils::getConfigLocation().compare(conf) == 0);

    // test conf dir
    QString dir = QString(":/");
    CPPUNIT_ASSERT(Utils::getResourcesDirectory().compare(dir) == 0);

    // test secure malloc
    char* str = (char*)Utils::secureMalloc(5);
    str = "helo\0";
    CPPUNIT_ASSERT(strcmp(str, "helo\0") == 0);

}
