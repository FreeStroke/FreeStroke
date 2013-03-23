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
/*!
 * \file stepstutorial.h
 * \brief The StepsNewGesture class contains all the Step to display in the tutorial Stepper
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef STEPSTUTORIAL_H
#define STEPSTUTORIAL_H

#include <QtCore/QObject>
#include <QtGui/QWidget>

#include "../../includes/ui/stepper/stepper.h"

/*!
 * \brief The StepsNewGesture class contains all the Step to display in the tutorial Stepper
 */
class StepsTutorial : QObject
{
    Q_OBJECT
public:
    /*!
     * \brief StepsTutorial default constructor
     * \param pParent the QWidget parent
     * \param isFirstLaunch boolean determining if this is the first launch of the application. If so, ask to add a Controller.
     */
    explicit StepsTutorial(QWidget *pParent = 0, bool isFirstLaunch = true);
    /*!
     * \brief Launch the execution of the stepper associated to the StepsTutorial instance.
     * \return The exit code of the process.
     */
    int show();

private:
    /*!
     * \brief stepper the Stepper which will be displayed
     */
    Stepper* stepper;
    //ExecutionManager* executionManager;
    //GlView* glViewStep4;

private slots:
    /*!
     * \brief Discover the KController ready to connect with a Freestroke Client.
     */
    void discoverController();
};

#endif // STEPSTUTORIAL_H
