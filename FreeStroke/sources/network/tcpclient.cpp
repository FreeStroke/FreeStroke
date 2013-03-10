#include "../../includes/network/tcpclient.h"

/*!
 * \file tcpclient.cpp
 * \author Adrien Madouasse
 * \brief TCP communication with a controller
 * \date 2013-02-13
 */
#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtCore/QTimer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

#include "../../includes/daolayer/daolayer.h"
#include "../../includes/network/diffiehellman.h"
#include "../../includes/network/aes.h"
#include "../../includes/common/utils.h"

TcpClient::TcpClient(QString pIpAdress, quint16 pPort)
{
    this->ipAddress = pIpAdress;
    this->port = pPort;
    this->socket = NULL;
    this->aesKey = NULL;
    this->waitedSize = 2;
    this->dao = DAOLayer::getInstance();
}

TcpClient::~TcpClient()
{
    Utils::secureFree(this->aesKey);
}

quint16 TcpClient::getPort()
{
    return this->port;
}

void TcpClient::setPort(quint16 pPort)
{
    this->port = pPort;
}

void TcpClient::socketConnected()
{
    qDebug() << "Connection established";
    this->connected = true;
    this->sendDH();
}

void TcpClient::socketDisconnected()
{
    qDebug() << "Socket disconnected, is closed : " << this->socket->isOpen();
    this->connected = false;
    qDebug() << this->socket->state();
    emit this->connectionClosed();
}

void TcpClient::catchSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error";
    qDebug() << error;
    if (error == QAbstractSocket::ConnectionRefusedError || error == QAbstractSocket::NetworkError)
    {
        this->connected = false;
        emit this->connectionRefused();
    }
    this->closeConnection();
}

bool TcpClient::isConnected()
{
    return this->connected;
}

void TcpClient::connection()
{
    Utils::secureFree(this->socket);
    this->socket = NULL;
    this->socket = new QTcpSocket();

    // Connect for read Diffie-Hellman
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(receiveDH()));

    // To manage the deconnexion of the socket
    connect(this->socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(this->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(catchSocketError(QAbstractSocket::SocketError)));

    // Connection
    QHostAddress addr(this->ipAddress);
    this->socket->connectToHost(addr,this->port);
}

void TcpClient::receiveDH()
{
    int sizeLongLong = sizeof(qlonglong);
    unsigned char buf[sizeLongLong];

    if (this->socket->read((char*)buf, sizeLongLong) != sizeLongLong)
    {
        this->socket->close();
        return;
    }

    // Retrieve the value of B from controller
    qlonglong B = 0;
    for (int i=0;i<sizeLongLong;i++)
    {
        B <<= 8;
        B += buf[i];
    }

    // Generate the Diffie-Hellman key to exchange AES key
    qlonglong encryptionKey = 0;
    this->diffieSend->CreateSenderEncryptionKey(encryptionKey, B);

    // Disconnect for read Diffie-Hellman
    disconnect(this->socket,SIGNAL(readyRead()),0,0);

    // Connect for read AES key
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(receiveAesKey()));
}

void TcpClient::receiveAesKey()
{
    unsigned char buf[AES_KEY_SIZE];
    int read;

    if ((read = this->socket->read((char*)buf, AES_KEY_SIZE)) != AES_KEY_SIZE)
    {
        this->socket->close();
        return;
    }

    this->aesKey = (unsigned char*)Utils::secureMalloc(AES_KEY_SIZE);

    // Retrieve Diffie-Hellman key
    qlonglong dhKey = 0;
    this->diffieSend->GetValue(dhKey);

    // Decrypt the AES key
    unsigned char* dhKeyChar = (unsigned char*)Utils::secureMalloc(sizeof(qlonglong));
    longToCharArray(dhKey, dhKeyChar);
    xorAesKey(dhKeyChar, buf, AES_KEY_SIZE, this->aesKey);

    // Initialize the AES algorithm
    this->aes.MakeKey((char*)this->aesKey, AES::sm_chain0, AES_KEY_SIZE, AES_BLOCK_SIZE);

    // Disconnect for read Diffie-Hellman
    disconnect(this->socket, SIGNAL(readyRead()), 0, 0);

    // Connect for read AES key
    qDebug() << "Communication initialized";
    emit this->connectionEstablished();
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(receive()));

    Utils::secureFree(dhKeyChar);
    delete this->diffieSend;
}

