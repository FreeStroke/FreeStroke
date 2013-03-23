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
#include "../../includes/gestures/algorithm/logisticregressionalgorithm.h"
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
#include "../../includes/gestures/data/inputgesture.h"

#include "../includes/logisticregressionalgorithmtest.h"

#include <QtCore/QDebug>
#include <QtCore/QHash>

LogisticRegressionAlgorithmTest::LogisticRegressionAlgorithmTest(std::string name) : CppUnit::TestCase(name) {}

void LogisticRegressionAlgorithmTest::runTest()
{
    // create gesture names file
    QList<QString> gestureNames = QList<QString>();
    gestureNames.append("track_clap");
    gestureNames.append("track_flick_left");
    gestureNames.append("track_flick_right");
    gestureNames.append("track_jump");
    gestureNames.append("track_kick_left");
    gestureNames.append("track_kick_right");
    gestureNames.append("track_punch_left");


    // create map of gestures for training
    QHash<Record*, QList<InputGesture*>*> *map = new QHash<Record*, QList<InputGesture*>*>();
    for(int i = 0; i < gestureNames.count(); i++)
    {
        QList<InputGesture*> *l = new QList<InputGesture*>();

        InputGesture *gesture0 = InputGesture::fromGesture(Gesture::fromFile("others/"+gestureNames.at(i) + "_01.log"));
        l->append(gesture0);


        InputGesture *gesture1 = InputGesture::fromGesture(Gesture::fromFile("others/"+gestureNames.at(i) + "_00.log"));
        l->append(gesture1);

        Record* record = new Record(gestureNames.at(i), NULL, NULL);
        map->insert(record, l);
    }


    LogisticRegressionAlgorithm *lra = new LogisticRegressionAlgorithm(0);

    // run train
    lra->train(map);

    while(!lra->wait()){}

    QList<Record*> *gestList = lra->getGestures();

    // tests results
    for(int j = 0; j < gestureNames.count(); j++)
    {
        QString testing = gestureNames.at(j);
        InputGesture *gesture = InputGesture::fromGesture(Gesture::fromFile("others/"+testing+"_00.log"));
        QList<QPair<Record*, double>* > *l = lra->recognizeSingleGesture(gesture);
        for(int i = 0; i < l->count(); i++)
        {
            CPPUNIT_ASSERT(gestList->contains(l->at(i)->first));
        }
        CPPUNIT_ASSERT((l->at(0)->first->getName().compare(testing)) == 0 && (l->at(0)->second > 0.7f));
    }
}


