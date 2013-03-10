#include "../../includes/daolayer/historyrecord.h"

#include <QtCore/QObject>
#include <QtCore/QDate>

HistoryRecord::HistoryRecord(Record *pRecord)
{
    this->recordExecuted = pRecord;
    this->executionDate = QDate().currentDate().toString("yyyy-MM-dd");
}

HistoryRecord::HistoryRecord(int pId, Record *pRecord, QString pExecutingDate)
{
    this->id = pId;
    this->recordExecuted = pRecord;
    this->executionDate = pExecutingDate;
}

int HistoryRecord::getId()
{
    return this->id;
}

Record *HistoryRecord::getRecordExecuted()
{
    return this->recordExecuted;
}

QString HistoryRecord::getExecutionDate()
{
    return this->executionDate;
}

void HistoryRecord::setId(int pId)
{
    this->id = pId;
}

void HistoryRecord::setRecordExecuted(Record *pRecord)
{
    this->recordExecuted = pRecord;
}

void HistoryRecord::setExecutionDate(QString pExecutingDate)
{
    this->executionDate = pExecutingDate;
}
