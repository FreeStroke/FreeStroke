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
#include "../../includes/gestures/executionmanager.h"
#include "../../includes/daolayer/daolayer.h"

#include <QtCore/QDebug>

#include <math.h>

ExecutionManager::ExecutionManager()
{
    this->segmenter = new Segmenter();
    this->lra = new LogisticRegressionAlgorithm(this);
}

void ExecutionManager::run()
{
    exec();
}

void ExecutionManager::startRecognizer()
{
    this->startWithRole(RECOGNIZER);
}

void ExecutionManager::startRecorder()
{
    this->startWithRole(RECORDER);
}

void ExecutionManager::endTraining()
{
    emit this->trainingEnded();
    this->startWithRole(RECOGNIZER);
}

void ExecutionManager::startTraining()
{
    DAOLayer *daoLayer = DAOLayer::getInstance();
    if (daoLayer == NULL)
    {
        return;
    }

    this->standby();

    QList<Record*> *records = daoLayer->getRecords();
    QHash<Record*, QList<InputGesture*> *> *trainingData = new QHash<Record*, QList<InputGesture*> *>();
    for(int i = 0; i < records->count(); i++)
    {
        Record *r = records->at(i);
        if (r->isDeleted())
        {
            continue;
        }
        qDebug() << "train with gesture : " << r->getName();
        QList<InputGesture*> *g = new QList<InputGesture*>();
        for(int j = 0; j < r->getGestures()->count(); j++)
        {
            //qDebug() << "add gesture : " << r->getGestures()->at(j)->toString()<<"\n\n";
            g->append(InputGesture::fromGesture(r->getGestures()->at(j)));
        }
        trainingData->insert(r, g);
    }


    // Train algorithm
    this->lra->train(trainingData);
}

void ExecutionManager::startWithRole(Role pRole)
{
    switch(pRole)
    {
    case INACTIVE:
        this->segmenter->setRole(S_INACTIVE);
        break;
    case RECORDER:
        this->segmenter->setRole(S_RECORDER);
        break;
    case RECOGNIZER:
        this->segmenter->setRole(S_RECOGNIZER);
        break;
    }
    this->segmenter->clear();
    DAOLayer *daoLayer = DAOLayer::getInstance();
    if(daoLayer != NULL)
    {
        QObject::connect(daoLayer, SIGNAL(skeletonDataReceived(QString)), this, SLOT(newSkeletonData(QString)));
    }
    this->role = pRole;
}

void ExecutionManager::newSkeletonData(QString pData)
{
    if(this->role == INACTIVE)
    {
        return;
    }
    DAOLayer *daoLayer = DAOLayer::getInstance();
    if(daoLayer != NULL)
    {
        RawJointState * rjs = RawJointState::fromInputLine(pData);
        if(rjs == NULL)
        {
            qDebug() << "rjs is NULL";
            return;
        }
        if (rjs->jointsCount < SkeletonData::leftPelvis)
        {
            delete rjs;
            qDebug() << "rjs is NULL";
            return;
        }
        if(this->segmenter->addState(rjs))
        {
            InputGesture *ig = this->segmenter->getLastInputGesture();
            QList<QPair<Record*, double>* >* results = this->lra->recognizeSingleGesture(ig);
            if(results == NULL)
            {
                qDebug() << "results are NULL";
                return;
            }
            switch(role)
            {
            case RECORDER:
            {
                Gesture *g = InputGesture::toGesture(ig);
                // TODO MANAGE CONFLICT
                /*if (results->count() > 0 && results->first()->second > 0.8f)
                {
                    qDebug()<<"Conflict with "<<results->first()->first->getName()<<" at "<<results->first()->second;
                    emit this->gestureConflict(g);
                }
                else*/
                {
                    qDebug()<<"Nb frames "<<g->getFrames()->count();
                    emit this->gestureRecorded(g);
                }
                break;
            }
            case RECOGNIZER:
                qDebug("-----------------------------");
                for(int i=0; i<results->count(); i++)
                {
                    if (results->at(i)->first == NULL)
                    {
                        continue;
                    }
                    qDebug()<< results->at(i)->first->getName()<< " "<< results->at(i)->second;
                }
                qDebug("-----------------------------");

                // Compute threshold
                float thresh = pow(0.9f, results->count());
                /*if(thresh < 0.45f)
                {
                    thresh = 0.45f;
                }*/
                qDebug()<<"Thresh "<<thresh;

                // Consider recognized
                DAOLayer *daoLayer = DAOLayer::getInstance();
                if (daoLayer != NULL && results->count() > 0 && results->first()->second > thresh)
                {
                    Record *r = daoLayer->getSingleRecord(results->first()->first->getId());
                    if(r != NULL && r->isGestureActive() && !r->isDeleted())
                    {
                        qDebug("Recognize with : %f", results->first()->second);
                        daoLayer->gestureRecognized(r);
                    }
                }
                break;
            }
            // qDebug()<<"Clear segmenter";
            this->segmenter->clear();
            delete results;
        }
    }
}

Role ExecutionManager::getRole()
{
    return this->role;
}

void ExecutionManager::standby()
{
    this->role = INACTIVE;
    this->segmenter->setRole(S_INACTIVE);
    DAOLayer *daoLayer = DAOLayer::getInstance();
    if(daoLayer != NULL)
    {
        QObject::disconnect(daoLayer, SIGNAL(skeletonDataReceived(QString)), this, 0);
    }
}



