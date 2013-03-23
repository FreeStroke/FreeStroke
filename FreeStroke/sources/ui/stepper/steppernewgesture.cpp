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
#include "../../includes/ui/stepper/steppernewgesture.h"
#include "../../includes/ui/element/label/label.h"
#include "../../includes/daolayer/daolayer.h"

#include <QtCore/QDebug>
#include <QtCore/QTimer>



StepperNewGesture::StepperNewGesture(ExecutionManager *pExecutionManager, CommandChooser* pCommandChooser, int pNumberOfGesture, QWidget* parent) : Stepper(parent)
{
    this->executionManager = pExecutionManager;
    this->commandChooser = pCommandChooser;
    this->numberOfGesture = pNumberOfGesture;
    this->recordSaved = false;
    this->record = NULL;
    this->gestures = new QList<Gesture*>();
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(startTimer()));
    this->time = new QTime(0,0,1);

    disconnect(this->buttonNext, SIGNAL(clicked()), 0, 0);
    disconnect(this->buttonPrevious, SIGNAL(clicked()), 0, 0);

    connect(this->buttonNext, SIGNAL(clicked()), this, SLOT(nextStep()));
    connect(this->buttonPrevious, SIGNAL(clicked()), this, SLOT(previousStep()));

    this->stepActions = new QList<StepperNewGesture::StepAction>();
}

void StepperNewGesture::nextStep()
{
    if(this->stepLoop())
    {
        return;
    }
    if(this->currentStep <= this->stepActions->count() && !this->recordSaved)
    {
        stepDependantAction(0);
    }
    Stepper::next();
}

void StepperNewGesture::previousStep()
{
    this->timer->stop();

    if (this->stepActions->at(this->currentStep) == StepperNewGesture::ConfigureAction)
    {
        this->gestures->removeAt(this->gestures->count() - 1);
    }

    if(this->stepLoop())
    {
        return;
    }
    Stepper::previous();
    stepDependantAction(-1);
}

bool StepperNewGesture::stepLoop()
{
    this->buttonPrevious->setText(tr("Previous"));
    if(this->currentStep > 0 &&
            this->stepActions->at(this->currentStep) == StepperNewGesture::ConfigureAction &&
            this->gestures->count() < this->numberOfGesture)
    {
        this->steps->at(this->currentStep)->widget->hide();
        this->currentStep = this->stepActions->indexOf(StepperNewGesture::StartTimer);
        Label* label =  dynamic_cast<Label*>(this->steps->at(this->currentStep)->widget);
        if(label != NULL)
        {
            label->setText(tr("You will have 5 seconds to place yourself\nbefore registering your gesture\n")
                           + QString::number(this->gestures->count() + 1)
                           + "/" + QString::number(this->numberOfGesture));
        }
        Stepper::organize();
        return true;
    }
    return false;
}

void StepperNewGesture::stepDependantAction(int offset)
{
    if ((this->currentStep + offset) < 0)
    {
        return;
    }
    switch(this->stepActions->at(this->currentStep + offset))
    {
    case StepperNewGesture::First :
        qDebug() << "First";
        break;
    case StepperNewGesture::StartTimer :
    {
        qDebug() << "StartTimer";
        timer->start(1000);
        time->setHMS(0,0,6);
        disconnect(this->executionManager, SIGNAL(gestureRecorded(Gesture*)), this, SLOT(endOfRecord(Gesture*)));
        disconnect(this->executionManager, SIGNAL(gestureConflict(Gesture*)), 0, 0);

        connect(this->executionManager, SIGNAL(gestureRecorded(Gesture*)), this, SLOT(endOfRecord(Gesture*)));
        connect(this->executionManager, SIGNAL(gestureConflict(Gesture*)), this, SLOT(conflictWhileRecording(Gesture*)));
        break;
    }
    case StepperNewGesture::StartRecording :
        this->executionManager->startRecorder();
        qDebug() << "StartRecording";
        break;
    case StepperNewGesture::VisualizeRecording :
        qDebug() << "VisualizeRecording";
        this->buttonPrevious->setText(tr("Refuse"));
        break;
    case StepperNewGesture::ConfigureAction :
        qDebug() << "ConfigureAction";
        break;
    case StepperNewGesture::SaveRecord :
    {
        qDebug() << "SaveRecord start";
        this->command = this->commandChooser->getCommand();
        this->recordName = this->commandChooser->getRecordName();
        connect(this->executionManager, SIGNAL(trainingEnded()), this, SLOT(trainingEnded()));
        DAOLayer::getInstance()->addRecord(new Record(this->recordName, this->gestures, this->command)); // Start the training
        qDebug() << "SaveRecord end";
        break;
    }
    case StepperNewGesture::Close :
        qDebug() << "Close";
        disconnect(this->executionManager, SIGNAL(trainingEnded()), 0, 0);
        disconnect(this->executionManager, SIGNAL(gestureRecorded(Gesture*)), 0, 0);
        disconnect(this->executionManager, SIGNAL(gestureConflict(Gesture*)), 0, 0);
        break;
    }
}

void StepperNewGesture::startTimer()
{
    this->time->setHMS(0,0,this->time->addMSecs(-1).second());
    Label* label =  dynamic_cast<Label*>(this->steps->at(this->currentStep)->widget);
    if(this->time->second() == 0)
    {
        this->nextStep();
        this->timer->stop();
        this->executionManager->startRecorder();
        if(label != NULL)
        {
            label->setText(tr("Ready ?"));
        }
        return;
    }
    if(label != NULL)
    {
        label->setText(QString::number(time->second()));
    }
}


void StepperNewGesture::addStep(QString pTitle, bool pNextVisible, bool pPreviousVisible, bool pCancelVisible, StepperNewGesture::StepAction pAction, QWidget* pWidget)
{
    this->stepActions->append(pAction);
    pWidget->setFixedSize(600,400);
    Stepper::addStep(pTitle, pNextVisible, pPreviousVisible, pCancelVisible, pWidget);
}

void StepperNewGesture::trainingEnded()
{
    this->recordSaved =true;
    this->nextStep();
}


void StepperNewGesture::endOfRecord(Gesture* pGesture)
{
    this->executionManager->standby();
    this->gestures->append(pGesture);
    this->nextStep();
}
void StepperNewGesture::conflictWhileRecording(Gesture* pGesture)
{
    qDebug()<<"In conflict management";

    this->executionManager->standby();
    this->previousStep();
    this->previousStep();

    Label* label =  dynamic_cast<Label*>(this->steps->at(this->currentStep)->widget);
    if(label != NULL)
    {
        label->setText(tr("This Gesture is too close to another one\n\nYou will have 5 seconds to place yourself\nbefore registering your gesture\n")
                       + QString::number(this->gestures->count() + 1)
                       + "/" + QString::number(this->numberOfGesture));
    }
}
