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

#include "../../includes/daolayer/daolayer.h"
#include "../../includes/common/gesture.h"
#include "../../includes/daolayer/record.h"
#include "../../includes/daolayer/sqlite3.h"
#include "../../includes/common/utils.h"
#include "../../includes/gestures/features/allfeatures.h"

#include "../../includes/ui/notification/notifications.h"


static DAOLayer * singleton = NULL;

DAOLayer *DAOLayer::getInstance()
{
    if( singleton == NULL)
    {
        singleton = new DAOLayer();
        if(singleton->open() == 0)
        {
            #warning Must be remove
            #ifndef UNITTEST
            qDebug("");
            //singleton->generateFalseDataOnDb();
            #endif
        }
        else
        {
            delete(singleton);
            singleton = NULL;
        }
    }
    return singleton;
}

DAOLayer::DAOLayer()
{
    dataBaseLocation = Utils::getDatabaseLocation();
    QDir d(Utils::getDatabaseDirectoryLocation());
    if(! d.exists())
    {
        d.mkpath(Utils::getDatabaseDirectoryLocation());
    }
    //static QFile f("ns_01.log");
    //f.open(QFile::WriteOnly);
#warning This a static class, please use getInstance()
}

DAOLayer::~DAOLayer()
{
    this->close();
}

bool DAOLayer::open()
{
//    qDebug() << "DAOLayer#open() - start" ;
    const char *requestPragma = "PRAGMA foreign_keys = ON";
    const char *requestRecord = "CREATE TABLE IF NOT EXISTS 'FreeStroke.Record' ( id INTEGER PRIMARY KEY ASC AUTOINCREMENT, name TEXT, creation_date TEXT, gesture TEXT, command TEXT, command_type INTEGER, isCommandActive INTEGER DEFAULT 1, isGestureActive INTEGER DEFAULT 1, isDeleted INTEGER DEFAULT 0);";
    const char *requestHistoryRecord = "CREATE TABLE IF NOT EXISTS 'FreeStroke.HistoryRecord' ( id INTEGER PRIMARY KEY ASC AUTOINCREMENT, id_record INTEGER, execution_date TEXT, FOREIGN KEY(id_record) REFERENCES  'FreeStroke.Record'(id));";
    const char *requestNeutralGesture = "CREATE TABLE IF NOT EXISTS 'FreeStroke.NeutralGesture' (id INTEGER PRIMARY KEY ASC AUTOINCREMENT, gesture TEXT);";
    int result;
    qDebug() << "dateBaseLocation " << dataBaseLocation;
    result = sqlite3_open_v2(dataBaseLocation.toLocal8Bit().data(),&(this->db),SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE ,NULL);
    if(result)
    {
        qDebug() << "Can't open database: " << sqlite3_errmsg(this->db);
        sqlite3_close(this->db);
        qDebug() << "DAOLayer#open() - end" ;
        return 1;
    }

    result = sqlite3_prepare_v2(db,requestRecord,(strlen(requestRecord)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "1.Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        sqlite3_close(this->db);
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "2.Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        sqlite3_close(this->db);
        return 1;
    }

    sqlite3_finalize(this->statement);

    result = sqlite3_prepare_v2(db,requestHistoryRecord,(strlen(requestHistoryRecord)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "3.Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        sqlite3_close(this->db);
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "4.Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        sqlite3_close(this->db);
        return 1;
    }

    sqlite3_finalize(this->statement);

    result = sqlite3_prepare_v2(db,requestPragma,(strlen(requestPragma)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "5.Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        sqlite3_close(this->db);
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "6.Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        sqlite3_close(this->db);
        return 1;
    }

    sqlite3_finalize(this->statement);

    result = sqlite3_prepare_v2(db,requestNeutralGesture,(strlen(requestNeutralGesture)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "7.Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        sqlite3_close(this->db);
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "8.Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        sqlite3_close(this->db);
        return 1;
    }

    sqlite3_finalize(this->statement);

//    qDebug() << "DAOLayer#open() - end normally" ;
    return 0;
}

bool DAOLayer::close()
{
//    qDebug() << "DAOLayer#close() - start" ;
    int result = sqlite3_close(this->db);
    if(result)
    {
        qDebug() << "Can't close database: " << sqlite3_errmsg(this->db);
        qDebug() << "DAOLayer#close() - end" ;
        return 1;
    }
//    qDebug() << "DAOLayer#close() - end" ;
    return 0;
}

bool DAOLayer::addRecord(Record *pRecord)
{
//    qDebug() << "DAOLayer#addRecord() - start" ;

    if(pRecord == NULL)
    {
        qDebug() << "DAOLayer#addRecord() - pRecord can't be NULL" ;
        qDebug() << "DAOLayer#addRecord() - end" ;
        return 1;
    }

    int result;
    const char *request = "INSERT INTO 'FreeStroke.Record' (name, creation_date, gesture,command, command_type, isCommandActive, isGestureActive, isDeleted) VALUES(:NAME, date('now'),:GES, :COMM, :CMTY, :ISCA, :ISGA, :ISDE);";

    result = sqlite3_prepare_v2(this->db,request,(strlen(request)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addRecord() - end" ;
        return 1;
    }
    char const * flatGesture = this->gesturesToChar(pRecord->getGestures());
    if (flatGesture == NULL)
    {
        qDebug()<<"DAOLayer#addRecord() - Gesture NULL";
        return false;
    }

    result = sqlite3_bind_text(this->statement, sqlite3_bind_parameter_index(this->statement, ":NAME"), pRecord->getName().toUtf8().data(), (((pRecord->getName()).length())*2)+1,  SQLITE_TRANSIENT);
    if(result)
    {
        qDebug() << "Can't bind name  request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addRecord() - end" ;
        return 1;
    }
    result = sqlite3_bind_text(this->statement, sqlite3_bind_parameter_index(this->statement, ":GES"), flatGesture, strlen(flatGesture)+1,  SQLITE_TRANSIENT);
    if(result)
    {
        qDebug() << "Can't bind gesture  request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addRecord() - end" ;
        return 1;
    }
    result = sqlite3_bind_text(this->statement, sqlite3_bind_parameter_index(this->statement, ":COMM"),(*(pRecord->getCommand())).getDefinition().toUtf8().data(), ((((*(pRecord->getCommand())).getDefinition()).length())*2)+1,  SQLITE_TRANSIENT);
    if(result)
    {
        qDebug() << "Can't bind command  request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addRecord() - end" ;
        return 1;
    }
    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":CMTY"), (*(pRecord->getCommand())).getType());
    if(result)
    {
        qDebug() << "Can't bind command type request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addRecord() - end" ;
        return 1;
    }
    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":ISCA"), pRecord->isCommandActive());
    if(result)
    {
        qDebug() << "Can't bind isCammandActive  request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addRecord() - end" ;
        return 1;
    }
    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":ISGA"), pRecord->isGestureActive());
    if(result)
    {
        qDebug() << "Can't bind isGestureActive  request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addRecord() - end" ;
        return 1;
    }
    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":ISDE"), pRecord->isDeleted());
    if(result)
    {
        qDebug() << "Can't bind isDeleted  request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addRecord() - end" ;
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "Can't bind execute  request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addRecord() - end" ;
        return 1;
    }

    sqlite3_finalize(this->statement);
    delete(flatGesture);
    // SIGNAL
    emit recordAdded(pRecord);

