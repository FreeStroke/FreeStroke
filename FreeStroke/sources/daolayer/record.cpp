#include "../../includes/daolayer/record.h"

Record::Record(QString pName, QList<Gesture *> * pGestures, Command * pCommand)
{
    this->id = -1; // we can't set an id, the dB has to do this
    this->name = pName;
    this->creationDate = ""; // we won't manipulate date, the dB do this better
    this->gestures = pGestures;
    this->myCommand = pCommand;
    this->commandActive = 1; // Default value
    this->gestureActive = 1; // Default value
    this->deleted = 0; // Default value
}

Record::Record(int pId, QString pName, QString pCreationDate,  QList<Gesture *> *pGestures, Command * pCommand, bool pCommandActive, bool pGestureActive, bool pDeleted)
{
    this->id = pId;
    this->name = pName;
    this->creationDate = pCreationDate;
    this->gestures = pGestures;
    this->myCommand = pCommand;
    this->commandActive = pCommandActive;
    this->gestureActive = pGestureActive;
    this->deleted = pDeleted;
}

int Record::getId()
{
    return this->id;
}

QString Record::getName()
{
    return this->name;
}

QString Record::getCreationDate()
{
    return this->creationDate;
}

QList<Gesture *> * Record::getGestures()
{
    return this->gestures;
}

Command *Record::getCommand()
{
    return this->myCommand;
}

bool Record::isCommandActive()
{
    return this->commandActive;
}

bool Record::isGestureActive()
{
    return this->gestureActive;
}

bool Record::isDeleted()
{
    return this->deleted;
}

void Record::setId(int pId)
{
    this->id = pId;
}

void Record::setName(QString pName)
{
    this->name = pName;
}

void Record::setCreationDate(QString pCreationDate)
{
    this->creationDate = pCreationDate;
}

void Record::setGestures(QList<Gesture *> * pGestures)
{
    this->gestures = pGestures;
}

void Record::setCommand(Command *pCommand)
{
    this->myCommand = pCommand;
}

void Record::setCommandActive(bool pIsCommandActive)
{
    this->commandActive = pIsCommandActive;
}

void Record::setGestureActive(bool pIsGestureActive)
{
    this->gestureActive = pIsGestureActive;
}
