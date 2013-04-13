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
 * \file steppercontroller.h
 * \brief The Stepper class is a Stepper used for discovering and choosing Controller.
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef STEPPERCONTROLLER_H
#define STEPPERCONTROLLER_H

#include "stepper.h"

#include "../../includes/common/controller.h"
#include "../../includes/ui/cell/cellcontroller.h"

/*!
 * \brief The Stepper class is a Stepper used for discovering and choosing Controller.
*/
class StepperController : public Stepper
{
    Q_OBJECT
public:
    /*!
     * \brief StepperController default constructor
     * \param parent the parent Widget
     */
    explicit StepperController(QWidget *parent = 0);
    /*!
     * \brief getControllers returns a QList of Controller discovered.
     * \return a QList of Controller discovered.
     */
    QList<Controller*>* getControllers();
private:
    /*!
     * \brief controllers QList of Controller discovered.
     */
    QList<Controller*>* controllers;
    /*!
     * \brief cells QList of the Cell containing Controller
     */
    QList<Cell*>* cells;
    /*!
     * \brief communication the Communication
     */
    void *communication ;

signals:
    /*!
     * \brief requestDiscover signal emitted when the StepperController need to discover Controller
     */
    void requestDiscover(QList<Controller*>*);
    /*!
     * \brief controllerChosen signal emitted when the Controller has been chosen.
     */
    void controllerChosen(Controller*);

private slots:
    /*!
     * \brief discoverResponse slot is called when all the Controller have been discovered. It displays found Controller
     * and allow to select one.
     */
    void discoverResponse();
    /*!
     * \brief chooseController slot is called when a Controller has been chosen. It emit a controllerChose signal and go
     * to the next Step.
     */
    void chooseController();
    /*!
     * \brief previousStep slot is called when the  previous DialogButton is clicked on the Step displaying available Controller.
     * it relaunch a discover.
     */
    void previousStep();

};

#endif // STEPPERCONTROLLER_H