//    qDebug() << "DAOLayer#addRecord() - end final" ;
    return 0;
}

QList<Record *> * DAOLayer::getRecords()
{
//    qDebug() << "DAOLayer#getRecords() - start" ;
    int result;
    const char *request = "SELECT * FROM 'FreeStroke.Record';";
    QList<Record *> *records = new QList<Record *>();
    result = sqlite3_prepare_v2(this->db,request,(strlen(request)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        return NULL;
    }

    do
    {
        result = sqlite3_step(this->statement);
        if(result == SQLITE_ROW)
        {
            int i = 0;
            int id = sqlite3_column_int(this->statement,i++);
            const char *name = reinterpret_cast<const char*>(sqlite3_column_text(statement, i++));
            const char *creationDate = reinterpret_cast<const char*>(sqlite3_column_text(statement, i++));
            const char *gesture =  reinterpret_cast<const char*>(sqlite3_column_text(statement, i++));
            const char *commandText = reinterpret_cast<const char*>(sqlite3_column_text(statement, i++));
            CommandType commandType = (CommandType)sqlite3_column_int(this->statement, i++);
            Command *myCommand = new Command(commandText,commandType);
            bool isGestureActive = sqlite3_column_int(this->statement,i++);
            bool isCommandActive = sqlite3_column_int(this->statement,i++);
            bool isDeleted = sqlite3_column_int(this->statement,i++);
            Record *rec = new Record(id,name,creationDate,gesturesFromChar(gesture),myCommand, isGestureActive, isCommandActive, isDeleted);
            records->append(rec);
        }
        else if(result != SQLITE_DONE)
        {
            qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
            sqlite3_finalize(this->statement);
            return NULL;
        }
    }
    while(result != SQLITE_DONE);
    sqlite3_finalize(this->statement);


//    qDebug() << "DAOLayer#getRecords() - end" ;
    return records;
}


Record * DAOLayer::getSingleRecord(int pId)
{
    int result;
    const char *request = "SELECT * FROM 'FreeStroke.Record' WHERE id=:IDRE;";
    Record *rec = NULL;
    result = sqlite3_prepare_v2(this->db,request,(strlen(request)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        return NULL;
    }
    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":IDRE"), pId);
    if(result)
    {
        qDebug() << "Can't bind id request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        return NULL;
    }
    result = sqlite3_step(this->statement);
    if(result != SQLITE_ROW)
    {
        qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        return NULL;
    }
    int i = 0;
    int id = sqlite3_column_int(this->statement,i++);
    const char *name = reinterpret_cast<const char*>(sqlite3_column_text(statement, i++));
    const char *creationDate = reinterpret_cast<const char*>(sqlite3_column_text(statement, i++));
    const char *gesture =  reinterpret_cast<const char*>(sqlite3_column_text(statement, i++));
    const char *commandText = reinterpret_cast<const char*>(sqlite3_column_text(statement, i++));
    CommandType commandType = (CommandType)sqlite3_column_int(this->statement, i++);
    Command *myCommand = new Command(commandText,commandType);
    bool isGestureActive = sqlite3_column_int(this->statement,i++);
    bool isCommandActive = sqlite3_column_int(this->statement,i++);
    bool isDeleted = sqlite3_column_int(this->statement,i++);
    rec = new Record(id,name,creationDate,gesturesFromChar(gesture),myCommand, isGestureActive, isCommandActive, isDeleted);

    sqlite3_finalize(this->statement);
    return rec;

}

