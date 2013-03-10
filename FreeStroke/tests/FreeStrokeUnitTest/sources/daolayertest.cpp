#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include "../../includes/daolayer/daolayer.h"
#include "../includes/daolayertest.h"
#include "../../includes/common/utils.h"

DAOLayerTest::DAOLayerTest(std::string name) : CppUnit::TestCase(name) {}

void DAOLayerTest::runTest()
{
    //initialyze DB
    qDebug() << "Remove previous DB " << QFile::remove(Utils::getDatabaseLocation());
    //static method
    qDebug() << "gestureToCharTest";
    this->gestureToCharTest();
    qDebug() << "gestureFromCharTest";
    this->gestureFromCharTest();
    qDebug() << "gesturesToCharTest";
    this->gesturesToCharTest();
    qDebug() << "gesturesFromCharTest";
    this->gesturesFromCharTest();
    qDebug() << "openTest";
    this->openTest();
    qDebug() << "closeTest";
    //   this->closeTest();

    //member method
    qDebug() << "insertTest";
    this->insertTest();
    qDebug() << "updateTest";
    this->updateTest();
    qDebug() << "getTest";
    this->getTest();
    qDebug() << "deleteTest";
    this->deleteTest();
    qDebug() << "deleteExtendTest";
    this->deleteExtendTest();

    qDebug() << "insertHistoryTest";
    this->insertHistoryTest();
    qDebug() << "getHistoryTest";
    this->getHistoryTest();
    qDebug() << "deleteHistoryTest";
    this->deleteHistoryTest();
    qDebug() << "deleteExtendHistoryTest";
    this->deleteExtendHistoryTest();

    qDebug() << "insertNeutralGesture";
    this->insertNeutralGesture();
    qDebug() << "getNeutralGesture";
    this->getNeutralGesture();
    qDebug() << "deleteNeutralGesture";
    this->deleteNeutralGesture();

//    qDebug() << "failTest";
//    this->failTest();
}

void DAOLayerTest::openTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    DAOLayer * daoLayer2 = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer == daoLayer2);
}

void DAOLayerTest::closeTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    delete daoLayer;
    CPPUNIT_ASSERT(daoLayer == NULL);
}

void DAOLayerTest::gestureToCharTest()
{
    const char * refGestureChar = "1 1 1000 1 1 1 ";

    QList<SkeletonData*> * frames = new QList<SkeletonData*>();
    QList<Vector3> * jointures = new QList<Vector3>();
    Vector3 *vector = new Vector3(1.0f,1.0f,1.0f);
    jointures->append(*vector);
    SkeletonData * skelData = new SkeletonData(jointures,1000);
    frames->append(skelData);
    Gesture * gesture = new Gesture(frames);

    const char * gestureChar = DAOLayer::gestureToChar(gesture);
    CPPUNIT_ASSERT(strcmp(gestureChar,refGestureChar) == 0);
    CPPUNIT_ASSERT(DAOLayer::gestureToChar(NULL) == NULL);
}

void DAOLayerTest::gestureFromCharTest()
{
    const char * refGestureChar = "1 1 1000 1 1 1 ";
    const char * refGestureChar2 = "1 1 1000 1 1 1 1";
    CPPUNIT_ASSERT(strcmp(refGestureChar,DAOLayer::gestureToChar(DAOLayer::gestureFromChar(refGestureChar))) == 0);
    CPPUNIT_ASSERT( NULL == DAOLayer::gestureFromChar(""));
    CPPUNIT_ASSERT( NULL == DAOLayer::gestureFromChar(refGestureChar2));
    CPPUNIT_ASSERT(DAOLayer::gestureFromChar(NULL) == NULL);
}


void DAOLayerTest::gesturesToCharTest()
{
    const char * refGestureChar = "1 1 1 1000 1 1 1 ";
    QList<SkeletonData*> * frames = new QList<SkeletonData*>();
    QList<Vector3> * jointures = new QList<Vector3>();
    Vector3 *vector = new Vector3(1.0f,1.0f,1.0f);
    jointures->append(*vector);
    SkeletonData * skelData = new SkeletonData(jointures,1000);
    frames->append(skelData);
    Gesture * gesture = new Gesture(frames);
    QList<Gesture *> * gestures = new QList<Gesture *> ();
    gestures->append(gesture);

    const char * gestureChar = DAOLayer::gesturesToChar(gestures);
    CPPUNIT_ASSERT(strcmp(gestureChar,refGestureChar) == 0);
}

