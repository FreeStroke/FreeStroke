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
#ifndef DAOLAYER_H
#define DAOLAYER_H

/*!
 * \file daolayer.h
 * \author Anthony Fourneau
 * \brief Access to the database
 * \date 2013-02-12
 */

#include "../daolayer/record.h"
#include "../common/gesture.h"
#include "historyrecord.h"
#include "sqlite3.h"

#define DBNAME "FreeStroke" /*!< The name of the database */

/*!
 * \class DAOLayer
 * \brief The class manages operations on the database
 *
 * This class is a singleton that allow you to connect to the database and save/get/remove record or history_record on the database
 */
class DAOLayer : public QObject
{
    Q_OBJECT

signals:

    /*!
     * \brief signal that a Record was added on the database
     *
     * \param the Record added on the database
     */
    void recordAdded(Record *);

    /*!
     * \brief signal that a HistoryRecord was added on the database
     *
     * \param the HistoryRecord added on the database
     */
    void historyRecordAdded(HistoryRecord *);

    /*!
     * \brief signal that a Record was deleted on the database
     *
     * \param the Record deleted on the database
     */
    void recordDeleted(Record *);

    /*!
     * \brief signal that the table HistoryRecord was emptied on the database
     *
     * On this case, all the HistoryRecord was deleted on the database
     */
    void historyRecordDeleted();

    /*!
     * \brief signal that new data has been transmitted from the Kinect
     *
     * The new data is sent to the other threads for update.
     */
    void skeletonDataReceived(QString);

public:
    /*!
     * \brief DAOLayer constructor, never call it manually
     *
     * This is the constructor, you don't have to call it, use getInstance() instead of it
     */
    DAOLayer();

    /*!
     * \brief DAOLayer destructor
     */
    ~DAOLayer();

    /*!
     * \brief This method instancie a single instance of DAOLayer
     * \return an instance of DAOLayer or NULL if it can't open database connection
     *
     *You should use this method to get an instance of DAOLayer. You have to test the result beacause it can be NULL if the connection the database failed.
     */
    static DAOLayer * getInstance();

    /*!
     * \brief Transform a char* gesture representation to a gesture
     * \param const char *  corresponding to a gesture in this format :  nbrGesture (nbrSkeletonData nbrJoinsParSkelData (timestamp (x y z) * nbrJoinssParSkelData ) * nbrSkeletonData)
     * \return Gesture * corresponding to the const char * parameter
     *
     * This static method permit to transform a char * representation of gesture to a gesture
     */
    static  Gesture * gestureFromChar(const char * );

    /*!
     * \brief Transform a gesture to a char* gesture representation
     * \param Gesture * a gesture
     * \return const char * representation gesture corresponding to gesture giving in parameter. The representation corresponding to : nbrGesture (nbrSkeletonData nbrJoinsParSkelData (timestamp (x y z) * nbrJoinssParSkelData ) * nbrSkeletonData)
     *
     * This static method permit to transform a gesture to his representation in const char *
     */
    static const char * gestureToChar(Gesture *);

    /*!
     * \brief Transform a list of gesture to a char* gesture representation
     * \param QList<Gesture *> * a list of gesture
     * \return const char * representation of the list of gesture corresponding to list of gesture giving in parameter. The representation corresponding to : nbrGesture (nbrSkeletonData nbrJoinsParSkelData (timestamp (x y z) * nbrJoinssParSkelData ) * nbrSkeletonData)
     *
     * This static method permit to transform a gesture to his representation in const char *
     */
    static const char * gesturesToChar(QList<Gesture *> *);

    /*!
     * \brief Transform a char* list gesture representation to a list of gesture
     * \param const char *  corresponding to a list of gesture in this format :  nbrGesture (nbrSkeletonData nbrJoinsParSkelData (timestamp (x y z) * nbrJoinssParSkelData ) * nbrSkeletonData)
     * \return QList<Gesture *> * corresponding to the const char * parameter
     *
     * This static method permit to transform a char * representation of list of gesture to a list of gesture
     */
    static QList<Gesture *> * gesturesFromChar(const char *);

