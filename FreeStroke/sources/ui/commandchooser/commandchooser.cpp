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
#include "../../includes/ui/commandchooser/commandchooser.h"

#include <QtGui/QFileDialog>

CommandChooser::CommandChooser(QWidget* pParent)
{
    this->btnPathChooser = new ButtonElement(pParent);
    this->btnPathChooser->setText("Browse");
    connect(this->btnPathChooser,SIGNAL(clicked()),this,SLOT(browseFiles()));

    this->tfieldRecordName = new TextField(pParent);
    connect(this->tfieldRecordName,SIGNAL(lostFocus()),this,SLOT(recordNameContentChanged()));

    this->comboCommandType = new ComboBox(pParent);
    this->comboCommandType->setFixedWidth(90);
    this->comboCommandType->addItem(tr("Script"));
    this->comboCommandType->addItem(tr("Keyboard"));
    connect(this->comboCommandType,SIGNAL(currentIndexChanged(QString)),this,SLOT(toogleCommandField()));

    this->tfieldCommandPath = new TextField(pParent);
    connect(this->tfieldCommandPath,SIGNAL(textChanged(QString)),this,SLOT(commandFieldContentChanged()));
    this->kListenerCommandKeys = new KeyListener(pParent);
    connect(this->kListenerCommandKeys,SIGNAL(keysChanged()),this,SLOT(commandFieldContentChanged()));
    this->toogleCommandField();
}

void CommandChooser::setParent(QWidget *pParent)
{
    this->btnPathChooser->setParent(pParent);
    this->comboCommandType->setParent(pParent);
    this->tfieldCommandPath->setParent(pParent);
    this->kListenerCommandKeys->setParent(pParent);
    this->tfieldRecordName->setParent(pParent);
    QObject::setParent(pParent);
}

Command* CommandChooser::getCommand()
{
    QString name;
    CommandType type;
    if(this->comboCommandType->currentText() == tr("Script"))
    {
        name = tfieldCommandPath->text();
        type = SCRIPT;
    }
    else
    {
        name = kListenerCommandKeys->getKeys();
        type = KEYSTROKE;
    }
    return new Command(name,type);
}

void CommandChooser::setRecord(Record* pRecord)
{
    this->tfieldRecordName->setText(pRecord->getName());
    this->setCommand(pRecord->getCommand());
}

void CommandChooser::setRecordName(QString pName)
{
    this->tfieldRecordName->setText(pName);
}

QString CommandChooser::getRecordName()
{
    return this->tfieldRecordName->text();
}

TextField* CommandChooser::getRecordNameTextField()
{
    return this->tfieldRecordName;
}

void CommandChooser::setCommand(Command* pCommand)
{
    if(pCommand->getType() == SCRIPT)
    {
        this->tfieldCommandPath->setText(pCommand->getDefinition());
        this->comboCommandType->setCurrentIndex(this->comboCommandType->findText(tr("Script"),Qt::MatchExactly));
    }
    else
    {
        this->kListenerCommandKeys->setKeys(pCommand->getDefinition());
        this->comboCommandType->setCurrentIndex(this->comboCommandType->findText(tr("Keyboard"),Qt::MatchExactly));
    }
    toogleCommandField();
}

TextField* CommandChooser::getCommandTextField()
{
    return this->tfieldCommandPath;
}

KeyListener* CommandChooser::getCommandKeyListener()
{
    return this->kListenerCommandKeys;
}


ButtonElement* CommandChooser::getCommandButton()
{
    return this->btnPathChooser;
}

ComboBox* CommandChooser::getCommandComboBox()
{
    return this->comboCommandType;
}

void CommandChooser::toogleCommandField()
{
    if(this->comboCommandType->currentText() == tr("Script"))
    {
        this->tfieldCommandPath->show();
        this->kListenerCommandKeys->hide();
        this->btnPathChooser->show();
    }
    else
    {
        this->kListenerCommandKeys->show();
        this->tfieldCommandPath->hide();
        this->btnPathChooser->hide();
    }
    emit commandChanged();
}

void CommandChooser::browseFiles()
{
    QString fileName = QFileDialog::getOpenFileName(0,
                                                    tr("Choose the command"), "",
                                                    tr("All Files (*)"));
    if(this->comboCommandType->currentText() == tr("Script"))
    {
        this->tfieldCommandPath->setText(fileName);
    }

}

void CommandChooser::commandFieldContentChanged()
{
    emit commandChanged();
}

void CommandChooser::recordNameContentChanged()
{
    emit recordNameChanged();
}
