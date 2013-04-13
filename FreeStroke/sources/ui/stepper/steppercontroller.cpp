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

#include "../../includes/mainwindow.h"
#include "../../includes/ui/stepper/steppercontroller.h"
#include "../../includes/ui/cell/cellcontroller.h"
#include "../../includes/network/communication.h"

StepperController::StepperController(QWidget *parent) : Stepper(parent)
{
    this->controllers = new QList<Controller*>();
    this->cells = new QList<Cell*>();

    disconnect(this->buttonPrevious, SIGNAL(clicked()), 0, 0);
    connect(this->buttonPrevious, SIGNAL(clicked()), this, SLOT(previousStep()));

    (MainWindow::getCommunication())->setStepper(this);
    connect(MainWindow::getCommunication(),SIGNAL(stopDiscover()),this,SLOT(discoverResponse()));
    emit requestDiscover(this->controllers);
}

void StepperController::discoverResponse()
{
    if(this->steps->at(this->currentStep + 1)->widget != NULL)
    {
        delete this->steps->at(this->currentStep + 1)->widget;
        this->steps->at(this->currentStep + 1)->widget = NULL;
    }
    QWidget* step2 = new QWidget(this);
    step2->setFixedSize(600,400);
    this->steps->at(this->currentStep + 1)->widget = step2;
    QVBoxLayout* layout = new QVBoxLayout(step2);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->steps->at(currentStep+1)->previousVisible(true);
    this->buttonPrevious->setText(tr("Search Again"));
    QFontMetrics metrics(this->buttonPrevious->font());
    this->buttonPrevious->resize(metrics.width(this->buttonPrevious->text()) + 10, this->buttonPrevious->height());
    this->organize();

    if(this->controllers->count() > 0)
    {
        Label* labelController = new Label("Click on the choosen controller", step2);
        labelController->setTextColor(QColor(255,255,255));
        labelController->changeFontSize(22);
        labelController->setFixedHeight(50);
        layout->addWidget(labelController);
        List* list = new List(step2);
        list->setMinimumSize(0,0);
        list->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);

        foreach(Controller* c, *this->controllers)
        {
            CellController* cell = new CellController(list);
            cell->setController(c);
            list->addCell(cell);
            cells->append(cell);
            connect(cell,SIGNAL(clicked()),this,SLOT(chooseController()));
        }
        layout->addWidget(list);
    }
    else
    {
        Label* labelNoController = new Label(tr("No controller found"),step2);
        labelNoController->changeFontSize(28);
        labelNoController->setTextColor(QColor(255,255,255));
        labelNoController->setFixedHeight(50);
        layout->addWidget(labelNoController);
    }
    this->next();
}

void StepperController::previousStep()
{
    disconnect(MainWindow::getCommunication(),SIGNAL(stopDiscover()),0,0);
    connect(MainWindow::getCommunication(),SIGNAL(stopDiscover()),this,SLOT(discoverResponse()));
    this->controllers->clear();
    this->cells->clear();
    emit requestDiscover(this->controllers);
    Stepper::previous();
}

QList<Controller*>* StepperController::getControllers()
{
    return this->controllers;
}

void StepperController::chooseController()
{
    if (this->cells->indexOf((Cell*)QObject::sender()) == -1)
    {
        return;
    }
    if (this->controllers->count() <= this->cells->indexOf((Cell*)QObject::sender()))
    {
        return;
    }
    emit controllerChosen(this->controllers->at(this->cells->indexOf((Cell*)QObject::sender())));
    this->next();
}
