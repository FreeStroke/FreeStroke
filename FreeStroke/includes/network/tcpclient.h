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
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

/*!
 * \file tcpclient.h
 * \author Adrien Madouasse
 * \brief TCP communication with a controller
 * \date 2013-02-13
 */

#include <QtNetwork>

#include "../../includes/daolayer/daolayer.h"
#include "../../includes/network/aes.h"
#include "../../includes/network/diffiehellman.h"

#define AES_KEY_SIZE 32
#define BUFF_SIZE 256
#define MAX_BUFF_SIZE 2048
#define AES_BLOCK_SIZE 16


/*!
 * \class TcpClient
 * \brief The TcpSocket class allow to communication with a controller
 *        to exchange skelton data
 */
class TcpClient : public QObject
{
    Q_OBJECT

public :
    /*!
     * \brief The constructor, initialize the IP address to communicate with
     * \param pIpAdress The IP address of the controller
     * \param pPort The TCP port
     */
    TcpClient(QString pIpAdress, quint16 pPort);

    /*!
     * \brief The destructor
     */
    ~TcpClient();

    /*!
     * \brief Retrieve the port
     * \return The TCP port
     */
    quint16 getPort();

    /*!
     * \brief Modify the TCP port
     * \param pPort The new port
     */
    void setPort(quint16 pPort);

    /*!
     * \brief Send a TCP message
     * \param pData The message to send
     * \param pSize The size of the data
     */
    void send(unsigned char *pData, int pSize);

    /*!
     * \brief Close the TCP connection
     */
    void closeConnection();

    /*!
     * \brief The state of the connection
     * \return true if the socket is connected to a controller
     */
    bool isConnected();

signals :
    /*!
     *\brief Signal to warn that the TCP connection is refused
     */
    void connectionRefused();

    /*!
     *\brief Signal to warn that the TCP connection is established
     */
    void connectionEstablished();

    /*!
     * \brief Signal to warn that the TCP connection is closed
     */
    void connectionClosed();

public slots :
    /*!
     * \brief Connect the TCP socket to the controller
     */
    void connection();

    /*!
     * \brief Produce and send data for Diffie-Hellman
     */
    void sendDH();

private slots :
    /*!
     * \brief Receive Diffie-Hellman data (B) from the controller
     */
    void receiveDH();

    /*!
     * \brief Receive AES key from the controller
     */
    void receiveAesKey();

    /*!
     * \brief Receive data from the controller
     */
    void receive();

    /*!
     * \brief Launch when the socket has been connected to a controller
     */
    void socketConnected();

    /*!
     * \brief Launch when the socket has been disconnected, it closes it
     */
    void socketDisconnected();

    /*!
     * \brief Launch when a socket error happened
     */
    void catchSocketError(QAbstractSocket::SocketError error);

private :
    /*!< The IP address */
    QString ipAddress;
    /*!< The TCP port */
    quint16 port;
    /*!< The TCP socket */
    QTcpSocket *socket;
    /*!< The Diffie-Hellman object to exchange keys */
    CDiffieHellman *diffieSend;
    /*!< Encryption key for AES */
    unsigned char *aesKey;
    /*!< AES object to encrypt and decrypt */
    AES aes;
    /*!< The number of bytes waited for reading */
    quint16 waitedSize;
    /*!< The Model */
    DAOLayer *dao;
    /*!< The state of the connection */
    bool connected;
    /*!< It is changing the port */
    bool changingPort;

    /*!
     * \brief Send the AES key to the controller
     * \param encryptionKey The Diffie Hellman key
     */
    void sendAesKey();

    /*!
     * \brief Generate the AES key to communicate with the controller
     */
    void createAesKey();

    /*!
     * \brief Transfert a long in a char array
     * \param pLong The long to transfert
     * \param pBuf The char array
     */
    void longToCharArray(qlonglong pLong, unsigned char *pBuf);

    /*!
     * \brief Apply a XOR on a buffer
     * \param pKey The key for the XOR
     * \param pData Date to encrypt
     * \param pDataSize Size of data
     * \param pEncrypt The encrypted message
     */
    void xorAesKey(unsigned char* pKey, unsigned char* pData, int pDataSize, unsigned char *pEncrypt);

    /*!
     * \brief Decrypt a message with the AES algorithm
     * \param pEncrytpted The encrypted message
     * \param pSize The size of the message
     * \param pDecrytpted A pointer for the decrypted message
     */
    void aesDecryption(unsigned char* pEncrytpted, int pSize, unsigned char* pDecrytpted);

    /*!
     * \brief Build a short (16 bits) with an array of chars
     * \param pArray The array of char to transform
     * \return The short produced
     */
    quint16 charArrayToShort(unsigned char *pArray);

};

#endif // TCPCLIENT_H
