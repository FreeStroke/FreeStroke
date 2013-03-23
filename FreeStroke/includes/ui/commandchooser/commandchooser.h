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
 * \file commandchooser.h
 * \brief The CommandChooser class represents all the Element used to choose a command to associate to a record.
 * There is two TextField (one for the Command name, one for the path if the CommandType is SCRIPT), a ComboBox
 * to choose the CommandType, a ButtonElement to choose the path of the Command, a KeyListener to choose the
 * key stroke to generate for the Command.
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */
#ifndef COMMANDCHOOSER_H
#define COMMANDCHOOSER_H

#include <QtGui/QWidget>

#include "../../includes/ui/element/combobox/combobox.h"
#include "../../includes/ui/element/textfield/textfield.h"
#include "../../includes/ui/element/keylistener/keylistener.h"
#include "../../includes/ui/element/button/buttonelement.h"
#include "../../includes/daolayer/command.h"
#include "../../includes/daolayer/record.h"

/*!
 * \brief The CommandChooser class represents all the Element used to choose a command to associate to a record.
 * There is two TextField (one for the Command name, one for the path if the CommandType is SCRIPT), a ComboBox
 * to choose the CommandType, a ButtonElement to choose the path of the Command, a KeyListener to choose the
 * key stroke to generate for the Command.
 */
class CommandChooser : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Main constructor
     * \param pParent parent widget
     */
    CommandChooser(QWidget* pParent);

    /*!
     * \brief Getter for command button
     * \return the command button of the chooser
     */
    ButtonElement* getCommandButton();


    /*!
     * \brief Getter for command combobox
     * \return the command combobox of the chooser
     */
    ComboBox* getCommandComboBox();

    /*!
     * \brief Getter for command object when configured by the user
     * \return the command object
     */
    Command* getCommand();


    /*!
     * \brief Getter for command textfield
     * \return the command textfield of the chooser
     */
    TextField* getCommandTextField();


    /*!
     * \brief Getter for the choosers keylistener
     * \return the keylistener of the chooser
     */
    KeyListener* getCommandKeyListener();


    /*!
     * \brief Getter for the records name edited
     * \return the name of the record edited
     */
    QString getRecordName();

    /*!
     * \brief Getter for command textfield
     * \return the command textfield of the chooser
     */
    TextField* getRecordNameTextField();

    /*!
     * \brief Setter for the record to edit
     *  \param pRecord the record to set to edit
     */
    void setRecord(Record* pRecord);

    /*!
     * \brief Setter for the command associated to the record in edition
     * \param pCommand the command to associate
     */
    void setCommand(Command* pCommand);

    /*!
     * \brief setParent set the parent Widget of all the Element
     */
    void setParent(QWidget *);

    /*!
     * \brief Setter for the record name to edit
     *  \param pName the record name to set to edit
     */
    void setRecordName(QString pName);

private:
    ComboBox* comboCommandType; /*!< Combobox to choose command type */
    TextField* tfieldCommandPath;  /*!< Textfield to choose the command */
    KeyListener* kListenerCommandKeys;  /*!< Keylistener to capture keystroke */
    ButtonElement* btnPathChooser;  /*!< Button element to choose the path of a script */
    TextField* tfieldRecordName;   /*!< Textfield to choose the records name */

private slots:
    /*!
     * \brief Toogle command edition
     */
    void toogleCommandField();

    /*!
     * \brief Toogle command field modification
     */
    void commandFieldContentChanged();

    /*!
     * \brief  Toogle record name field modification
     */
    void recordNameContentChanged();

    /*!
     * \brief  Toogle browse button push
     */
    void browseFiles();

signals:
    /*!
     * \brief Signals when a command has been modified
     */
    void commandChanged();


    /*!
     * \brief Signals when a record name has been modified
     */
    void recordNameChanged();
};

#endif // COMMANDCHOOSER_H
