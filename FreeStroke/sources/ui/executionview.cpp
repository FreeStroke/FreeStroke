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
#include "../../includes/ui/executionview.h"
#include "../../includes/ui/bottombar/bottombar.h"
#include "../../includes/common/utils.h"
#include "../../includes/ui/element/combobox/combobox.h"
#include "../../includes/ui/element/keylistener/keylistener.h"
#include "../../includes/ui/gestureparams/gestureparams.h"

#include "../../includes/ui/cell/cell.h"
#include "../../includes/ui/dialog/dialog.h"
#include "../../includes/ui/element/switcher/switcher.h"
#include "../../includes/ui/element/textfield/textfield.h"
#include "../../includes/ui/glview/glview.h"
#include "../../includes/ui/scrollbar/scrollbar.h"
#include "../../includes/ui/stepper/stepper.h"
#include "../../includes/ui/maincontainer/maincontainer.h"

#include "../../includes/ui/dialog/dialog.h"

ExecutionView::ExecutionView(QWidget *parent) : QWidget(parent)
{
    this->gestureListView = new GestureListView(this);
    this->dao = DAOLayer::getInstance();
    this->labelNoHistory = new Label(tr("No history to display"), this);
    this->btnTrash = new ButtonElement(this);


    if(this->dao == NULL)
    {
        qDebug() << "dao is NULL :'(";
        return;
    }

    QList<HistoryRecord*>* historyRecords = this->dao->getHistoryRecords();

    if(historyRecords != NULL)
    {
        foreach(HistoryRecord* hr, *historyRecords)
        {
            Cell* c = new Cell(hr, this->gestureListView);
            c->getGlView()->setGesture(hr->getRecordExecuted()->getGestures()->at(0));
            this->gestureListView->addCell(c);
        }
    }
    this->glView = new GlView(this);
    this->glView->pauseRotation();
    connect(this->dao,SIGNAL(skeletonDataReceived(QString)), this, SLOT(skeletonDataRecieved(QString)));
    connect(this->dao,SIGNAL(historyRecordAdded(HistoryRecord*)),this, SLOT(historyRecordAdded(HistoryRecord*)));
    connect(this->dao,SIGNAL(historyRecordDeleted()),this, SLOT(historyRecordDeleted()));
    this->createView();
    this->historyChanged();
}

GlView* ExecutionView::getGlView()
{
    return this->glView;
}

void ExecutionView::createView()
{
    // West
    // Top Bar
    QWidget *leftBarWidget = new QWidget(this);
    QVBoxLayout *topBarLayout = new QVBoxLayout(leftBarWidget);

    topBarLayout->setSpacing(0);
    topBarLayout->setMargin(0);

    BottomBar *topBar = new BottomBar(leftBarWidget);
    topBar->setTopBar(true);
    topBar->setFixedWidth(170);
    topBar->addRightLine(true);

    Label* labelHistory = new Label(tr("History"), topBar);
    QFont f = labelHistory->font();
    f.setPixelSize(18);
    labelHistory->setFont(f);
    topBar->addElement(labelHistory);

    this->btnTrash->setParent(topBar);
    btnTrash->setIcon(QPixmap(Utils::getResourcesDirectory()+"icon-trash.png"));
    topBar->addElement(btnTrash);

    connect(btnTrash, SIGNAL(clicked()), this, SLOT(deleteHistoryRecord()));

    topBar->addRightLine(true);

    topBarLayout->addWidget(topBar);

    // Gesture View
    leftBarWidget->setFixedWidth(this->gestureListView->width());
    this->gestureListView->show();
    this->gestureListView->setFocus();

    MainContainer* container = new MainContainer(this);
    this->gestureListView->setParent(container);
    this->labelNoHistory->setParent(container);
    labelNoHistory->hide();
    container->addWidget(this->gestureListView);
    container->addWidget(labelNoHistory);

    topBarLayout->addWidget(container);

    // Center
    this->glView->startAnimating();

    // Layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(leftBarWidget);
    layout->addWidget(this->glView);
    layout->setSpacing(0);
    layout->setMargin(0);
}

void ExecutionView::skeletonDataRecieved(QString pData)
{
    this->glView->nextSkeleton(SkeletonData::fromLine(pData));
}

void ExecutionView::historyRecordAdded(HistoryRecord * historyRecord)
{
    Cell* c = new Cell(historyRecord, this->gestureListView);
    c->getGlView()->setGesture(historyRecord->getRecordExecuted()->getGestures()->at(0));
    this->gestureListView->insertCellAtHead(c);
    this->historyChanged();
}

void ExecutionView::historyRecordDeleted()
{
    this->gestureListView->removeAllCells();
    this->historyChanged();
}

void ExecutionView::deleteHistoryRecord()
{
    Dialog *d = new Dialog("", this);
    d->addButton(tr("No"), Dialog::Reject, DialogButton::Dark);
    d->addButton(tr("Yes"), Dialog::Accept, DialogButton::Normal, true);
    Dialog::DialogCode dc = d->displayNotification(Dialog::Information, tr("Do you really want to permanently delete all history items?"), tr("This operation cannot be undone"));
    if (dc == Dialog::Accepted)
    {
        if(this->dao != NULL)
        {
            this->dao->removeHistoryRecord();
        }
    }
}

void ExecutionView::historyChanged()
{
    if(this->gestureListView->count() == 0)
    {
        this->labelNoHistory->show();
        this->btnTrash->setEnabled(false);
    }
    else
    {
        this->labelNoHistory->hide();
        this->btnTrash->setEnabled(true);
    }
}