    /*!
     * \brief add a record on the database
     *
     * \param the Record to add on the database
     * \return 0 on success or 1 in case of error
     *
     * Add a record on the database
     */
    bool addRecord(Record *);

    /*!
     * \brief  add an history record on the database
     * \param HistoryRecord*
     * \return  0 on success or 1 in case of error
     *
     *  Add an history record on the database, the history record must contain a valid record, because there is a foreign key with the record
     */
    bool addHistoryRecord(HistoryRecord *);

    /*!
     * \brief add a neutral gesture to the database
     * \param Gesture the gesture to save
     * \return  0 on success or 1 in case of error
     */
    bool addNeutralGesture(Gesture *);

    /*!
     * \brief gestureRecognized
     * \param pRecord
     */
    void gestureRecognized(Record* pRecord);

    /*!
     * \brief get all record of the database
     * \return QList<Record *> * all the record of the database or NULL in case of error
     */
    QList<Record *> *getRecords();

    /*!
     * \brief get a record of the database
     * \param the id of the record
     * \return Record * the record corresponding to the param or NULL in case of error
     */
    Record *getSingleRecord(int);

    /*!
     * \brief get all history record of the database
     * \return QList<HistoryRecord *> * all the history record of the database or NULL in case of error
     */
    QList<HistoryRecord *> *getHistoryRecords();

    /*!
     * \brief get all neutral gesture of the database
     * \return QList<Gesture> * all the gesture of the database or NULL in case of error
     */
    QList<Gesture *> *getNeutralGestures();

    /*!
     * \brief remove a record on the database
     * \return  0 on success or 1 in case of error
     */
    bool removeRecord(Record *);

    /*!
     * \brief remove all the history record on the database
     * \return  0 on success or 1 in case of error
     *
     * On this case, all the HistoryRecord was deleted on the database
     */
    bool removeHistoryRecord();

    /*!
     * \brief remove all the NeutralGesture on the database
     * \return 0 on success or 1 in case of error
     *
     * On this case, all the NeutralGesture was deleted on the database
     */
    bool removeNeutralGesture();

    /*!
     * \brief update the record on database with the value of Record passed in parameters
     * \param the updated record
     * \return   0 on success or 1 in case of error
     */
    bool updateRecord(Record *);

    /*!
     * \brief received data from network and add it to the database
     * \param QStrig the line received from communication
     *
     * Received data from network, add it to the database and signal new data
     */
    void dataFromCommunication(QString);

    /*!
     * \brief get the data base location
     * \return a string that represent the data base location
     */
    QString getDatabaseLocation();

private:

    /*!
     * \brief permit to add data on the data base for testing on initialization
     *
     * This method add some record and history record on the database for testing
     * This method should not be use on release.
     *
     */
    void generateFalseDataOnDb();

    /*!
     * \brief open the  database connection
     * \return  0 on success or 1 in case of error
     *
     * Open the database connection and create table if they don't exist
     */
    bool open();


    /*!
     * \brief close the database connection
     * \return  0 on success or 1 in case of error
     */
    bool close();

    QString dataBaseLocation; /*!< The data base location on the system */
    sqlite3	*db; /*!< The database connection handle :  is represented by a pointer to an instance of the opaque structure named "sqlite3" */
    sqlite3_stmt *statement;  /*!< SQL statement object : An instance of this object represents a single SQL statement. This object is variously known as a "prepared statement" or a "compiled SQL statement" or simply as a "statement" */

    /*!
     * \brief Try to get vector data about joints of a skeleton in a line parsed in argument.
     * \param pJointures
     * \param pJointCount
     * \return true if the parsing succeed, false if not.
     */
    static bool lineToVectors(QList<Vector3> *pJointures, QStringList *pLine, int pJointCount);
};

#endif // DAOLAYER_H
