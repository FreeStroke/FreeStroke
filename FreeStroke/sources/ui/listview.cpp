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
#include "../../includes/ui/listview.h"
#include "../../includes/common/utils.h"

#include "../../includes/mainwindow.h"
#include "../../includes/ui/element/combobox/combobox.h"
#include "../../includes/ui/cell/cell.h"
#include "../../includes/ui/element/button/buttonelement.h"
#include "../../includes/ui/element/label/label.h"
#include "../../includes/ui/glview/glview.h"
#include "../../includes/ui/scrollbar/scrollbar.h"
#include "../../includes/ui/stepper/stepsnewgesture.h"
#include "../../includes/ui/maincontainer/maincontainer.h"
#include "../../includes/ui/dialog/dialog.h"
#include "../../includes/ui/commandchooser/commandchooser.h"

#include "../../includes/xml/xml.h"

#include "../../includes/others/mac/mac.h"

ListView::ListView(QWidget *parent) : QWidget(parent)
{
    this->gestureListView = new GestureListView(this);
    this->rightLabel = new Label("",this);
    this->rightLabel->changeFontSize(23);
    this->labels = new QWidget(this);

    this->dao = DAOLayer::getInstance();
    if(dao == NULL)
    {
        qDebug() << "DAO IS NULL";
        return;
    }
    connect(this->dao, SIGNAL(recordAdded(Record*)), this, SLOT(refreshListViewContent()));
    this->glView = new GlView(this);
    this->refreshListViewContent(false);

    this->params = new GestureParams(this);
    this->switcherGesture = new Switcher(this);
    this->switcherAction = new Switcher(this);
    this->btnAdd = new ButtonElement(this);
    this->btnTrash = new ButtonElement(this);
    this->createView();
}

