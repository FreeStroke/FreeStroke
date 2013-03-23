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
#pragma once

using namespace std;
/*!
 *\file serverutils.h
 *\author Bruce
 *\brief contains utils methods for server
 *\date 2013-02-14
 */
#if defined WIN32
	#include <winsock2.h>
	#include <ws2ipdef.h>
	#include <ws2tcpip.h>
#else
    #include <stropts.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
    typedef struct in_addr IN_ADDR;
#endif
#if defined QT_CREATOR_ENV
    #include <QThread>
#endif
#include "kutils.h"
#include "kinect.h"
#include <stdlib.h>
#include <atomic>
#include <signal.h>

#define BUFFER_SIZE 2048
#define DEFAULT_PORT 47371
/*!
 * \brief Socket utils contains methods for socket server
 */
#ifndef QT_CREATOR_ENV
    class ServerUtils
#else
    class ServerUtils : public QThread
#endif
{
public:
	
    /*!
     * \brief SocketUtils instanciate the windows context to use socket
     * \param pRespondToClient the pointer to the atomic boolean that will say if the udp server should respond or not
     * \param pStop shoul the server stop?
	 * \param port the port where the server listen
	 */
	ServerUtils(atomic_bool* pRespondToClient, atomic_bool* pStop, atomic_ushort* port);

	/*!
     * \brief ~SocketUtils close socket and windows context
	 */
	~ServerUtils();
	
    /*!
     * \brief run run a server
     */
    virtual void run() = 0;



    /*!
     * \brief initSrv init the server
     */
    void initSrv();

    /*!
     * \brief closeSkt close the server socket
     */
    void closeSkt();

protected:

	/*!
     * \brief check socket error
	 * \param pX returned value of the socket
	 * \param pStr the message to be displayed if error
	 * \param pY the expected returned value
	 */
	void checkSkt(int pX, const char* pStr, int pY = 0);

	/*!
     * \brief check if pPort is between 0 and 65535
	 * \param pPort the checked port
	 */
	void checkPort(int pPort);

		
	/*!
     * \brief convert a binary arry to long
	 * \param pStr the array where the int is stored
	 */
	long long loadBinaryLong(unsigned char* pStr);
	
	/*!
     * \brief convert an int to binary arry of 2 byte
	 * \param pStr the arry where the int is stored
	 * \param pX the int to store
	 */
	void saveBinaryInt(char* pStr,int pX);

	/*!
     * \brief convert an long to binary arry of 4 bytes
	 * \param pStr the arry where the int is stored
	 * \param pX the int to store
	 */
	void saveBinaryLong(char* pStr,long long pX);

#if defined WIN32
    WSADATA w;							// Used to open windows connection
#endif
    SOCKET sockt;							// Socket descriptor of server
    struct sockaddr_in serverInfo;			// Information about the server
    atomic_bool* respondToClient;
    atomic_bool* stopLoop;
	atomic_ushort* port;
};

