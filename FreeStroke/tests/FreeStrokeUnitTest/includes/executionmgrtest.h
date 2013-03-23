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
#ifndef EXECUTIONMGRTEST_H
#define EXECUTIONMGRTEST_H

#include "../../includes/common/gesture.h"
#include "../../includes/gestures/executionmanager.h"

#include <cppunit/extensions/HelperMacros.h>
#include <QtCore/QObject>

class ExecutionMgrTest : public QObject, public CppUnit::TestCase
{
    Q_OBJECT
public:
    ExecutionMgrTest(std::string name);
    void runTest();

public slots:
    void gestureConflict(Gesture* pGesture);
    void gestureRecognized(Gesture* pGesture);
    void gestureRecorded(Gesture* pGesture);
    void skeletonDataReceived(SkeletonData* pData);
    void trainingEnded();

private:
    bool gestureRecon, gestureConf, gestureRecord, trainingDone, dataReceived;
    /* Here it is assumed that the segmenter and the lra work as expected */
    void testNewDataSkeletonData(Role pRole);
    void testRecognizer();
    void testStartRecorder();
    void testStartTraining();
    void testRecordGesture();
    void testRecognizeGesture();
};

#endif // EXECUTIONMGRTEST_H
