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
#include "stdafx.h"
#include "udpserver.h"



/*!
 *\file udpserver.cpp
 *\author Bruce
 *\brief contains a udp server
 *\date 2013-02-14
 */

UdpServer::UdpServer(atomic_bool* pRespondToClient, atomic_bool* pStop , string* pName, atomic_ushort* pPortTcp, atomic_ushort* pPort)
    :ServerUtils(pRespondToClient, pStop, pPort)
{
    KUtils::mustntBeNull(pName);
    if((pName->size() > 32) || (pName->size() < 2))
	{
		fprintf(stderr, "wrong answer \n");
		throw ERROR_BAD_ARGUMENTS;
    }
    name = pName;
    portTcp = pPortTcp;
	// Open a datagram socket
}


UdpServer::~UdpServer()
{
}

void UdpServer::initSrv()
{
    ServerUtils::initSrv();
    sockt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockt == INVALID_SOCKET)
	{
		fprintf(stderr, "Could not create socket.\n");
        #if defined WIN32
            WSACleanup();
        #endif
		throw SOCKET_ERROR;
	}
	checkPort(portTcp->load());
	// Clear out serverInfo struct
	memset(&imr, 0, sizeof(struct ip_mreq));
    // Set family and port
	imr.imr_multiaddr.s_addr = inet_addr(GROUP); 
    imr.imr_interface.s_addr = htonl(INADDR_ANY);
    checkSkt(bind(sockt, (struct sockaddr *)&serverInfo, sizeof(struct sockaddr_in)),"Could not bind UDP socket.\n");
    struct timeval timeout;
    timeout.tv_sec = 1000;
    timeout.tv_usec = 0;
    // set GROUP option
    checkSkt(setsockopt(sockt, IPPROTO_IP, IP_ADD_MEMBERSHIP,(char*) &imr, sizeof(imr)),
        "setsockopt: IP_ADD_MEMBERSHIP");
    checkSkt(setsockopt(sockt, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)), " recvfrom Timeout");
}

void UdpServer::run()
{
	// Loop and get data from clients
	bool l = stopLoop->load();
    while (!stopLoop->load())
    {
        struct sockaddr_in client;
        int bytes_received;
        socklen_t client_length = (int)sizeof(struct sockaddr_in);
        char buffer[BUFFER_SIZE];
        bytes_received = recvfrom(sockt, buffer, BUFFER_SIZE,
                                  0, (struct sockaddr *)&client, &client_length);
        /*bool l = (bytes_received == 1);
        bool l2 = (buffer[0] == 0);
        bool l3 = respondToClient->load();
       // cout << l << " " << l2 << " " << l3 << " " << endl;*/
        if ((bytes_received == 1) && (buffer[0] == 0) && (respondToClient->load()))
        {
			int size_answer = 4+(int)(name->size());
            char* toSendc = (char*) KUtils::securedMalloc(size_answer);
			toSendc[0] = 1;
			saveBinaryInt(&(toSendc[1]), portTcp->load());
			#if defined WIN32
                _memccpy(&(toSendc[3]), name->c_str(), name->size() +1 ,name->size() +1 );
			#else
                memccpy(&(toSendc[3]), name->c_str(), name->size() +1 ,name->size() +1 );
			#endif
			checkSkt(sendto(sockt, toSendc, size_answer, 0, (struct sockaddr *)&client, client_length),
				"Error sending datagram.\n",
				size_answer);
			free(toSendc);
        }
	}
    closeSkt();
}
