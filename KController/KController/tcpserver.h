#pragma once

/*!
 *\file tcpserver.h
 *\author Bruce
 *\brief contains a tcp server
 *\date 2013-02-14
 */

#include <ctime>
#include <string.h>
#include "serverutils.h"
#include "logger.h"
#include "kinect.h"

#ifndef UNITTEST
    #include "DiffieHellman.h"
    #include "aes.h"
#else
    #include "../../../sources/network/diffiehellman.h"
    #include "../../../sources/network/aes.h"
#endif
#ifndef QT_CREATOR_ENV
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <stdio.h>
#endif
#define MAX_CLIENTS 2
#if defined WIN32 && defined KINECT
    #include <NuiApi.h>
    #define KINECT_ERROR -2
#endif

/*!
 * \brief The TcpServer class implements a tcp server that will send kinect data to the only connected client.
 */
class TcpServer: public ServerUtils
{
public:
    /*!
     * \brief TcpServer build a TcpServer used by KControllerServer
	 * \param pKinect the kinect sending data to the server
	 * \param pRespond the pointer to the atomic boolean that will say if the udp server should respond or not
     * \param pStop shoul the server stop?
     * \param pPort tcp port where UdpServer listen
     */
    #if defined WIN32
        TcpServer(Kinect* pKinect, atomic_bool* pRespond, atomic_bool* pStop, atomic_ushort* pPort, HWND *pHwnd);
    #else
        TcpServer(Kinect* pKinect, atomic_bool* pRespond, atomic_bool* pStop, atomic_ushort* pPort);
    #endif
    ~TcpServer();

    /*!
     * \brief Listen contains the server main loop
     */
    void run();

    /*!
     * \brief initSrv init the server
     */
    void initSrv();

	/*
	 ***************************************************
	 *  Network Methods 
	 *****************************************************
	 */
protected:

	/*!
	 * \brief bind the server to a new port (use bindPort);
     * \parma keepSending the bool used by server's loop to say if it must keep sending data to a connected client
	 */
    void changePort(bool&   keepSending);

private:

	/*!
     * \brief Format and crypt message
	 * \param pMsg the address of the message to format
	 * \return the lengt of the formated message
     */
    int FormatAndCryptMsg(const char* pMsg);

	/*!
     * \brief Call by listen to instantiate a secured connection AES & Diffie-Hellman
	 * \return if the connection sucessfully connected
     */
    bool initSecuredConnection();

    /*!
     * \brief dataSend dataSending with errors protection
     * \param csock the socket to use for sending
     * \param buffer the data to send
     * \param length length of the data to send
     * \return if the send was succesfull
     */
    bool dataSend(int csock, char* buff, int length);

/*
 ***************************************************
 *  Kinect Methods  
 ***************************************************
 */
#if defined WIN32
	/*!< Window's UI handler usedo to notify connection*/
    HWND *hwnd;
#endif
	
	/*!< Reception buffer */
	unsigned char bufferI[BUFFER_SIZE];
	/*!< Emission buffer */
	unsigned char bufferO[BUFFER_SIZE];

	/*!< conected client's socket*/
	int csock;

	/*!< string used to format data send back to a client*/
	string* answer;

	/*!<the logger*/
    Logger* logger;

	/*!< kinect handler*/ 
	Kinect* kinect;

	/*!< port which server socket was bind too*/
	unsigned short oldPort;

	/*!< class to use diffihelman authentification*/
	CDiffieHellman DH;
	/*!< classe to crypt with aes*/
    AES aes;
};
