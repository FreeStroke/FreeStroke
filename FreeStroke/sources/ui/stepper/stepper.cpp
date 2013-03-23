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
#include "../../includes/ui/stepper/stepper.h"
#include <QtGui/QDesktopWidget>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QDebug>

Step::Step(QString pTitle, bool pNextVisible, bool pPreviousVisible, bool pCancelVisible, QWidget *pWidget)
{
    this->showNext = pNextVisible;
    this->showPrevious = pPreviousVisible;
    this->showCancel = pCancelVisible;
    this->title = pTitle;
    this->widget = pWidget;
}

void Step::nextVisible(bool pShowNext)
{
    this->showNext = pShowNext;
}

void Step::closeVisible(bool pShowCancel)
{
    this->showCancel = pShowCancel;
}

void Step::previousVisible(bool pShowPrevious)
{
    this->showPrevious = pShowPrevious;
}

Stepper::Stepper(QWidget *parent) : Dialog("", parent)
{
    this->steps = new QList<Step*>();
    this->currentStep = 0;

    this->addButton(tr("Next"), Stepper::Next, DialogButton::Normal, true);
    this->addButton(tr("Previous"), Stepper::Previous, DialogButton::Dark, false);
    this->addButton(tr("Cancel"), Stepper::Cancel, DialogButton::Bright, false);
    this->setFocus();
}

QList<Step*> *Stepper::getSteps()
{
    return this->steps;
}

Step *Stepper::getCurrentStep()
{
    return this->steps->at(currentStep);
}

void Stepper::addButton(QString pLabelText, Stepper::Role pRole, DialogButton::Type pType, bool pDefault)
{
    DialogButton* b = new DialogButton(pLabelText, pType, this);

    if (pRole == Stepper::Next)
    {
        buttonNext = b;
        connect(b, SIGNAL(clicked()), this, SLOT(next()));
    }
    else if (pRole == Stepper::Previous)
    {
        buttonPrevious = b;
        connect(b, SIGNAL(clicked()), this, SLOT(previous()));
    }
    else if (pRole == Stepper::Cancel)
    {
        buttonCancel = b;
        connect(b, SIGNAL(clicked()), this, SLOT(cancel()));
    }

    this->setFocus();
    b->setDefault(pDefault);
}


void Stepper::addStep(QString pTitle, bool pNextVisible, bool pPreviousVisible, bool pCancelVisible, QWidget* pWidget)
{
    pWidget->hide();
    pWidget->setParent(this);
    //resize the widget if bigger than the maximum size
    pWidget->setFixedSize(pWidget->width()>this->maximumWidth()?this->maximumWidth():pWidget->width(),
                    pWidget->height()>this->maximumHeight() - 93 ?this->maximumHeight()-93:pWidget->height());

    this->steps->append(new Step(pTitle, pNextVisible, pPreviousVisible, pCancelVisible, pWidget));
    this->organize();
}

void Stepper::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape && !this->steps->at(this->currentStep)->showCancel)
    {
        return;
    }
    if(!this->steps->at(this->currentStep)->showNext && !(e->key() ==Qt::Key_Escape))
    {
        return;
    }
    Dialog::keyPressEvent(e);
}

void Stepper::organize()
{
    //Show the current widget
    this->steps->at(this->currentStep)->widget->show();
    QSize size = this->steps->at(this->currentStep)->widget->size();

    //Resize the stepper
    size.setWidth(size.width()>this->minimumWidth()?size.width():this->minimumWidth());
    size.setHeight(size.height() + this->minimumHeight() - 52);
    this->resize(size);

    //move the stepper to the center of the screen
    QRect r = this->frameGeometry();
    QDesktopWidget d;
    r.moveCenter(d.availableGeometry().center());
    this->move(r.topLeft());

    //Move the widget to the center of the stepper
    this->steps->at(this->currentStep)->widget->setGeometry(
                (this->width()-this->steps->at(this->currentStep)->widget->width())/2,
                41,
                this->steps->at(this->currentStep)->widget->width(),
                this->steps->at(this->currentStep)->widget->height());

    //Show / Hide buttons
    if(this->steps->at(currentStep)->showCancel)
    {
        this->buttonCancel->show();
        this->buttonClose->show();
    }
    else
    {
        this->buttonCancel->hide();
        this->buttonClose->hide();
    }

    if(this->steps->at(currentStep)->showNext)
    {
        this->buttonNext->show();
    }
    else
    {
        this->buttonNext->hide();
    }

    if(this->steps->at(currentStep)->showPrevious)
    {
        this->buttonPrevious->show();
    }
    else
    {
        this->buttonPrevious->hide();
    }
    this->setTitle((this->steps->at(this->currentStep))->title);

    if(this->currentStep == this->steps->length()-1)
    {
        this->buttonNext->setText(tr("Finish"));
    }
    else
    {
        this->buttonNext->setText(tr("Next"));
    }

    //Set the buttons at the right places
    int rightOffset = 10;
    int leftOffset = 10;
    int margin = 10;
    this->buttonCancel->move(leftOffset, this->height() - 24 - (this->buttonCancel->height() / 2));

    if(this->steps->at(this->currentStep)->showNext || this->buttonPrevious->text().compare(tr("Previous")) == 0)
    {
        this->buttonNext->move(this->width() - rightOffset - this->buttonNext->width(), this->height() - 24 - (this->buttonNext->height() / 2));
        rightOffset += this->buttonNext->width() + margin;
    }
    else
    {
        rightOffset += margin*2;
    }

    this->buttonPrevious->move(this->width() - rightOffset - this->buttonPrevious->width(), this->height() - 24 - (this->buttonPrevious->height() / 2));
    this->setFocus();
}

void Stepper::next()
{
    //hide the current widget
    this->steps->at(this->currentStep)->widget->hide();
    this->currentStep++;
    if(this->currentStep == this->steps->count())
    {
        this->accept();
        return;
    }
    this->organize();
}

void Stepper::previous()
{
    //cannot go to inexistant step ! previousButton shouldn't be available at step 0 anyway ...
    if (this->currentStep == 0)
    {
        return;
    }

    //hide the current widget
    this->steps->at(this->currentStep)->widget->hide();

    this->currentStep--;
    this->organize();
}

void Stepper::cancel()
{
    this->reject();
}


void Stepper::setButtonPreviousName(QString name)
{
    this->buttonPrevious->setText(name);
}

void Stepper::setButtonNextName(QString name)
{
    this->buttonNext->setText(name);
}

void Stepper::setButtonCancelName(QString name)
{
    this->buttonCancel->setText(name);
}

