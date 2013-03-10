#include "../includes/keytest.h"

#include <QtCore/QDebug>

KeyTest::KeyTest(std::string name) : CppUnit::TestCase(name) {}

void KeyTest::runTest()
{
    CPPUNIT_ASSERT(KeyConverter::keyFromText("A") == Qt::Key_A);
    CPPUNIT_ASSERT(KeyConverter::textFromKey(Qt::Key_A) == "A");

    CPPUNIT_ASSERT(KeyConverter::keyFromText("Shift") == Qt::Key_Shift);
    CPPUNIT_ASSERT(KeyConverter::textFromKey(Qt::Key_Shift) == "Shift");

    CPPUNIT_ASSERT(KeyConverter::keyFromText("Ctrl") == Qt::Key_Control);
    CPPUNIT_ASSERT(KeyConverter::textFromKey(Qt::Key_Control) == "Ctrl");

    CPPUNIT_ASSERT(KeyConverter::keyFromText(QString::fromUtf8("À")) == Qt::Key_Agrave);
    CPPUNIT_ASSERT(KeyConverter::textFromKey(Qt::Key_Agrave) == QString::fromUtf8("À"));

    bool shift = false;
    bool ctrl = false;
    bool meta = false;
    bool alt = false;
    bool altgr = false;
    int key = 0;

    CPPUNIT_ASSERT(KeyConverter::fromText(QString::fromUtf8("Shift\tAlt\tCtrl\tAltGr\tMeta\tA"), &key, &shift, &ctrl, &alt, &meta, &altgr));
    CPPUNIT_ASSERT(shift == true);
    CPPUNIT_ASSERT(ctrl == true);
    CPPUNIT_ASSERT(alt == true);
    CPPUNIT_ASSERT(altgr == true);
    CPPUNIT_ASSERT(meta == true);
    CPPUNIT_ASSERT(key == Qt::Key_A);
}