void DAOLayerTest::gesturesFromCharTest()
{
    const char * refGestureChar = "1 1 1 1000 1 1 1 ";
    const char * refGestureChar2 = "1 1 1 1000 1 1 1 1";
    CPPUNIT_ASSERT(strcmp(refGestureChar,DAOLayer::gesturesToChar(DAOLayer::gesturesFromChar(refGestureChar))) == 0);
    CPPUNIT_ASSERT( NULL == DAOLayer::gesturesFromChar(""));
    CPPUNIT_ASSERT( NULL == DAOLayer::gesturesFromChar(refGestureChar2));
}


void DAOLayerTest::insertTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    int res;
    QList<Record *> * records = daoLayer->getRecords();
    int init = records->count();

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

    res = daoLayer->addRecord(record);
    CPPUNIT_ASSERT(res == 0);

    records = daoLayer->getRecords();
    CPPUNIT_ASSERT(records->count() == init+1);
    CPPUNIT_ASSERT(daoLayer->addRecord(NULL) == 1);
}

void DAOLayerTest::updateTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    int res;
    QList<Record *> * records = daoLayer->getRecords();
    int init = records->count();

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
    record->setCommandActive(0);
    record->setId(1);
    res = daoLayer->updateRecord(record);
    CPPUNIT_ASSERT(res == 0);

    records = daoLayer->getRecords();
    init = records->count();
    Record  *rSave = NULL;
    for (int i = 0 ; i < init ; i++)
    {
        Record *r = records->at(i);
        if(r->getId() == 1)
        {
            rSave = r;
        }
    }

    CPPUNIT_ASSERT(rSave->getId() == 1);
    CPPUNIT_ASSERT(strcmp(rSave->getName(),"MyTestRecord2") == 0);
    command = rSave->getCommand();
    CPPUNIT_ASSERT(strcmp(command->getDefinition().toLocal8Bit().data(),"toto") == 0);
    CPPUNIT_ASSERT(command->getType() == KEYSTROKE );
    CPPUNIT_ASSERT(rSave->isCommandActive() == 0);
    CPPUNIT_ASSERT(rSave->isGestureActive() == 1);
    CPPUNIT_ASSERT(rSave->isDeleted() == 0);
    CPPUNIT_ASSERT(!rSave->getCreationDate().isEmpty());
    CPPUNIT_ASSERT(strcmp(DAOLayer::gesturesToChar(rSave->getGestures()),"1 1 1 1000 0 0 0 ") == 0);
    CPPUNIT_ASSERT(records->count() == init);
    CPPUNIT_ASSERT(daoLayer->updateRecord(NULL) == 1);
}

void DAOLayerTest::deleteTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    int res;
    QList<Record *> * records = daoLayer->getRecords();
    int init = records->count();

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
    record->setId(1);
    res = daoLayer->removeRecord(record);
    CPPUNIT_ASSERT(res == 0);

    records = daoLayer->getRecords();
    CPPUNIT_ASSERT(records->count() == init-1);
    CPPUNIT_ASSERT(daoLayer->removeRecord(NULL) == 1);
}


void DAOLayerTest::deleteExtendTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    int res;
    const int id = 2;
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
    record->setId(id);
    res = daoLayer->addRecord(record);
    CPPUNIT_ASSERT(res == 0);

    QList<Record *> * records = daoLayer->getRecords();
    int init = records->count();

    QString date = "aujourd'hui";
    HistoryRecord * hr = new HistoryRecord(id,record,date);
    res = daoLayer->addHistoryRecord(hr);
    CPPUNIT_ASSERT(res == 0);

    res = daoLayer->removeRecord(record);
    CPPUNIT_ASSERT(res == 0);

    records = daoLayer->getRecords();
    CPPUNIT_ASSERT(records->count() == init);

    for(int i = 0 ; i < records->count() ; i++)
    {
        Record *r = records->at(i);
        if(r->getId() == id)
        {
            CPPUNIT_ASSERT(r->isDeleted() == 1);
        }
        else
        {
            CPPUNIT_ASSERT(r->isDeleted() == 0);
        }
    }
}