void ListView::createView()
{
    //Left
    QWidget *leftBarWidget = new QWidget(this);
    QVBoxLayout *leftBarLayout = new QVBoxLayout(leftBarWidget);
    leftBarLayout->setSpacing(0);
    leftBarLayout->setMargin(0);

    //list
    MainContainer* leftContainer = new MainContainer(leftBarWidget);
    labels->setParent(leftContainer);
    QVBoxLayout* vLabelsLayout = new QVBoxLayout(labels);
    vLabelsLayout->setContentsMargins(13,0,13,0);

    Label* labelNoRecord = new Label(tr("Add a gesture"), labels);
    labelNoRecord->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    Label* imgNoRecord = new Label("",labels);
    imgNoRecord->setPixmap(QPixmap(Utils::getResourcesDirectory()+"arrow-bottom.png"));
    imgNoRecord->setFixedSize(22,22);
    labelNoRecord->changeFontSize(15);

    vLabelsLayout->addWidget(labelNoRecord);
    vLabelsLayout->addWidget(imgNoRecord);
    leftContainer->addWidget(labels);
    leftContainer->addWidget(this->gestureListView);

    this->gestureListView->setFocus();
    this->gestureListView->setParent(leftContainer);
    leftBarWidget->setFixedWidth(this->gestureListView->width());
    connect(this->gestureListView, SIGNAL(selectionChanged()), this, SLOT(refreshSelection()));

    // Bottom Bar
    BottomBar *bottomBar = new BottomBar(leftBarWidget);
    bottomBar->setFixedWidth(this->gestureListView ->width());
    bottomBar->addRightLine(true);

    this->btnAdd->setIcon(QPixmap(Utils::getResourcesDirectory()+"icon-add.png"));
    connect(this->btnAdd, SIGNAL(clicked()), this, SLOT(addGesture()));
    bottomBar->addElement(this->btnAdd);

    this->btnTrash->setIcon(QPixmap(Utils::getResourcesDirectory()+"icon-trash.png"));
    connect(this->btnTrash, SIGNAL(clicked()), this, SLOT(deleteGestures()));
    bottomBar->addElement(this->btnTrash);

    bottomBar->addSeparator();

    this->btnExport = new ButtonElement(bottomBar);
    this->btnExport->setIcon(QPixmap(Utils::getResourcesDirectory()+"icon-export.png"));
    this->btnExport->setEnabled(false);
    connect(this->btnExport, SIGNAL(clicked()), this, SLOT(toogleExport()));
    bottomBar->addElement(this->btnExport);


    this->btnImport = new ButtonElement(bottomBar);
    this->btnImport->setIcon(QPixmap(Utils::getResourcesDirectory()+"icon-import.png"));
    this->btnImport->setEnabled(true);
    connect(this->btnImport, SIGNAL(clicked()), this, SLOT(toogleImport()));
    bottomBar->addElement(this->btnImport);

    leftBarLayout->addWidget(leftContainer);
    leftBarLayout->addWidget(bottomBar);

    // Right

    QWidget *rightBarWidget = new QWidget(this);
    QVBoxLayout *rightBarLayout = new QVBoxLayout(rightBarWidget);
    rightBarLayout->setSpacing(0);
    rightBarLayout->setMargin(0);

    //top bar
    params->setFixedHeight(35);

    btnPause = new ButtonElement(this);
    btnPause->setIcon(QPixmap(Utils::getResourcesDirectory()+"icon-pause.png"));
    btnPause->setText(tr("Pause"));
    connect(btnPause, SIGNAL(clicked()), this, SLOT(toggleGestureAnimation()));
    params->addElement(btnPause);

    params->addSpacer();

    Label *labelGeste = new Label(" " + tr("Active gesture") + "  ", params);
    params->addElement(labelGeste);
    params->addElement(switcherGesture);
    connect(switcherGesture, SIGNAL(toggle(bool)), this, SLOT(toogleGestureState(bool)));

    Label *labelAction = new Label("    " + tr("Active action") + "  ", params);
    params->addElement(labelAction);
    params->addElement(switcherAction);
    connect(switcherAction, SIGNAL(toggle(bool)), this, SLOT(toogleActionState(bool)));

    //right Container
    MainContainer* container = new MainContainer(this);
    this->glView->setParent(container);
    this->glView->show();
    this->rightLabel->setParent(container);
    this->rightLabel->hide();
    container->addWidget(this->glView);
    container->addWidget(this->rightLabel);

    //GL View
    this->glView->setMinimumSize(100, 100);
    this->glView->startAnimating();

    //Bottom Bar
    this->bottomRightBar = new BottomBar(rightBarWidget);
    this->bottomRightBar->setMinimumWidth(300);
    this->bottomRightBar->addLeftLine(false);

    this->commandChooser = new CommandChooser(this->bottomRightBar);
    connect(this->commandChooser,SIGNAL(commandChanged()),this,SLOT(updateCommand()));
    connect(this->commandChooser,SIGNAL(recordNameChanged()),this,SLOT(updateRecordName()));
    ComboBox *combo = this->commandChooser->getCommandComboBox();

    this->bottomRightBar->addElement(combo);
    this->bottomRightBar->addSeparator();

    this->bottomRightBar->addElement(this->commandChooser->getCommandKeyListener());

    this->bottomRightBar->addElement(this->commandChooser->getCommandTextField());

    this->bottomRightBar->addElement(this->commandChooser->getCommandButton());

    this->bottomRightBar->addSeparator();
    Label* labelRecordName = new Label(tr("Commande name :"),this->bottomRightBar);
    QFontMetrics fm(labelRecordName->font());
    labelRecordName->setFixedWidth(fm.width(labelRecordName->text()));
    this->bottomRightBar->addElement(labelRecordName);
    this->bottomRightBar->addElement(this->commandChooser->getRecordNameTextField());

    rightBarLayout->addWidget(this->params);
    rightBarLayout->addWidget(container);
    rightBarLayout->addWidget(this->bottomRightBar);

    // Layout
    QHBoxLayout *layoutListView = new QHBoxLayout(this);
    layoutListView->addWidget(leftBarWidget);
    layoutListView->addWidget(rightBarWidget);
    layoutListView->setSpacing(0);
    layoutListView->setMargin(0);
    this->refreshSelection();
}

