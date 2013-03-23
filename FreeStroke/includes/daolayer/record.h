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
 * \file record.h
 * \author Guillaume Demurger
 * \brief Represents a record object composed by a gesture and a command
 * \date 2013-02-14
 */
#ifndef RECORD_H
#define RECORD_H

#include "../common/gesture.h"
#include "command.h"

#include <QtCore/QString>

/*!
 * \brief Represents a record object composed by a gesture and a command
 */
class Record {
public:
    /*!
     * \brief Main constructor of a record
     */
    Record(QString, QList<Gesture *> *, Command *);

    /*!
     * \brief Extended constructor setting all record attributes
     */
    Record(int, QString, QString, QList<Gesture *> *, Command *,bool ,bool ,bool);

    /*!
     * \brief Getter for record Id
     * \return the records id
     */
    int getId();


    /*!
     * \brief Getter for record Name
     * \return the records name
     */
    QString getName();


    /*!
     * \brief Getter for record's creation date
     * \return the records creation date
     */
    QString getCreationDate();


    /*!
     * \brief Getter for gestures associated to the record
     * \return a list of gestures associated to the record, one or more instance of a gesture
     */
    QList<Gesture *> * getGestures();

    /*!
     * \brief Getter for the command associated to the record
     * \return a command object that will be exectuted when the gesture is recognized
     */
    Command *getCommand();

    /*!
     * \brief Tests if the command object is active (so will be executed)
     * \return true if the command is active
     */
    bool isCommandActive();


    /*!
     * \brief Tests if the gesture active (so will be recognized)
     * \return true if the gesture is active
     */
    bool isGestureActive();


    /*!
     * \brief Tests if the record has been deleted (setted to true if history records are associated after deletion)
     * \return true if the command is deleted (will be removed from database if no history records are associated)
     */
    bool isDeleted();


    /*!
     * \brief Setter for Id attribute of a record
     */
    void setId(int);


    /*!
     * \brief Setter for Name attribute of a record
     * \param pName the name to associate with the record
     */
    void setName(QString pName);


    /*!
     * \brief Setter for Creation Date attribute of a record
     * \param pCreationDate the date of creation of the record
     */
    void setCreationDate(QString pCreationDate);

    /*!
     * \brief Setter for gestures associated with a record
     * \param the list of gestures to associate (will replace previous associated gestures)
     */
    void setGestures(QList<Gesture *> *);

    /*!
     * \brief Setter for command attribute of a record (will replace previous associated command)
     */
    void setCommand(Command *);

    /*!
     * \brief Activates / Deactivates command execution of the record
     */
    void setCommandActive(bool);


    /*!
     * \brief Activates / Deactivates gesture recognize of the record
     */
    void setGestureActive(bool);


    /*!
     * \brief Activates / Deactivates future deletion of the record
     */
    void setDeleted(bool);

private:
    int id; /*!< id of the record in database */
    QString name; /*!< name of the record */
    QString creationDate; /*!< date of recording */
    QList<Gesture *> * gestures; /*!< list of gestures used to train the recognize model */
    Command *myCommand; /*!< command that will be executed if the command is active */
    bool commandActive; /*!< command activation */
    bool gestureActive; /*!< gesture activation */
    bool deleted; /*!< record activation */


};

#endif // RECORD_H
