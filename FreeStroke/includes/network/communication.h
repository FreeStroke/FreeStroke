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
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/*!
 * \file communication.h
 * \author Adrien Madouasse
 * \brief Complete communication between FreeStroke and a controller
 * \date 2013-02-14
 */

#include "../../includes/common/controller.h"
#include "../../includes/network/tcpclient.h"
#include "../../includes/network/udpclient.h"
#include "../../includes/ui/stepper/steppercontroller.h"

/*!
 * \class Communication
 * \brief The Communication class allows the communication between FreeStroke and a controller
 */
class Communication : public QThread
{
    Q_OBJECT

public :
    /*!
     * \brief The constructor, initializes the multicast address and the UDP port
     * \param pMulticastAddr The multicast address to find controllers
     * \param pUdpPort The UDP port to find controllers
     */
    Communication(QString pMulticastAddr, quint16 pUdpPort, quint16 pUdpRespPort);

    /*!
     * \brief Modify the multicast address to find controllers
     * \param pMulticastAddr The multicast address to find controllers
     */
    void setMulticastAddr(QString pMulticastAddr);

    /*!
     * \brief Modify the UDP port for multicast
     * \param pUdpPort The new port
     */
    void setUdpPort(quint16 pUdpPort);

    /*!
     * \brief Modify the UDP bind port for multicast
     * \param pUdpBindPort The new port
     */
    void setUdpBindPort(quint16 pUdpBindPort);

    /*!
     * \brief Permit to launch udp discover
     */
    void setStepper(StepperController *pStepper);

    /*!
     * \brief Get the current controller
     * \return the current controller
     */
    Controller* getController();

    /*!
     * \brief Close the communication
     */
    void close();

    /*!
     * \brief Check if the TCP socket is connected to a controller
     * \return true if the socket is connected
     */
    bool isConnectedToController();

public slots :
    /*!
     * \brief Initializes the TCP communication, it exchanges keys with
     *        Diffie-Hellman algorithm for AES
     * \param pController The controller to connect with
     */
    void initTcpCommunication(Controller *pController);

    /*!
     * \brief Send an UDP message to discover controller
     */
    void sendUdpDiscover(QList<Controller*> *controllers);

    /*!
     * \brief Stop the UDP listening to find controllers
     */
    void stopUdpDiscover();

private slots :
    /*!
     * \brief Catch the signal which warns that the TCP connection has been refused
     */
    void catchTcpConnectionRefused();

    /*!
     * \brief Catch the signal which warns that the TCP connection has been established
     */
    void catchTcpConnectionEstablished();

    /*!
     * \brief Catch the signal which warns that the TCP connection has been closed
     */
    void catchTcpConnectionClosed();

signals :
    /*!
     * \brief Warn that the discover is over
     */
    void stopDiscover();

    /*!
     *\brief Signal to warn that the TCP connection is refused
     */
    void tcpConnectionRefused();

    /*!
     *\brief Signal to warn that the TCP connection is established
     */
    void tcpConnectionEstablished();

    /*!
     * \brief Signal to warn that the TCP connection is closed
     */
    void tcpConnectionClosed();

private :
    /*!< The multicast address to find controllers */
    QString multicastAddr;
    /*!< The UDP port to find controllers */
    quint16 udpPort;
    /*!< The UDP port where controllers respond */
    quint16 udpBindPort;
    /*!< The chosen controller */
    Controller *controller;
    /*!< The UDP socket */
    UdpClient *udp;
    /*!< The TCP socket */
    TcpClient *tcpClient;
    /*!< The list of controller */
    QList<Controller*> *controllers;
};

#endif // COMMUNICATION_H
