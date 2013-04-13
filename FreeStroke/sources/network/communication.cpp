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
#include "../../includes/network/communication.h"

/*!
 * \file communication.cpp
 * \author Adrien Madouasse
 * \brief Communication : UDP discover and secure TCP connection
 * \date 2013-02-13
 */

#include "../../includes/network/udpclient.h"
#include "../../includes/network/tcpclient.h"
#include "../../includes/ui/stepper/steppercontroller.h"

Communication::Communication(QString pMulticastAddr, quint16 pUdpPort, quint16 pudpBindPort)
{
    this->multicastAddr = pMulticastAddr;
    this->udpPort = pUdpPort;
    this->udpBindPort = pudpBindPort;
    this->udp = NULL;
    this->tcpClient = NULL;
    this->controller = NULL;
}

void Communication::setStepper(StepperController *pStepper)
{
    connect(pStepper, SIGNAL(requestDiscover(QList<Controller*>*)), this, SLOT(sendUdpDiscover(QList<Controller*>*)));
    connect(pStepper, SIGNAL(controllerChosen(Controller*)), this, SLOT(initTcpCommunication(Controller*)));
}

void Communication::setMulticastAddr(QString pMulticastAddr)
{
    this->multicastAddr = pMulticastAddr;
}

void Communication::setUdpPort(quint16 pUdpPort)
{
    this->udpPort = pUdpPort;
}

void Communication::setUdpBindPort(quint16 pUdpBindPort)
{
    this->udpBindPort = pUdpBindPort;
}

Controller* Communication::getController()
{
    return this->controller;
}

bool Communication::isConnectedToController()
{
    return this->tcpClient->isConnected();
}

void Communication::initTcpCommunication(Controller *pController)
{
    this->controller = pController;

    qDebug() << "Init TCP communication";
    qDebug() << "Connection to " << this->controller->getName() << " " << this->controller->getIpAddr() << " " << this->controller->getPort();

    this->tcpClient = new TcpClient(this->controller->getIpAddr(),this->controller->getPort());
    connect(this->tcpClient, SIGNAL(connectionRefused()), this, SLOT(catchTcpConnectionRefused()));
    connect(this->tcpClient, SIGNAL(connectionEstablished()), this, SLOT(catchTcpConnectionEstablished()));
    connect(this->tcpClient, SIGNAL(connectionClosed()), this, SLOT(catchTcpConnectionClosed()));
    this->tcpClient->connection();
}

void Communication::sendUdpDiscover(QList<Controller*> *pControllers)
{
    qDebug() << "UDP";
    this->controllers = pControllers;

    // Seek Controllers
    this->udp = new UdpClient(this->multicastAddr, this->udpPort, this->udpBindPort);
    this->udp->sendDiscover(this->controllers);

    QTimer::singleShot(1500, this, SLOT(stopUdpDiscover()));
}

void Communication::stopUdpDiscover()
{
    qDebug() << "Stop UDP";
    this->udp->closeConnection();

    qDebug() << "Nb of controllers :" << this->controllers->size();

    emit this->stopDiscover();

    this->controllers = NULL;
    delete this->udp;
    this->udp = NULL;
}

void Communication::close()
{
    if (this->udp != NULL)
    {
        this->udp->closeConnection();
    }
    if (this->tcpClient != NULL)
    {
        this->tcpClient->closeConnection();
        disconnect(this->tcpClient, SIGNAL(connectionRefused()), 0, 0);
        disconnect(this->tcpClient, SIGNAL(connectionEstablished()), 0, 0);
        disconnect(this->tcpClient, SIGNAL(connectionClosed()), 0, 0);
        this->msleep(500);
    }
}

void Communication::catchTcpConnectionRefused()
{
    qDebug() << "catchTcpConnectionRefused";
    emit this->tcpConnectionRefused();
}

void Communication::catchTcpConnectionEstablished()
{
    emit this->tcpConnectionEstablished();
}

void Communication::catchTcpConnectionClosed()
{
    qDebug() << "catchTcpConnectionClosed";
    emit this->tcpConnectionClosed();
}
