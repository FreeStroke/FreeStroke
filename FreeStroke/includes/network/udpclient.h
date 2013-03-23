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
#ifndef UDPCLIENT_H
#define UDPCLIENT_H

/*!
 * \file udpclient.h
 * \author Adrien Madouasse
 * \brief UDP communication with a controller
 * \date 2013-02-12
 */
#include <QtCore/QList>
#include <QtCore/QThread>
#include <QtNetwork/QUdpSocket>

#include "../common/controller.h"

#define PORT 47371
#define PORT_RESP 47372
#define MAX_SIZE_BUFFER_UDP 256
#define MULTICAST_ADDR "224.11.2.13"

/*!
 * \class UdpClientListener
 * \brief The UdpClientListener class listen the network to find controllers
 */
class UdpClientListener : public QThread
{
    Q_OBJECT

public :
    /*!
     * \brief The constructor, initialize the UDP socket with a port to listen
     * \param pPort The port to set
     */
    UdpClientListener(QUdpSocket *pSocket, quint16 pPort, void *pParent);

private slots:
    /*!
     * \brief Treat the response from a controller
     */
    void treatResponse();

    /*!
     * \brief Stop the listening of the UDP socket
     */
    void stopListening();

private :
    /*!< The port to listen with UDP */
    quint16 port;
    /*!< The UDP socket to read */
    QUdpSocket *socketReader;
    /*!< Reference to UdpClient */
    void *parent;
};

/*!
 * \class UdpClient
 * \brief The UdpClient class allow to send a discover command on the network
 *        to find controllers
 */
class UdpClient : public QObject
{
    Q_OBJECT

public :
    /*!
     * \brief The constructor, initializes the UDP socket with a port
     * \param pPort The port to set
     */
    UdpClient(QString pIpAddr, quint16 pPort, quint16 pBindPort);

    /*!
     * \brief Retrieve the port
     * \return The port associated to socket
     */
    quint16 getPort();

    /*!
     * \brief Change the port of the controller
     * \param pPort The new port
     */
    void setPort(quint16 pPort);

    /*!
     * \brief Retrieve the port to bind
     * \return The port associated to socket
     */
    quint16 getBindPort();

    /*!
     * \brief Add a controller to the list of controllers
     * \param controller The controller to add
     */
    void addController(Controller *controller);

    /*!
     * \brief Change the port bind to socket
     * \param pPort The new port
     */
    void setBindPort(quint16 pBindPort);

    /*!
     * \brief Send a discover request on the network to find a controller
     */
    void sendDiscover(QList<Controller *> *pControllers);

    /*!
     * \brief Check if the list of controllers already contains a controller
     * \param pController The controller to check
     * \return true if the controller is already in the list
     */
    bool contains(Controller *pController);

    /*!
     * \brief Close the UDP connection
     */
    void closeConnection();

signals :
    /*!
     * \brief Signal to stop UDP listening
     */
    void stopUdpListening();

private:
    /*!< The IP address on which we send */
    QString ipAddr;
    /*!< The port on which we send */
    quint16 port;
    /*!< The port which to bind */
    quint16 bindPort;
    /*!< The UDP socket */
    QUdpSocket *socket;
    /*!< List of Controller */
    QList<Controller*> *controllers;
    /*!< The Thread to listen the network */
    UdpClientListener *listen;
};

#endif // UDPCLIENT_H
