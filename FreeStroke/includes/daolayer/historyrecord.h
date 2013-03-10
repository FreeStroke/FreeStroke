#ifndef HISTORYRECORD_H
#define HISTORYRECORD_H

/*!
 * \file historyrecord.h
 * \author Anthony Fourneau
 * \brief Representation of an history record
 * \date 2013-02-12
 */
#include <iostream>
#include <QtCore/QString>

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
