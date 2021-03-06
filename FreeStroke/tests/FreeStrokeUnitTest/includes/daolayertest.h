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
#ifndef DAOLAYERTEST_H
#define DAOLAYERTEST_H
#include <cppunit/extensions/HelperMacros.h>

class DAOLayerTest : public CppUnit::TestCase
{
public:
    DAOLayerTest(std::string name);
    void runTest();
    void openTest();
    void closeTest();
    void gestureToCharTest();
    void gestureFromCharTest();
    void gesturesToCharTest();
    void gesturesFromCharTest();

    void insertTest();
    void updateTest();
    void deleteTest();
    void deleteExtendTest();
    void getTest();

    void insertHistoryTest();
    void deleteHistoryTest();
    void deleteExtendHistoryTest();
    void getHistoryTest();

    void insertNeutralGesture();
    void deleteNeutralGesture();
    void getNeutralGesture();

//    void failTest();
};

#endif // DAOLAYERTEST_H