void TcpClient::receive()
{
    while (this->waitedSize < this->socket->bytesAvailable())
    {
        if (this->waitedSize == 2)
        {
            if (this->socket->bytesAvailable() < 2)
            {
                return;
            }
            else
            {
                unsigned char buf[2];

                if (this->socket->read((char*)buf, 2) == -1)
                {
                    qDebug()<<"Error during read size";
                    this->socket->close();
                    return;
                }

                this->waitedSize = this->charArrayToShort(buf);

                if (this->waitedSize > MAX_BUFF_SIZE)
                {
                    qDebug() << "Data too big, close the TCP socket";
                    this->socket->close();
                    return;
                }
                else if (this->waitedSize < AES_KEY_SIZE + 4)
                {
                    if (this->waitedSize == 1)
                    {
                        // Read port
                        if (this->socket->read((char*)buf, 2) == -1)
                        {
                            qDebug()<<"Error during read the port";
                            this->socket->close();
                            return;
                        }

                        qDebug() << "Old port : " << this->port;
                        // Change the port
                        this->port = this->charArrayToShort(buf);

                        qDebug() << "New port : " << this->port;

                        disconnect(this->socket, SIGNAL(readyRead()), 0, 0);
                        this->socket->close();

                        this->waitedSize = 2;

                        QTimer::singleShot(650, this, SLOT(connection()));
                        return;
                    }

                    // Packet to check the connexion
                    this->waitedSize = 2;
                }
            }
        }

        if (this->socket->bytesAvailable() >= this->waitedSize && this->waitedSize > 2)
        {
            int toRead = (AES_BLOCK_SIZE - (this->waitedSize % AES_BLOCK_SIZE)) % AES_BLOCK_SIZE + this->waitedSize;
            unsigned char buf[toRead];

            int read;
            if ((read = this->socket->read((char*)buf, toRead)) == -1)
            {
                qDebug()<<"Error during read data";
                this->socket->close();
                return;
            }

            unsigned char* decrypt = NULL;
            try
            {
                decrypt = (unsigned char*)Utils::secureMalloc(read);
                this->aesDecryption(buf, read, decrypt);

                // Send data to the model
                this->dao->dataFromCommunication(QString(QByteArray((char*)decrypt, read)));

                Utils::secureFree(decrypt);
            }
            catch (int n)
            {
                qDebug() << "Error " << n << " in decryption";
            }

            this->waitedSize = 2;
        }
    }
}

void TcpClient::send(unsigned char* pData, int pSize)
{
    this->socket->write((char*)pData, pSize);
}

void TcpClient::sendDH()
{
    this->diffieSend = new CDiffieHellman();

    // Generate shared key (generator and modulus)
    qlonglong g = 0;
    qlonglong m = 0;
    this->diffieSend->CreateKeys(g, m);

    // Generate public key for sender (A)
    qlonglong A = 0;
    if (this->diffieSend->CreateSenderInterKey(A) != 0)
    {
        qDebug() << "Error in AES initialization, in the A creation";
    }

    unsigned char *data = (unsigned char*)Utils::secureMalloc(sizeof(qlonglong)*3);
    memset(data, 0, sizeof(qlonglong)*3);

    qlonglong longs[3];
    longs[0] = g;
    longs[1] = m;
    longs[2] = A;

    // Put longs in a array of char
    for (int i=0;i<3;i++)
    {
        longToCharArray(longs[i], data+i*8);
    }

    // Send public data for Diffie-Hellman
    this->send(data, sizeof(qlonglong)*3);

    Utils::secureFree(data);
}

void TcpClient::longToCharArray(qlonglong pLong, unsigned char* pBuf)
{
    for (int i=0;i<(int)sizeof(qlonglong);i++)
    {
        pBuf[7-i] = pLong >> (8*i);
    }
}

void TcpClient::xorAesKey(unsigned char* pKey, unsigned char* pData, int pDataSize, unsigned char* pEncrypt)
{
    for (int i=0;i<pDataSize;i++)
    {
        pEncrypt[i] = pKey[i%4+4] ^ pData[i];
    }
}

void TcpClient::aesDecryption(unsigned char* pEncrytpted, int pSize, unsigned char* pDecrytpted)
{
    memset(pDecrytpted, 0, pSize);
    this->aes.Decrypt((char*)pEncrytpted, (char*)pDecrytpted, pSize, AES::ECB);
}

quint16 TcpClient::charArrayToShort(unsigned char* pArray)
{
    quint16 rShort = pArray[1] & 0x00FF;
    rShort += pArray[0] << 8;
    return rShort;
}

void TcpClient::closeConnection()
{
    if (this->socket != NULL && this->socket->isOpen())
    {
        this->socket->close();

        disconnect(this->socket, SIGNAL(readyRead()), 0, 0);
        disconnect(this->socket, SIGNAL(connected()), 0, 0);
        disconnect(this->socket, SIGNAL(disconnected()),  0, 0);
        disconnect(this->socket, SIGNAL(error(QAbstractSocket::SocketError)),  0, 0);

    }
}