GestureListView* ListView::getGestureListView()
{
    return this->gestureListView;
}

void ListView::toggleGestureAnimation()
{
    if (this->glView->isAnimating())
    {
        this->glView->pauseAnimating();
        this->btnPause->setIcon(QPixmap(Utils::getResourcesDirectory()+"icon-play.png"));
        this->btnPause->setText(tr("Play"));
    }
    else
    {
        this->glView->startAnimating();
        this->btnPause->setIcon(QPixmap(Utils::getResourcesDirectory()+"icon-pause.png"));
        this->btnPause->setText(tr("Pause"));
    }
}

void ListView::refreshSelection()
{
    if(this->gestureListView->count()>0)
    {
        this->labels->hide();
    }
    else
    {
        this->labels->show();
    }

    if (this->gestureListView->getSelectedCells()->length() == 1)
    {
        this->commandChooser->setRecord(this->gestureListView->getSelectedCells()->at(0)->getRecord());
        this->gestureListView->getSelectedCells()->at(0)->setText(this->commandChooser->getRecordName());
        this->bottomRightBar->show();
        this->btnTrash->setEnabled(true);
        this->rightLabel->setText("");
        this->rightLabel->hide();
        this->glView->show();
        this->glView->setGesture(this->gestureListView->getSelectedCells()->at(0)->getGesture());

        this->params->show();

        this->switcherAction->setState(this->gestureListView->getSelectedCells()->at(0)->getRecord()->isCommandActive());
        this->switcherGesture->setState(this->gestureListView->getSelectedCells()->at(0)->getRecord()->isGestureActive());

        this->btnExport->setEnabled(true);
    }
    else if (this->gestureListView->getSelectedCells()->length() >= 1)
    {
        this->bottomRightBar->hide();
        this->btnTrash->setEnabled(true);
        this->params->hide();
        this->glView->hide();
        this->rightLabel->show();
        this->rightLabel->setText(QString::number(this->gestureListView->getSelectedCells()->count()) + tr(" selected gestures"));

        this->btnExport->setEnabled(true);
    }
    else
    {
        this->bottomRightBar->hide();
        this->btnTrash->setEnabled(false);
        this->params->hide();
        this->glView->hide();
        this->rightLabel->show();
        this->rightLabel->setText(tr("No gesture to display"));

        this->btnExport->setEnabled(false);
    }
}

void ListView::addGesture()
{
    StepsNewGesture* stepper = new StepsNewGesture(MainWindow::getExecutionManager(), 2, this);
    MainWindow::getExecutionManager()->standby();
    stepper->show();
    delete stepper;
    stepper = NULL;
}

void ListView::deleteGestures()
{
    if (this->gestureListView->getSelectedCells()->count() == 0)
    {
        return;
    }
    Dialog *d = new Dialog("", this);
    d->addButton(tr("No"), Dialog::Reject, DialogButton::Dark);
    d->addButton(tr("Yes"), Dialog::Accept, DialogButton::Normal, true);
    Dialog::DialogCode dc;
    if (this->gestureListView->getSelectedCells()->count()>1)
    {
        dc = d->displayNotification(Dialog::Information, tr("Do you really want to delete those items ?"), tr("This operation cannot be undone."));

    }
    else
    {
        dc = d->displayNotification(Dialog::Information, tr("Do you really want to delete this item ?"), tr("This operation cannot be undone."));

    }
    if (dc == Dialog::Accepted)
    {
        foreach(Cell* c, *this->gestureListView->getSelectedCells())
        {
            this->gestureListView->removeCell(c);
            if(this->dao->removeRecord(c->getRecord()) != 0)
            {
                qDebug() << "error while removing from DAO";
            }
        }
        if (this->gestureListView->count()==0)
        {
            this->gestureListView->clearListSelection();
        }
        else
        {
            this->gestureListView->selectCell(this->gestureListView->getCells()->at(0));
        }
        ExecutionManager *em = MainWindow::getExecutionManager();
        em->startTraining();
    }
}