void DAOLayerTest::getTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);
    QList<Record *> * records = daoLayer->getRecords();
    int init = records->count();
    Record  *rSave = NULL;
    for (int i = 0 ; i < init ; i++)
    {
        Record *r = records->at(i);
        if(r->getId() == 1)
        {
            rSave = r;
        }
    }

    Record * singRec = daoLayer->getSingleRecord(1);
    CPPUNIT_ASSERT(singRec != NULL);
    CPPUNIT_ASSERT(singRec->getId() == 1);


    CPPUNIT_ASSERT(rSave->getId() == 1);
    CPPUNIT_ASSERT(strcmp(rSave->getName(),"MyTestRecord2") == 0);
    Command * command = rSave->getCommand();
    CPPUNIT_ASSERT(strcmp(command->getDefinition().toLocal8Bit().data(),"toto") == 0);
    CPPUNIT_ASSERT(command->getType() == KEYSTROKE );
    CPPUNIT_ASSERT(rSave->isCommandActive() == 0);
    CPPUNIT_ASSERT(rSave->isGestureActive() == 1);
    CPPUNIT_ASSERT(rSave->isDeleted() == 0);
    CPPUNIT_ASSERT(!rSave->getCreationDate().isEmpty());
    CPPUNIT_ASSERT(strcmp(DAOLayer::gesturesToChar(rSave->getGestures()),"1 1 1 1000 0 0 0 ") == 0);

    records = daoLayer->getRecords();
    CPPUNIT_ASSERT(records->count() == init);

    CPPUNIT_ASSERT(daoLayer->getSingleRecord(-1) == NULL);
}

void DAOLayerTest::insertHistoryTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    QList<HistoryRecord *> * hrecords = daoLayer->getHistoryRecords();
    int init = hrecords->count();

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
    record->setId(2);
    daoLayer->addRecord(record);
    QString date = "aujourd'hui";
    HistoryRecord * hr = new HistoryRecord(1,record,date);
    int res = daoLayer->addHistoryRecord(hr);
    CPPUNIT_ASSERT(res == 0);

    hrecords = daoLayer->getHistoryRecords();
    CPPUNIT_ASSERT(hrecords->count() == init+1);
}

void DAOLayerTest::getHistoryTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    QList<HistoryRecord *> * hrecords = daoLayer->getHistoryRecords();
    int init = hrecords->count();

    hrecords = daoLayer->getHistoryRecords();
    CPPUNIT_ASSERT(hrecords->count() == init);
}


void DAOLayerTest::deleteHistoryTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    int res = daoLayer->removeHistoryRecord();
    CPPUNIT_ASSERT(res == 0);

    QList<HistoryRecord *> * hrecords = daoLayer->getHistoryRecords();
    CPPUNIT_ASSERT(hrecords->isEmpty());
}


void DAOLayerTest::deleteExtendHistoryTest()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    //for clean prvious test
    daoLayer->removeHistoryRecord();

    int res;
    const int id = 3;
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
    record->setId(id);
    res = daoLayer->addRecord(record);
    CPPUNIT_ASSERT(res == 0);

    QList<Record *> * records = daoLayer->getRecords();
    int init = records->count();

    QString date = "aujourd'hui";
    HistoryRecord * hr = new HistoryRecord(id,record,date);
    res = daoLayer->addHistoryRecord(hr);
    CPPUNIT_ASSERT(res == 0);

    res = daoLayer->removeRecord(record);
    CPPUNIT_ASSERT(res == 0);

    records = daoLayer->getRecords();
    CPPUNIT_ASSERT(records->count() == init);

    for(int i = 0 ; i < records->count() ; i++)
    {
        Record  *r = records->at(i);
        if(r->getId() == id)
        {
            CPPUNIT_ASSERT(r->isDeleted() == 1);
        }
        else
        {
            CPPUNIT_ASSERT(r->isDeleted() == 0);
        }
    }

    daoLayer->removeHistoryRecord();
    records = daoLayer->getRecords();
    CPPUNIT_ASSERT(records->count() == init-1);

    for(int i = 0 ; i < records->count() ; i++)
    {
        Record  *r = records->at(i);
        if(r->getId() == id)
        {
            //this record should not exist anymore
            CPPUNIT_ASSERT(false);
        }
        else
        {
            CPPUNIT_ASSERT(r->isDeleted() == 0);
        }
    }
}

