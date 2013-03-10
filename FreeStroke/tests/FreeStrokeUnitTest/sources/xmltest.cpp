#include <QtCore/QDebug>

#include "../includes/xmltest.h"
#include "../../includes/xml/xml.h"
#include "../../includes/daolayer/command.h"
#include "../../includes/common/utils.h"
XmlTest::XmlTest(std::string name) : CppUnit::TestCase(name) {}

void XmlTest::runTest()
{
    qDebug() << "XML class test start";
    qDebug() << "Export test";
    exportTest();
    qDebug() << "Import test";
    importTest();
    qDebug() << "Export Import test";
    exportImportTest();
    qDebug() << "XML class end OK";
}


void XmlTest::exportTest()
{
    Xml *xml = new Xml();

    QList<SkeletonData*> * frames = new QList<SkeletonData*>();
    QList<Vector3> * jointures = new QList<Vector3>();
    Vector3 *vector = new Vector3();
    jointures->append(*vector);
    SkeletonData * skelData = new SkeletonData(jointures,1000);
    frames->append(skelData);
    Gesture * gesture = new Gesture(frames);
    Command * command = new Command("toto", KEYSTROKE);
    QList<Gesture *> * gestures = new QList<Gesture *>();
    gestures->append(gesture);
    Record * record = new Record("MyTestRecord2",gestures,command);
    QList<Record * > * records  = new QList<Record *>();
    records->append(record);

    xml->exportRecords(records, "exportFreestroke.xml");
    CPPUNIT_ASSERT(QFile::exists("exportFreestroke.xml"));

}

void XmlTest::importTest()
{
    Xml *xml = new Xml();
    QList<Record *> * records =xml->importRecord("exportFreestroke.xml");
    CPPUNIT_ASSERT(records != NULL);
}

void XmlTest::exportImportTest()
{
    Xml *xml = new Xml();
    QList<SkeletonData*> * frames = new QList<SkeletonData*>();
    QList<Vector3> * jointures = new QList<Vector3>();
    Vector3 *vector = new Vector3();
    jointures->append(*vector);
    SkeletonData * skelData = new SkeletonData(jointures,1000);
    frames->append(skelData);
    Gesture * gesture = new Gesture(frames);
    Command * command = new Command("toto", KEYSTROKE);
    QList<Gesture *> * gestures = new QList<Gesture *>();
    gestures->append(gesture);
    Record * record = new Record("MyTestRecord2",gestures,command);

    // Add clap.log
    Gesture * g = Gesture::fromFile(QDir::toNativeSeparators(Utils::getApplicationDirectoryRoot() + "../../tests/FreeStrokeUnitTest/others/clap.log"));
    qDebug() << QDir::toNativeSeparators(Utils::getApplicationDirectoryRoot() + "../../tests/FreeStrokeUnitTest/others/clap.log");
    if( g == NULL)
    {
        qDebug() << "generateFalseDataOnDb() - Error gesure::fromFile clap ==> NULL";
        qDebug() << "generateFalseDataOnDb() - end";
        return;
    }
    Command * command2 = new Command("Shift\t5",KEYSTROKE);

    QList<Gesture *> * gestures2 = new QList<Gesture *>();
    gestures2->append(g);
    Record *r = new Record("Ma clap commande",gestures2,command2);

    QList<Record * > * records  = new QList<Record *>();
    records->append(record);
    records->append(r);

    if(xml->exportRecords(records, "exportFreestroke.xml") == 1){
        CPPUNIT_ASSERT(1 == 0 );
    }
    QList<Record *> * recordsImp = xml->importRecord("exportFreestroke.xml");


    CPPUNIT_ASSERT(records->length() == recordsImp->length());
    for( int i = 0 ; i < records->length() ; i++)
    {
        Record *r1 = records->at(i);
        Record *r2 = recordsImp->at(i);
        CPPUNIT_ASSERT(r1->isCommandActive() == r2->isCommandActive());
        CPPUNIT_ASSERT(r1->isGestureActive() == r2->isGestureActive());
        CPPUNIT_ASSERT(r1->isDeleted() == r2->isDeleted());
        CPPUNIT_ASSERT(r1->getName().compare(r2->getName()) == 0);
        Command *c1 =r1->getCommand();
        Command *c2 = r2->getCommand();
        CPPUNIT_ASSERT(c1->getDefinition().compare(c2->getDefinition()) == 0);
        CPPUNIT_ASSERT((int)c1->getType() == (int)c2->getType());

        QList<Gesture *> * gs1 = r1->getGestures();
        QList<Gesture *> * gs2 = r2->getGestures();
        CPPUNIT_ASSERT(gs1->length() == gs2->length());
        CPPUNIT_ASSERT(gs1->length() == 1);
        Gesture * g1 = gs1->at(0);
        Gesture * g2 = gs2->at(0);
        QList<SkeletonData *> * skel1 = g1->getFrames();
        QList<SkeletonData *> * skel2 = g2->getFrames();

        CPPUNIT_ASSERT(skel1->length() == skel2->length());

        for( int j = 0 ; j < skel1->length() ; j++)
        {
            SkeletonData * s1 = skel1->at(j);
            SkeletonData * s2 = skel2->at(j);
            CPPUNIT_ASSERT(s1->getTimestamp() == s2->getTimestamp());

             QList<Vector3>* joints1 = s1->getJointures();
             QList<Vector3>* joints2 = s2->getJointures();
             CPPUNIT_ASSERT(joints1->length() == joints2->length());

             for( int k = 0; k < joints1->length() ; k++)
             {
                Vector3 v1 = joints1->at(k);
                Vector3 v2 = joints2->at(k);
                CPPUNIT_ASSERT(v1.x == v2.x);
                CPPUNIT_ASSERT(v1.y == v2.y);
                CPPUNIT_ASSERT(v1.z == v2.z);
             }
        }
    }
}