void ListView::toogleActionState(bool state)
{
    if(this->gestureListView->getSelectedCells()->count() == 0)
    {
        return;
    }
    foreach (Cell* cell, *this->gestureListView->getSelectedCells())
    {
        Record* record = cell->getRecord();
        record->setCommandActive(state);
        this->dao->updateRecord(record);
    }
}

void ListView::updateCommand()
{
    this->gestureListView->getSelectedCells()->at(0)->getRecord()->setCommand((this->commandChooser->getCommand()));
    this->dao->updateRecord(this->gestureListView->getSelectedCells()->at(0)->getRecord());
}

void ListView::updateRecordName()
{
    this->gestureListView->getSelectedCells()->at(0)->getRecord()->setName(this->commandChooser->getRecordName());
    this->dao->updateRecord(this->gestureListView->getSelectedCells()->at(0)->getRecord());
    refreshSelection();
}

void ListView::toogleGestureState(bool state)
{
    if(this->gestureListView->getSelectedCells()->count() == 0)
    {
        return;
    }
    foreach (Cell* cell, *this->gestureListView->getSelectedCells())
    {
        Record* record = cell->getRecord();
        record->setGestureActive(state);
        this->dao->updateRecord(record);
    }
}

void ListView::toogleImport()
{
    disconnect(this->dao, SIGNAL(recordAdded(Record*)), 0, 0);
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Import Gestures"), "",
                                                    tr("FreeStroke XML File (*.xml);;All Files (*)"));
    if (fileName.isEmpty())
    {
        // TODO : Manage error
        return;
    }

    int recordAdded = 0;
    Xml *xml = new Xml();
    QList<Record*> *records = xml->importRecord(fileName);
    if(records == NULL)
    {
        // TODO : Manage error
        return;
    }
    QString title(tr("Import of "));
    title.append(records->count());
    title.append(tr(" gesture(s)"));
    Dialog *d = new Dialog(title, this);
    d->addButton(tr("Import all"), Dialog::Reject, DialogButton::Dark);
    d->addButton(tr("Choose"), Dialog::Accept, DialogButton::Normal, true);
    Dialog::DialogCode dc = d->displayNotification(Dialog::Information, tr("Do you want to import all gestures ?"), tr("Or choose wich gesture to import"));
    Stepper *s;
    QWidget * container;
    QWidget * bottomWidget;

    for(int i = 0; i < records->count(); i++)
    {
        Record *r = records->at(i);
        int res;
        if(dc == Dialog::Accepted)
        {
            s = new Stepper(this);
            s->setAttribute(Qt::WA_DeleteOnClose,false);
            container = new QWidget(s);
            container->setFixedSize(600,400);
            bottomWidget = new QWidget(container);
            bottomWidget->setFixedHeight(50);
            QHBoxLayout* hLayout = new QHBoxLayout(bottomWidget);


            CommandChooser *commandChooser2 = new CommandChooser(bottomWidget);
            commandChooser2->setParent(bottomWidget);
            commandChooser2->setRecord(r);

            ComboBox *combo  = commandChooser2->getCommandComboBox();
            KeyListener *keyListener = commandChooser2->getCommandKeyListener();
            TextField *textField = commandChooser2->getCommandTextField();
            ButtonElement *btnCommand = commandChooser2->getCommandButton();
            Label* labelRecordName = new Label("Record name : ",s);
            labelRecordName->setTextColor(QColor(210,210,210));
            TextField *tfRecordName = commandChooser2->getRecordNameTextField();


            hLayout->addWidget(combo);
            hLayout->addWidget(keyListener);
            hLayout->addWidget(textField);
            hLayout->addWidget(btnCommand);
            hLayout->addWidget(labelRecordName);
            hLayout->addWidget(tfRecordName);

            QVBoxLayout* vLayout = new QVBoxLayout(container);
            Label *label = new Label(tr("Is it the right gesture ?"),s);
            label->setFixedHeight(50);
            label->changeFontSize(23);
            label->setTextColor(QColor(210,210,210));
            GlView *gl = new GlView(container);
            gl->setGesture(r->getGestures()->at(0));
            gl->startAnimating();

            vLayout->addWidget(label);
            vLayout->addWidget(gl);
            vLayout->addWidget(bottomWidget);
            title.clear();
            title.append(tr("Import gesture "));
            title.append(QString::number(i+1));
            title.append("/");
            title.append(QString::number(records->count()));
            s->addStep(title,true, false,true,container);
            s->setButtonCancelName(tr("No"));
            s->setButtonNextName(tr("Yes"));
            res = s->exec();
            r->setCommand(commandChooser2->getCommand() );
            r->setName(commandChooser2->getRecordName());
            delete s;
        }
        else
        {
            res = Dialog::Accepted;
        }
        qDebug() << "res = " << res;
        if(res == Dialog::Accepted)
        {
            qDebug() << "accepted";
            if(this->dao->addRecord(r) != 0)
            {
                qDebug() << "Problem importing record in DAOLayer";
                // TODO : Manage error
                return;
            }
            recordAdded++;
        }
    }

    if(recordAdded > 0)
    {
        Dialog *d = new Dialog("", this);
        d->addButton(tr("OK"), Dialog::Accept, DialogButton::Normal, true);
        d->displayNotification(Dialog::Information, tr("Success"), tr("Records have been successfully imported."));
        this->refreshListViewContent();
    }
    connect(this->dao, SIGNAL(recordAdded(Record*)), this, SLOT(refreshListViewContent()));
}


