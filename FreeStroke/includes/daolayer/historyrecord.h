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
#ifndef HISTORYRECORD_H
#define HISTORYRECORD_H

/*!
 * \file historyrecord.h
 * \author Anthony Fourneau
 * \brief Representation of an history record
 * \date 2013-02-12
 */

#include "record.h"

/*!
 * \class HistoryRecord
 * \brief The class is the representation of an HistoryRecord
 *
 */
class HistoryRecord {
public:
    /*!
     * \brief HistoryRecord constructor
     * \param the Record that this HistoryRecord will correspond
     */
    HistoryRecord(Record *);

    /*!
     * \brief HistoryRecord constructor
     * \param id of the HistoryRecord
     * \param the Record that this HistoryRecord will correspond
     * \param the date when the HistoryRecord was added
     */
    HistoryRecord(int,Record *,QString);

    /*!
     * \brief get the Id of the HistoryRecord
     * \return the Id of the HistoryRecord
     */
    int getId();
    /*!
     * \brief get the Record corresponding to the HistoryRecord
     * \return the Record corresponding to the HistoryRecord
     */
    Record *getRecordExecuted();
    /*!
     * \brief get the date of the HistoryRecord
     * \return the date of the HistoryRecord
     */
    QString getExecutionDate();

    /*!
     * \brief set the Id of this HistoryRecord
     * \param the id
     */
    void setId(int);

    /*!
     * \brief set the record corresponding to this HistoryRecord
     * \param the record corresponding to the HistoryRecord
     */
    void setRecordExecuted(Record *);

    /*!
     * \brief set the date of this HistoryRecord
     * \param the date
     */
    void setExecutionDate(QString);
private:
    int id; /*!< the id of the HistoryRecord */
    Record *recordExecuted; /*!< the record correponding to the HistoryRecord */
    QString executionDate; /*!< the date of the execution of the record*/
};

#endif // HISTORYRECORD_H