bool DAOLayer::removeRecord(Record *pRecord)
{
    //qDebug() << "DAOLayer#removeRecord() - start" ;
    //qDebug() << "Id record " << pRecord->getId();
    if(pRecord == NULL)
    {
        qDebug() << "DAOLayer#removeRecord() - pRecord can't be NULL" ;
        qDebug() << "DAOLayer#removeRecord() - end" ;
        return 1;
    }

    int result;
    const char *requestDelete;
    const char *resquestSel = "SELECT * FROM 'FreeStroke.HistoryRecord' WHERE id_record=:IDRE;";
    int countHistory =0;

    result = sqlite3_prepare_v2(this->db,resquestSel,(strlen(resquestSel)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "1.Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#removeRecord() - end" ;
        return 1;
    }

    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":IDRE"), pRecord->getId());
    do
    {
        result = sqlite3_step(this->statement);
        if(result == SQLITE_ROW)
        {
            countHistory++;
        }
        else if(result != SQLITE_DONE)
        {
            qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
            sqlite3_finalize(this->statement);
            qDebug() << "DAOLayer#removeRecord() - end" ;
            return 1;
        }
    }
    while(result != SQLITE_DONE);

    sqlite3_finalize(this->statement);

    if(countHistory == 0)
    {
        requestDelete = "DELETE FROM 'FreeStroke.Record' WHERE id=:IDRE;";
    }
    else
    {
        requestDelete = "UPDATE 'FreeStroke.Record' SET isDeleted=1  WHERE id=:IDRE;";
    }

    //qDebug()<<"Request "<<requestDelete;

    result = sqlite3_prepare_v2(this->db,requestDelete,(strlen(requestDelete)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug(requestDelete);
        qDebug() << "2.Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#removeRecord() - end" ;
        return 1;
    }

    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":IDRE"), pRecord->getId());
    if(result)
    {
        qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#removeRecord() - end" ;
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#removeRecord() - end" ;
        return 1;
    }

    sqlite3_finalize(this->statement);

    //SIGNAL
    emit recordDeleted(pRecord);

//    qDebug() << "DAOLayer#removeRecord() - end" ;
    return 0;
}

bool DAOLayer::updateRecord(Record * pRecord)
{
//    qDebug() << "DAOLayer#updateRecord() - start" ;

    if(pRecord == NULL)
    {
        qDebug() << "DAOLayer#updateRecord() - pRecord can't be NULL" ;
        qDebug() << "DAOLayer#updateRecord() - end" ;
        return 1;
    }

    const char * request = "UPDATE 'FreeStroke.Record' SET  name=:NAME, command=:COMM, command_type=:CMTY, isCommandActive=:ISCA, isGestureActive=:ISGA, isDeleted=:ISDE  WHERE id=:IDRE;";

    int result = sqlite3_prepare_v2(this->db,request,(strlen(request)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#updateRecord() - end" ;
        return 1;
    }


    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":IDRE"), pRecord->getId());
    if(result)
    {
        qDebug() << "Can't bind ID request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#updateRecord() - end" ;
        return 1;
    }


    result = sqlite3_bind_text(this->statement, sqlite3_bind_parameter_index(this->statement, ":NAME"), pRecord->getName().toLocal8Bit().data(), (((pRecord->getName()).length())*2)+1,  SQLITE_TRANSIENT);
    if(result)
    {
        qDebug() << "Can't bind name request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#updateRecord() - end" ;
        return 1;
    }

    result = sqlite3_bind_text(this->statement, sqlite3_bind_parameter_index(this->statement, ":COMM"),(*(pRecord->getCommand())).getDefinition().toLocal8Bit().data(), ((((*(pRecord->getCommand())).getDefinition()).length())*2)+1,  SQLITE_TRANSIENT);
    if(result)
    {
        qDebug() << "Can't bind command request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#updateRecord() - end" ;
        return 1;
    }
    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":CMTY"), (*(pRecord->getCommand())).getType());
    if(result)
    {
        qDebug() << "Can't bind command type request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#updateRecord() - end" ;
        return 1;
    }
    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":ISCA"), pRecord->isCommandActive());
    if(result)
    {
        qDebug() << "Can't bind isCammandActive request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#updateRecord() - end" ;
        return 1;
    }
    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":ISGA"), pRecord->isGestureActive());
    if(result)
    {
        qDebug() << "Can't bind isGestureActive request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#updateRecord() - end" ;
        return 1;
    }
    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":ISDE"), pRecord->isDeleted());
    if(result)
    {
        qDebug() << "Can't bind isDeleted request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#updateRecord() - end" ;
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#updateRecord() - end" ;
        return 1;
    }

    sqlite3_finalize(this->statement);