void DAOLayerTest::insertNeutralGesture()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    int res;
    QList<Gesture *> * gestures = daoLayer->getNeutralGestures();
    int init = gestures->count();

    QList<SkeletonData*> * frames = new QList<SkeletonData*>();
    QList<Vector3> * jointures = new QList<Vector3>();
    Vector3 *vector = new Vector3(1.0f,1.0f,1.0f);
    jointures->append(*vector);
    SkeletonData * skelData = new SkeletonData(jointures,1000);
    frames->append(skelData);
    Gesture * gesture = new Gesture(frames);
    res = daoLayer->addNeutralGesture(gesture);
    CPPUNIT_ASSERT(res == 0);

    gestures = daoLayer->getNeutralGestures();
    CPPUNIT_ASSERT(init+1 == gestures->count());
    CPPUNIT_ASSERT(daoLayer->addNeutralGesture(NULL) == 1);

}

void DAOLayerTest::getNeutralGesture()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    QList<Gesture *> * gestures = daoLayer->getNeutralGestures();

    int init = gestures->count();
    Gesture *gest = gestures->at(0);

    CPPUNIT_ASSERT(strcmp(DAOLayer::gestureToChar(gest), "1 1 1000 1 1 1 ") == 0);

    gestures = daoLayer->getNeutralGestures();
    CPPUNIT_ASSERT(init == gestures->count());
}

void DAOLayerTest::deleteNeutralGesture()
{
    DAOLayer * daoLayer = DAOLayer::getInstance();
    CPPUNIT_ASSERT(daoLayer != NULL);

    int res = daoLayer->removeNeutralGesture();
    CPPUNIT_ASSERT(res == 0);

    QList<Gesture *> *gestures = daoLayer->getNeutralGestures();
    CPPUNIT_ASSERT(0 == gestures->count());
}

//void DAOLayerTest::failTest()
//{
//    DAOLayer * daoLayer = DAOLayer::getInstance();

//    daoLayer->close();

//    QList<SkeletonData*> * frames = new QList<SkeletonData*>();
//    QList<Vector3> * jointures = new QList<Vector3>();
//    Vector3 *vector = new Vector3();
//    jointures->append(*vector);
//    SkeletonData * skelData = new SkeletonData(jointures,1000);
//    frames->append(skelData);
//    Gesture * gesture = new Gesture(frames);
//    Command * command = new Command("toto", KEYSTROKE);
//    QList<Gesture *> * gestures = new QList<Gesture *>();
//    gestures->append(gesture);
//    Record * record = new Record("MyTestRecord2",gestures,command);

//    QString date = "aujourd'hui";
//    HistoryRecord * hr = new HistoryRecord(1,record,date);

//    CPPUNIT_ASSERT(daoLayer->addRecord(record) == 1);
//    CPPUNIT_ASSERT(daoLayer->getRecords() == NULL);
//    CPPUNIT_ASSERT(daoLayer->getSingleRecord(1) == NULL);
//    CPPUNIT_ASSERT(daoLayer->removeRecord(record) == 1);
//    CPPUNIT_ASSERT(daoLayer->updateRecord(record) == 1);
//    CPPUNIT_ASSERT(daoLayer->addHistoryRecord(hr) == 1);
//    CPPUNIT_ASSERT(daoLayer->removeHistoryRecord() == 1);
//    CPPUNIT_ASSERT(daoLayer->getHistoryRecords() == NULL);
//    CPPUNIT_ASSERT(daoLayer->addNeutralGesture(gesture) == 1);
//    CPPUNIT_ASSERT(daoLayer->getNeutralGestures() == NULL);
//    CPPUNIT_ASSERT(daoLayer->removeNeutralGesture() == 1);
//}
