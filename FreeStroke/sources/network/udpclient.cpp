#include "../../includes/network/udpclient.h"

/*!
 * \file udpclient.cpp
 * \author Adrien Madouasse
 * \brief UDP communication with a controller
 * \date 2013-02-12
 */
#include <QtCore/QDebug>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QUdpSocket>

#include "../../includes/common/utils.h"
#include "../../includes/common/controller.h"

UdpClientListener::UdpClientListener(QUdpSocket *pSocket, quint16 pPort, void *pParent)
{
    this->socketReader = pSocket;
    this->parent = pParent;

    // Prepare for read
    connect(this->socketReader, SIGNAL(readyRead()), this, SLOT(treatResponse()));
    connect((QObject*)this->parent, SIGNAL(stopUdpListening()), this, SLOT(stopListening()));
    this->socketReader->bind(pPort);
}

void UdpClientListener::treatResponse()
{
    char buf[MAX_SIZE_BUFFER_UDP];
    QHostAddress addr;
    quint16 p;
    this->socketReader->readDatagram(buf, MAX_SIZE_BUFFER_UDP, &addr, &p);

    // Type of message
    short type = (short)buf[0];

    if (type == 1)
    {
        // TCP port
        quint16 tcpPort = 0;
        tcpPort += buf[2] & 0x00FF;
        tcpPort += buf[1] << 8;

        QString name(buf+3);

        // Add the found controller to the list
        Controller *ctrl = new Controller(addr.toString(), tcpPort, name);
        UdpClient *udpClient = static_cast<UdpClient*>(this->parent);
        udpClient->addController(ctrl);
    }
}

void UdpClientListener::stopListening()
{
    qDebug() << "Stop listening";
    disconnect(this->socketReader,SIGNAL(readyRead()),0,0);
    disconnect((QObject*)this->parent, SIGNAL(stopUdpListening()), 0, 0);
    this->socketReader->close();
    this->socketReader = NULL;
    this->terminate();
}

UdpClient::UdpClient(QString pIpAddr, quint16 pPort, quint16 pBindPort)
{
    this->ipAddr = pIpAddr;
    this->port = pPort;
    this->bindPort = pBindPort;
    this->socket = new QUdpSocket(this);
    this->listen = new UdpClientListener(this->socket, this->bindPort, this);
}

quint16 UdpClient::getPort()
{
    return this->port;
}

void UdpClient::setPort(quint16 pPort)
{
    this->port = pPort;
}

quint16 UdpClient::getBindPort()
{
    return this->bindPort;
}

void UdpClient::setBindPort(quint16 pBindPort)
{
    this->bindPort = pBindPort;
}

void UdpClient::addController(Controller *pController)
{
    if (!this->contains(pController))
    {
        qDebug() << pController->getName();
        qDebug() << pController->getIpAddr();
        qDebug() << pController->getPort();
        this->controllers->append(pController);
    }
}

bool UdpClient::contains(Controller *pController)
{
    foreach (Controller *controller, *this->controllers)
    {
        if (pController->getName().compare(controller->getName()) == 0 && pController->getIpAddr().compare(controller->getIpAddr()) == 0
                && pController->getPort() == controller->getPort())
        {
            return true;
        }
    }
    return false;
}

void UdpClient::sendDiscover(QList<Controller*> *pControllers)
{
    this->controllers = pControllers;

    // Launch the thread
    this->listen->start();

    char type[1];
    type[0] = 0;

    // Build multicast address
    QHostAddress addr(this->ipAddr);

    // Send the datagram on all valid interfaces
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface inter, interfaces)
    {
        if (inter.IsUp && inter.isValid()
                && (inter.flags() & QNetworkInterface::CanMulticast) == QNetworkInterface::CanMulticast)
        {
            socket->setMulticastInterface(inter);

            // Send the datagram on the multicast address
            if (this->socket->writeDatagram(type, 1, addr, this->port) == -1)
            {
                qDebug() << "Error while sending datagram to controllers";
            }
        }
    }
}

void UdpClient::closeConnection()
{
    if (this->listen != NULL && this->listen->isRunning())
    {
        emit this->stopUdpListening();
        // Wait actively but it's ok ;)
        while(this->listen->isRunning()) {}
        delete this->listen;
        delete this->socket;
        this->listen = NULL;
        this->socket = NULL;
    }
}
