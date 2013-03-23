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
#include "../includes/allfeaturestest.h"
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

#include "../../includes/gestures/features/allfeatures.h"

#include <QtCore/QDebug>

AllFeaturesTest::AllFeaturesTest(std::string name) : CppUnit::TestCase(name) {}

void AllFeaturesTest::runTest()
{
    return;
    /* -------------------------------
     * Testing GestureFeatures
     * -------------------------------
     */
    QList<RawJointState*> list = RawJointState::fromFile("others/clap.log");
    QList<RawJointState*> *rjsList = new QList<RawJointState*>();
    for(int i = 0; i < list.count(); i++)
    {
        rjsList->append(list.at(i));
    }

    // Testing with clap gesture
    InputGesture *gesture = InputGesture::fromJointStates(rjsList);

    QList<float> results = AllFeatures::gestureFeatureResults(gesture);
    QList<float> expected = QList<float>();
    expected.append(0.5299032);
    expected.append(0.8769053);
    expected.append(0.563993);
    expected.append(0.4272553);
    expected.append(0.01967496);
    expected.append(0.9881827);
    expected.append(0.03631651);
    expected.append(0.03772903);
    expected.append(0.03122234);
    expected.append(0.01063834);
    expected.append(0.04877752);
    expected.append(0.9441665);
    expected.append(0.0310263);
    expected.append(0);
    expected.append(0.075);
    expected.append(0);
    expected.append(-1.495665);
    expected.append(0.025);
    expected.append(0);
    expected.append(-0.8658663);

    // Testing GestureFeatures results
    for(int i = 0; i < expected.count(); i++)
    {
        //qDebug()<<"had "<<results.at(i)<<" expected "<< expected.at(i);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(results.at(i), expected.at(i), 0.00001 );
    }


    /* -------------------------------
     * Testing NeutralStanceFeature
     * -------------------------------
     */

    QList<float> expectedVariances = QList<float>();
    expectedVariances.append(0.01629463);
    expectedVariances.append(0.008697385);
    expectedVariances.append(0.0142573);
    expectedVariances.append(0.08929195);
    expectedVariances.append(0.09091631);
    expectedVariances.append(0.07221991);
    expectedVariances.append(0.01293937);
    expectedVariances.append(0.4217213);
    expectedVariances.append(0.2119044);
    expectedVariances.append(0.14649);
    expectedVariances.append(0.02311843);
    expectedVariances.append(0.03178224);
    expectedVariances.append(0.01161025);
    expectedVariances.append(0.01789512);
    expectedVariances.append(0.02200648);
    expectedVariances.append(0.0133253);
    expectedVariances.append(0.01133756);
    expectedVariances.append(0.02152017);
    expectedVariances.append(0.02272098);
    expectedVariances.append(0.01930015);

    QList<Gesture*> *neutralGestures = new QList<Gesture*>();
    // For testing : Save ns sample files (ns_00.log to ns_02.log)
    int count = 0;
    for(int j = 0; j < 3; j++)
    {
        QString fname;
        fname.append("ns_0");
        fname.append(QString::number(j));
        fname.append(".log");
        Gesture *gest = Gesture::fromFile("others/" + fname);
        neutralGestures->append(gest);
        count += gest->getFrames()->count();
    }

    // Save neutral feature data
    AllFeatures::saveNeutralFeature(neutralGestures);

    // Load and train neutral model
    QList<float> *variances = AllFeatures::loadNeutralFeature();

    CPPUNIT_ASSERT(variances != NULL);
    CPPUNIT_ASSERT(variances->count() == expectedVariances.count());
    for(int i = 0; i < variances->count(); i++)
    {
       // qDebug()<<"had "<<variances->at(i)<<" expected "<< expectedVariances.at(i);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(variances->at(i), expectedVariances.at(i), 0.00001 );
    }

}
