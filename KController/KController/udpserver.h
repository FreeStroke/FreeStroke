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

/*!
 *\file udpserver.h
 *\author Bruce
 *\brief contains a udp server
 *\date 2013-02-14
 */
#include "serverutils.h"

using namespace std;
#define GROUP "224.11.2.13"

/*!
 * \brief The UdpServer class implements an udp server that receve multicast request. Used by KControllerServer
 *          And send KController name and port.
 */
class UdpServer : public ServerUtils
{
public:
    /*!
     * \brief UdpServer build a UdpServer
     * \param pRespondToClient the pointer to the atomic boolean that say if it should respond or not
     * \param pStop shoul the server stop?
     * \param pName KController's name
     * \param pPort udp port where UdpServer listen
     * \param pPortTcp the tcp port where KController listen
     */
	UdpServer(atomic_bool* pRespondToClient, atomic_bool* pStop, string* pName, atomic_ushort* pPortTcp, atomic_ushort* pPort);
	~UdpServer();

    /*!
     * \brief Listen contains the server main loop
     */
    void run();

    /*!
     * \brief initSrv init the server
     */
    void initSrv();

private:
    string* name;
    atomic_ushort* portTcp;
    struct ip_mreq imr;
};

