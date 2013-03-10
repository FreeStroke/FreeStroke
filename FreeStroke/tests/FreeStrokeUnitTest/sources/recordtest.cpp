#include "../includes/recordtest.h"
#include "../../includes/common/gesture.h"
#include "../../includes/daolayer/record.h"

#include <QtCore/QDate>
RecordTest::RecordTest(std::string name) : CppUnit::TestCase(name) {}

void RecordTest::runTest()
{
    QString name = QString("testRecord");
    QList<Gesture*> *gestList = new QList<Gesture*>();
    QList<Gesture*> *gestList2 = new QList<Gesture*>();
    gestList->append(Gesture::fromFile("others/clap.log"));
    Command *c = new Command("CTRL  Q", KEYSTROKE);
    Command *c2 = new Command("CTRL  R", KEYSTROKE);
    Record *r = new Record(name, gestList, c);
    r->setName("plop");
    r->setCreationDate(QDate().currentDate().addDays(2).toString("yyyy-MM-dd"));
    r->setCommand(c2);
    r->setGestures(gestList2);
    r->setGestureActive(false);
    CPPUNIT_ASSERT(r->getName().compare("plop") == 0);
    CPPUNIT_ASSERT(r->getCreationDate().compare(QDate().currentDate().addDays(2).toString("yyyy-MM-dd")) == 0);
    CPPUNIT_ASSERT(r->getCommand()->getDefinition().compare(c2->getDefinition()) == 0);
    CPPUNIT_ASSERT(r->getCommand()->getType() == c2->getType());
    CPPUNIT_ASSERT(!r->isGestureActive());


}