void ListView::toogleExport()
{
    // open file dialog to get filename
    if(this->gestureListView->getSelectedCells()->count() == 0)
    {
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export Gestures"), "",
                                                    tr("FreeStroke XML File (*.xml);;All Files (*)"));
    if (fileName.isEmpty())
    {
        return;
    }

    // get selected records
    QList<Record*> *records = new QList<Record*>();
    for(int i = 0; i < this->gestureListView->getSelectedCells()->count(); i++)
    {
        records->append(this->gestureListView->getSelectedCells()->at(i)->getRecord());
    }

    // update dao records
    Xml *xml = new Xml();
    if(xml->exportRecords(records, fileName) == 0)
    {
        Dialog *d = new Dialog("", this);
        d->addButton(tr("OK"), Dialog::Accept, DialogButton::Normal, true);
        d->displayNotification(Dialog::Information, tr("Success"), tr("Records have been successfully exported."));
    }
    else
    {
        qDebug() << "Problem during export";
    }
    this->refreshSelection();
}

void ListView::refreshListViewContent(bool pTrain)
{
    bool selectFlag;
    if(this->gestureListView->getSelectedCells()->count() == 0)
    {
        selectFlag = false;
    }
    else
    {
        selectFlag = true;
    }
    QList<Record*>* records = this->dao->getRecords();

    bool needTrain=false;
    if (records != NULL)
    {
        foreach (Record* record, *records)
        {
            if(!record->isDeleted() && !this->gestureListView->containsRecord(record))
            {
                Cell* cell = new Cell(record, this->gestureListView);
                this->gestureListView->addCell(cell);
                if(!selectFlag)
                {
                    cell->setSelected(true);
                    selectFlag = true;
                }
                needTrain=true;
            }
        }
    }

    if (needTrain && pTrain)
    {
        ExecutionManager *em = MainWindow::getExecutionManager();
        em->startTraining();
    }
}
