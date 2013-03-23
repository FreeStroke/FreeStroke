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
#include "../includes/segmentertest.h"
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

#include "../../includes/gestures/segmenter.h"
#include "../../includes/gestures/features/allfeatures.h"
#include "../../includes/daolayer/daolayer.h"

#include <QtCore/QList>
#include <QtCore/QDebug>

SegmenterTest::SegmenterTest(std::string name) : CppUnit::TestCase(name) {}

void SegmenterTest::runTest()
{
    //return;
    // create gesture names file
    QList<QString> gestureNames = QList<QString>();
#warning Must change test files to final generated files
    gestureNames.append("track_flick_left");
    gestureNames.append("track_flick_right");
    gestureNames.append("track_jump");
    gestureNames.append("track_clap");
    gestureNames.append("track_kick_left");
    gestureNames.append("track_kick_right");
    gestureNames.append("track_punch_left");


    Segmenter *seg = new Segmenter();

    for(int j = 0; j < gestureNames.count(); j++)
    {

        QString testing = gestureNames.at(j);

        InputGesture *gesture = InputGesture::fromGesture(Gesture::fromFile("others/"+testing+"_00.log"));
        CPPUNIT_ASSERT(gesture != NULL);
        int i = 0;
        for(i = 0; i < gesture->states->count(); i++)
        {
            CPPUNIT_ASSERT(gesture->states->at(i) != NULL);
            if(seg->addState(gesture->states->at(i)))
            {
                break;
            }

        }
        if(testing.compare("track_clap") == 0)
        {
            CPPUNIT_ASSERT(i >= gesture->states->count());
        }
        else
        {
            CPPUNIT_ASSERT(i < gesture->states->count());

            InputGesture *segmented = seg->getLastInputGesture();
            CPPUNIT_ASSERT(segmented != NULL);
            CPPUNIT_ASSERT(segmented->totalTime() <= gesture->totalTime());
            seg->clear();
        }
    }

    seg->setRole(S_INACTIVE);
    CPPUNIT_ASSERT(seg->getRole() == S_INACTIVE);

    DAOLayer *dao = DAOLayer::getInstance();
    CPPUNIT_ASSERT(dao != NULL);
    CPPUNIT_ASSERT(dao->removeNeutralGesture() == 0);

    Segmenter *seg2 = new Segmenter();
    CPPUNIT_ASSERT(dao->getNeutralGestures() != NULL);


}
