#include "../includes/historyrecordtest.h"
#include "../../includes/daolayer/record.h"
#include "../../includes/common/gesture.h"
#include "../../includes/daolayer/command.h"
#include "../../includes/daolayer/commandtype.h"
#include "../../includes/daolayer/historyrecord.h"

#include <QtCore/QDate>
HistoryRecordTest::HistoryRecordTest(std::string name) : CppUnit::TestCase(name) {}

void HistoryRecordTest::runTest()
{
    QString name = QString("testRecord");
    QString name2 = QString("other");
    QList<Gesture*> *gestList = new QList<Gesture*>();
    QList<Gesture*> *gestList2 = new QList<Gesture*>();
    gestList->append(Gesture::fromFile("others/clap.log"));
    Command *c = new Command("CTRL  Q", KEYSTROKE);
    Command *c2 = new Command("plop.exe", SCRIPT);
    Record *r = new Record(name, gestList, c);
    Record *r2 = new Record(name2, gestList2, c2);
    HistoryRecord *hr = new HistoryRecord(r);
    HistoryRecord *hr2 = new HistoryRecord(0, NULL, QDate().currentDate().toString("yyyy-MM-dd"));
    CPPUNIT_ASSERT(hr->getExecutionDate().compare(QDate().currentDate().toString("yyyy-MM-dd")) == 0);
    CPPUNIT_ASSERT(hr->getExecutionDate().compare(hr2->getExecutionDate()) == 0);
    CPPUNIT_ASSERT(hr2->getId() == 0);
    CPPUNIT_ASSERT(hr->getRecordExecuted()->getName().compare(r->getName()) == 0);
    hr->setId(1);
    CPPUNIT_ASSERT(hr->getId() != hr2->getId());
    hr->setExecutionDate(QDate().currentDate().addDays(2).toString("yyyy-MM-dd"));
    CPPUNIT_ASSERT(hr->getExecutionDate().compare(QDate().currentDate().addDays(2).toString()));
    hr2->setRecordExecuted(r);
    CPPUNIT_ASSERT(hr2->getRecordExecuted()->getId() == hr->getRecordExecuted()->getId());
    hr2->setRecordExecuted(r2);
    CPPUNIT_ASSERT(hr2->getRecordExecuted()->getName() != hr->getRecordExecuted()->getName());

}