//    qDebug() << "DAOLayer#updateRecord() - end" ;
    return 0;
}

bool DAOLayer::addHistoryRecord(HistoryRecord *pHistoryRecord)
{
//    qDebug() << "DAOLayer#addHistoryRecord() - start" ;

    if(pHistoryRecord == NULL)
    {
        qDebug() << "DAOLayer#addHistoryRecord() - pHistoryRecord can't be NULL" ;
        qDebug() << "DAOLayer#addHistoryRecord() - end" ;
        return 1;
    }


    int result;
    const char *request = "INSERT INTO  'FreeStroke.HistoryRecord' (id_record, execution_date) VALUES(:IDRE, date('now'));";

    result = sqlite3_prepare_v2(this->db,request,(strlen(request)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addHistoryRecord() - end" ;
        return 1;
    }

    result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":IDRE"), pHistoryRecord->getRecordExecuted()->getId());
    if(result)
    {
        qDebug() << "Can't bind request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addHistoryRecord() - end" ;
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addHistoryRecord() - end" ;
        return 1;
    }

    sqlite3_finalize(this->statement);

    // SIGNAL
    emit historyRecordAdded(pHistoryRecord);

//    qDebug() << "DAOLayer#addHistoryRecord() - end" ;
    return 0;
}

bool DAOLayer::removeHistoryRecord()
{
//    qDebug() << "DAOLayer#removeHistoryRecord() - start" ;

    int result;
    const char *resquestSel = "SELECT DISTINCT id_record FROM 'FreeStroke.HistoryRecord';";
    const char *resquestDelHistory = "DELETE FROM 'FreeStroke.HistoryRecord'";
    const char *requestDelRec  = "DELETE FROM 'FreeStroke.Record' WHERE id=:IDRE AND isDeleted=1";
    QList<int> *idsRecord = new QList<int>();

    // GET DISTINCT RECORDS_ID

    result = sqlite3_prepare_v2(this->db,resquestSel,(strlen(resquestSel)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() <<  "Can't prepare request select : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#removeHistoryRecord() - end" ;
        return 1;
    }

    do
    {
        result = sqlite3_step(this->statement);
        if(result == SQLITE_ROW)
        {
            idsRecord->append(sqlite3_column_int(this->statement,0));
        }
        else if(result != SQLITE_DONE)
        {
             qDebug() <<  "Can't execute request select : " << sqlite3_errmsg(this->db);
            sqlite3_finalize(this->statement);
            qDebug() << "DAOLayer#removeHistoryRecord() - end" ;
            return 1;
        }
    }
    while(result != SQLITE_DONE);
    sqlite3_finalize(this->statement);

    // CLEAN HISTORY_RECORDS TABLE

    result = sqlite3_prepare_v2(this->db,resquestDelHistory,(strlen(resquestDelHistory)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() <<  "Can't prepare request delete history: " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#removeHistoryRecord() - end" ;
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "result " << result;
         qDebug() <<  "1.Can't execute request delete history : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#removeHistoryRecord() - end" ;
        return 1;
    }

    sqlite3_finalize(this->statement);

    // DELETE RECORD THAT HAVE isDeleted TO 1
    result = sqlite3_prepare_v2(this->db,requestDelRec,(strlen(requestDelRec)*2)+1,&this->statement,NULL);
    if(result)
    {
         qDebug() <<  "Can't prepare request delete record: " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#removeHistoryRecord() - end" ;
        return 1;
    }

    for(int i = 0; i < idsRecord->size(); i++)
    {
        result = sqlite3_bind_int(this->statement, sqlite3_bind_parameter_index(this->statement, ":IDRE"),idsRecord->at(i) );
        if(result)
        {
            qDebug() << "result " << result;
             qDebug() <<  "2.Can't bind id delete history : " << sqlite3_errmsg(this->db);
            sqlite3_finalize(this->statement);
            qDebug() << "DAOLayer#removeHistoryRecord() - end";
            return 1;
        }
        result = sqlite3_step(this->statement);
        if(result != SQLITE_DONE)
        {
            qDebug() << "result " << result;
             qDebug() <<  "2.Can't execute request delete history : " << sqlite3_errmsg(this->db);
            sqlite3_finalize(this->statement);
            qDebug() << "DAOLayer#removeHistoryRecord() - end" ;
            return 1;
        }
       result =  sqlite3_reset(this->statement);
       if(result)
       {
           qDebug() << "result " << result;
            qDebug() <<  "2.Can't execute request delete history : " << sqlite3_errmsg(this->db);
           sqlite3_finalize(this->statement);
           qDebug() << "DAOLayer#removeHistoryRecord() - end" ;
           return 1;
       }
    }

    sqlite3_finalize(this->statement);

    // SIGNAL
    emit historyRecordDeleted();

//    qDebug() << "DAOLayer#removeHistoryRecord() - end" ;
    return 0;
}

QList<HistoryRecord *> *DAOLayer::getHistoryRecords()
{
//    qDebug() << "DAOLayer#getHistoryRecords() - start" ;
    int result;
    const char *resquestSel = "SELECT * FROM 'FreeStroke.HistoryRecord';";
    QList<HistoryRecord *> *histoRecords = new QList<HistoryRecord *>();

    result = sqlite3_prepare_v2(this->db,resquestSel,(strlen(resquestSel)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#getHistoryRecords() - end" ;
        return NULL;
    }

    do
    {
        result = sqlite3_step(this->statement);
        if(result == SQLITE_ROW)
        {
            int result2;
            sqlite3_stmt *statement2;
            int  i = 0;
            int id = sqlite3_column_int(this->statement, i++);
            int id_record = sqlite3_column_int(this->statement, i++);
            const char *creationDate = reinterpret_cast<const char*>(sqlite3_column_text(statement, i++));
            const char *request = "SELECT * FROM 'FreeStroke.Record' WHERE id=:IDRE;";
            Record *rec;

            result2 = sqlite3_prepare_v2(this->db,request,(strlen(request)*2)+1,&statement2,NULL);
            if(result2)
            {
                qDebug() << "Can't prepare request : " << sqlite3_errmsg(this->db);
                sqlite3_finalize(statement2);
                qDebug() << "DAOLayer#getHistoryRecords() - end" ;
                return NULL;
            }

            result2 = sqlite3_bind_int(statement2, sqlite3_bind_parameter_index(statement2, ":IDRE"), id_record);
            do
            {
                result2 = sqlite3_step(statement2);
                if(result2 == SQLITE_ROW)
                {
                    int i = 0;
                    int id = sqlite3_column_int(statement2,i++);
                    const char *name = reinterpret_cast<const char*>(sqlite3_column_text(statement2, i++));
                    const char *creationDate = reinterpret_cast<const char*>(sqlite3_column_text(statement2, i++));
                    const char *gesture =  reinterpret_cast<const char*>(sqlite3_column_text(statement2, i++));
                    const char *commandText = reinterpret_cast<const char*>(sqlite3_column_text(statement2, i++));
                    CommandType commandType = (CommandType)sqlite3_column_int(statement2, i++);
                    Command *myCommand = new Command(commandText,commandType);
                    bool isGestureActive = sqlite3_column_int(statement2,i++);
                    bool isCommandActive = sqlite3_column_int(statement2,i++);
                    bool isDeleted = sqlite3_column_int(statement2,i++);
                    rec = new Record(id,name,creationDate,gesturesFromChar(gesture),myCommand, isGestureActive, isCommandActive, isDeleted);

                }
                else if(result2 != SQLITE_DONE)
                {
                    qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
                    sqlite3_finalize(statement2);
                    qDebug() << "DAOLayer#getHistoryRecords() - end" ;
                    return NULL;
                }
            }
            while(result2 != SQLITE_DONE);
            sqlite3_finalize(statement2);

            HistoryRecord *hr = new HistoryRecord(id, rec, creationDate);
            histoRecords->append(hr);

        }
        else if(result != SQLITE_DONE)
        {
            qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
            sqlite3_finalize(this->statement);
            qDebug() << "DAOLayer#getHistoryRecords() - end" ;
            return NULL;
        }
    }
    while(result != SQLITE_DONE);

    sqlite3_finalize(this->statement);

//    qDebug() << "DAOLayer#getHistoryRecords() - end" ;
    return histoRecords;
}

bool DAOLayer::addNeutralGesture(Gesture * pGesture)
{
//    qDebug() << "DAOLayer#addNeutralGesture() - start" ;

    if(pGesture == NULL)
    {
        qDebug() << "DAOLayer#addNeutralGesture() - pGesture can't be NULL" ;
        qDebug() << "DAOLayer#addNeutralGesture() - end" ;
        return 1;
    }


    int result;
    const char *request = "INSERT INTO 'FreeStroke.NeutralGesture' (gesture) VALUES(:GEST);";

    result = sqlite3_prepare_v2(this->db,request,(strlen(request)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addNeutralGesture() - end" ;
        return 1;
    }

    char const * flatGesture = this->gestureToChar(pGesture);

    result = sqlite3_bind_text(this->statement, sqlite3_bind_parameter_index(this->statement, ":GEST"), flatGesture, strlen(flatGesture)+1,  SQLITE_TRANSIENT);
    if(result)
    {
        qDebug() << "Can't bind gesture request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addNeutralGesture() - end" ;
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#addNeutralGesture() - end" ;
        return 1;
    }

    sqlite3_finalize(this->statement);

    delete(flatGesture);

//    qDebug() << "DAOLayer#addNeutralGesture() - end" ;
    return 0;
}

QList<Gesture *> * DAOLayer::getNeutralGestures()
{
//    qDebug() << "DAOLayer#getNeutralGestures() - start" ;
    int result;
    const char *request = "SELECT * FROM 'FreeStroke.NeutralGesture';";
    QList<Gesture *> *gestures = new QList<Gesture *>();

    result = sqlite3_prepare_v2(this->db,request,(strlen(request)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#getNeutralGestures() - end" ;
        return NULL;
    }

    do
    {
        result = sqlite3_step(this->statement);
        if(result == SQLITE_ROW)
        {
            const char *gesture =  reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));

            Gesture * ges = gestureFromChar(gesture);
            gestures->append(ges);
        }
        else if(result != SQLITE_DONE)
        {
            qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
            sqlite3_finalize(this->statement);
            qDebug() << "DAOLayer#getNeutralGestures() - end" ;
            return NULL;
        }
    }
    while(result != SQLITE_DONE);
    sqlite3_finalize(this->statement);


//    qDebug() << "DAOLayer#getNeutralGestures() - end" ;
    return gestures;
}

bool DAOLayer::removeNeutralGesture()
{
//    qDebug() << "DAOLayer#removeNeutralGesture() - start" ;

    int result;
    const char *resquestDelNeutralGesture = "DELETE FROM 'FreeStroke.NeutralGesture'";


    result = sqlite3_prepare_v2(this->db,resquestDelNeutralGesture,(strlen(resquestDelNeutralGesture)*2)+1,&this->statement,NULL);
    if(result)
    {
        qDebug() << "Can't prepare request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#removeNeutralGesture() - end" ;
        return 1;
    }

    result = sqlite3_step(this->statement);
    if(result != SQLITE_DONE)
    {
        qDebug() << "Can't execute request : " << sqlite3_errmsg(this->db);
        sqlite3_finalize(this->statement);
        qDebug() << "DAOLayer#removeNeutralGesture() - end" ;
        return 1;
    }

    sqlite3_finalize(this->statement);

//    qDebug() << "DAOLayer#removeNeutralGesture() - end" ;
    return 0;
}

const char * DAOLayer::gestureToChar(Gesture * pGesture)
{
//    qDebug() << "DAOLayer::gestureToChar() - start";

    if(pGesture == NULL)
    {
        qDebug() << "DAOLayer#gestureToChar() - pGesture can't be NULL" ;
        qDebug() << "DAOLayer#gestureToChar() - end" ;
        return NULL;
    }


    QString *flatGesture = new QString();
    QList<SkeletonData*> * frames = pGesture->getFrames();
    if(frames->count() <= 0)
    {
        qDebug() << "DAOLayer::gestureToChar() - The list must not be empty";
        return NULL;
    }
    // nbrSkeletonData nbrJointuresParSkelData (timestamp (x y z) * nbrJointuresParSkelData ) * nbrSkeletonData
    flatGesture->append(QString::number(frames->count()));
    flatGesture->append(" ");
    flatGesture->append(QString::number(((SkeletonData*)frames->at(0))->getJointures()->count()));
    flatGesture->append(" ");

    for (int  i = 0 ; i < frames->count() ; i++)
    {
        SkeletonData*  skelData = frames->at(i);
        flatGesture->append(QString::number(skelData->getTimestamp()));
        flatGesture->append(" ");
        QList<Vector3> *jointures = skelData->getJointures();
        for(int j = 0 ; j < jointures->count() ; j++)
        {
            Vector3 jointure =  jointures->at(j);
            QString xString;
            xString.setNum(jointure.x,'g',10);
            QString yString;
            yString.setNum(jointure.y,'g',10);
            QString zString;
            zString.setNum(jointure.z,'g',10);
            flatGesture->append(xString);
            flatGesture->append(" ");
            flatGesture->append(yString);
            flatGesture->append(" ");
            flatGesture->append(zString);
            flatGesture->append(" ");
        }
    }
    char *temp = new char[flatGesture->length()+1];
    strcpy(temp,flatGesture->toLocal8Bit().data());
    return temp;
}

Gesture * DAOLayer::gestureFromChar(const char * pGestureArrayChar)
{
//    qDebug() << "DAOLayer::gestureFromChar() - start";

    if(pGestureArrayChar == NULL)
    {
        qDebug() << "DAOLayer#gestureFromChar() - pGestureArrayChar can't be NULL" ;
        qDebug() << "DAOLayer#gestureFromChar() - end" ;
        return NULL;
    }


    QString *gestureString = new QString(pGestureArrayChar);
    QStringList occurs = gestureString->split(" ",  QString::SkipEmptyParts);
    if(occurs.isEmpty())
    {
        qDebug() << "DAOLayer::gestureFromChar() - The list must not be empty";
        return NULL;
    }
    QList<SkeletonData*> * frames = new QList<SkeletonData*>();

    int nbrSkelData = occurs.takeFirst().toInt();
    int nbrJoints = occurs.takeFirst().toInt();
    for(int i = 0 ; i < nbrSkelData ; i++ )
    {
        int timestamp = occurs.takeFirst().toLong();
        QList<Vector3> *jointures = new QList<Vector3>();
        if (!lineToVectors(jointures, &occurs, nbrJoints))
        {
            qDebug()<<"Error while getting neutral";
        }
        SkeletonData *skelData = new SkeletonData(jointures,timestamp);
        frames->append(skelData);
    }

    if( !occurs.isEmpty())
    {
        qDebug() << "DAOLayer::gestureFromChar() - The list should be empty";
        return NULL;
    }

    Gesture * gesture = new Gesture(frames);
//    qDebug() << "DAOLayer::gestureFromChar() - end";
    return gesture;
}


const char * DAOLayer::gesturesToChar(QList<Gesture *> * pGestures)
{
//    qDebug() << "DAOLayer::gesturesToChar() - start";

    if(pGestures == NULL)
    {
        qDebug() << "DAOLayer::gesturesToChar() - pGestures can't be NULL";
        return NULL;
    }

    QString *flatGesture = new QString();

    if(pGestures->count() <= 0)
    {
        qDebug() << "DAOLayer::gesturesToChar() - The list of gesture must not be empty";
        return NULL;
    }
    flatGesture->append(QString::number(pGestures->count()));
    flatGesture->append(" ");
    for(int i = 0 ; i < pGestures->count() ; i ++)
    {
        Gesture * gesture = pGestures->at(i);
        const char * tmp = DAOLayer::gestureToChar(gesture);
        if(tmp == NULL)
        {
            qDebug() << "DAOLayer::gesturesToChar() - Error when processing transformation";
            return NULL;
        }
        flatGesture->append(tmp);
        delete(tmp);
    }
    char *temp = new char[flatGesture->length()+1];
    strcpy(temp,flatGesture->toLocal8Bit().data());
    return temp;
}

QList<Gesture *> * DAOLayer::gesturesFromChar(const char * pGestureArrayChar)
{
//    qDebug() << "DAOLayer::gesturesFromChar() - start";

    if(pGestureArrayChar == NULL)
    {
        qDebug() << "DAOLayer#gesturesFromChar() - pGestureArrayChar can't be NULL" ;
        qDebug() << "DAOLayer#gesturesFromChar() - end" ;
        return NULL;
    }


    QString *gestureString = new QString(pGestureArrayChar);
    QStringList occurs = gestureString->split(" ",  QString::SkipEmptyParts);
    QList<Gesture *> *gestures = new QList<Gesture * >();
    if(occurs.isEmpty())
    {
        qDebug() << "DAOLayer::gesturesFromChar() - The list must not be empty";
        return NULL;
    }
    int nbrGesture = occurs.takeFirst().toInt();
    for ( int i = 0 ; i < nbrGesture ; i++)
    {

        QList<SkeletonData*> * frames = new QList<SkeletonData*>();
        int nbrSkelData = occurs.takeFirst().toInt();
        int nbrJoints = occurs.takeFirst().toInt();
        for(int j = 0 ; j < nbrSkelData ; j++ )
        {
            int timestamp = occurs.takeFirst().toInt();
            QList<Vector3> *jointures = new QList<Vector3>();
            lineToVectors(jointures, &occurs, nbrJoints);
            SkeletonData *skelData = new SkeletonData(jointures,timestamp);
            frames->append(skelData);
        }

        Gesture * gesture = new Gesture(frames);
        gestures->append(gesture);
    }

    if( !occurs.isEmpty())
    {
        qDebug() << "DAOLayer::gesturesFromChar() - The list should be empty";
        return NULL;
    }

//    qDebug() << "DAOLayer::gesturesFromChar() - end";
    return gestures;
}

void DAOLayer::gestureRecognized(Record *pRecord)
{
    Notifications::add(Notification::Success,"Gesture recognized : " + pRecord->getName(), 6000);
    HistoryRecord *hr = new HistoryRecord(pRecord);
    this->addHistoryRecord(hr);
    if(pRecord->isCommandActive())
    {
        pRecord->getCommand()->executeCommand();
    }
}

void DAOLayer::dataFromCommunication(QString line)
{
    if(line.isEmpty())
    {
        qDebug() << "DAOLayer#dataFromCommunication() - line can't be empty" ;
        qDebug() << "DAOLayer#dataFromCommunication() - end" ;
        return;
    }
    //f.write(line.toAscii());
    //f.write("\n");
    emit this->skeletonDataReceived(line);
}

QString DAOLayer::getDatabaseLocation()
{
    return this->dataBaseLocation;
}

void DAOLayer::generateFalseDataOnDb()
{
//    qDebug() << "generateFalseDataOnDb() - start";

    //Clean DB
    QList<Record *> * records = singleton->getRecords();
    for (int i = 0 ; i < records->count() ; i++)
    {
        singleton->removeRecord(records->at(i));
    }
    singleton->removeHistoryRecord();


    int res;


    // Add clap.log
    Gesture * g = Gesture::fromFile(QDir::toNativeSeparators(Utils::getApplicationDirectoryRoot() + "../../tests/FreeStrokeUnitTest/others/clap.log"));
    qDebug() << QDir::toNativeSeparators(Utils::getApplicationDirectoryRoot() + "../../tests/FreeStrokeUnitTest/others/clap.log");
    if( g == NULL)
    {
        qDebug() << "generateFalseDataOnDb() - Error gesure::fromFile clap ==> NULL";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    Command * command = new Command("Shift\t5",KEYSTROKE);
    QList<Gesture *> * gestures = new QList<Gesture *>();
    gestures->append(g);
    Record *r = new Record("Ma clap commande",gestures,command);
    res = singleton->addRecord(r);
    int id = sqlite3_last_insert_rowid(this->db);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data clap";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    r->setId(id);

    // Add kick.log
    g = Gesture::fromFile(QDir::toNativeSeparators(Utils::getApplicationDirectoryRoot() + "../../tests/FreeStrokeUnitTest/others/kick.log"));
    if( g == NULL)
    {
        qDebug() << "generateFalseDataOnDb() - Error gesure::fromFile kick ==> NULL";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    command = new Command("Ctrl\tAlt\t5",KEYSTROKE);
    gestures->clear();
    gestures->append(g);
    Record *r1 = new Record("Ma kick commande",gestures,command);
    res = singleton->addRecord(r1);
    id = sqlite3_last_insert_rowid(this->db);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data kick";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    r1->setId(id);

    // Add jump.log
    g = Gesture::fromFile(QDir::toNativeSeparators(Utils::getApplicationDirectoryRoot() + "../../tests/FreeStrokeUnitTest/others/jump.log"));
    if( g == NULL)
    {
        qDebug() << "generateFalseDataOnDb() - Error gesure::fromFile jump ==> NULL";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    command = new Command("Meta\tD",KEYSTROKE);
    gestures->clear();
    gestures->append(g);
    Record *r2 = new Record("Ma jump commande",gestures,command);
    res = singleton->addRecord(r2);
    id = sqlite3_last_insert_rowid(this->db);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data jump";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    r2->setId(id);

    HistoryRecord *hr = new HistoryRecord(r);
    HistoryRecord *hr1 = new HistoryRecord(r1);
    HistoryRecord *hr2 = new HistoryRecord(r2);
    res = singleton->addHistoryRecord(hr);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    res = singleton->addHistoryRecord(hr1);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    res = singleton->addHistoryRecord(hr2);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    res = singleton->addHistoryRecord(hr);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    res = singleton->addHistoryRecord(hr1);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    res = singleton->addHistoryRecord(hr2);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    res = singleton->addHistoryRecord(hr);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    res = singleton->addHistoryRecord(hr1);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    res = singleton->addHistoryRecord(hr2);
    if(res == 1)
    {
        qDebug() << "generateFalseDataOnDb() - Error while adding data";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }

    for(int i = 0; i<10;i++)
    {
        res = singleton->addHistoryRecord(hr2);
        if(res == 1)
        {
            qDebug() << "generateFalseDataOnDb() - Error while adding data";
            qDebug() << "generateFalseDataOnDb() - end";
            return;
        }
    }


//    qDebug() << "generateFalseDataOnDb() - end";
}

bool DAOLayer::lineToVectors(QList<Vector3> *pJointures, QStringList *pLine, int pJointCount)
{
    for( int j = 0 ; j < pJointCount ; j++ )
    {
        bool res = true;
        float x = pLine->takeFirst().toFloat(&res);
        if(res == false)
        {
            return false;
        }
        float y = pLine->takeFirst().toFloat(&res);
        if(res == false)
        {
            return false;
        }
        float z = pLine->takeFirst().toFloat(&res);
        if(res == false)
        {
            return false;
        }
        Vector3 * vec = new Vector3(x,y,z);
        pJointures->append(*vec);
    }
    return true;
}
