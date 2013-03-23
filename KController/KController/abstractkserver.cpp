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
#include "abstractkserver.h"


/*!
 *\file absractkserver.cpp
 *\author Bruce
 *\brief contains a udp and tcp server
 *\date 2013-02-14
 */

AbstractKServer::AbstractKServer(string* pName, unsigned short pPortTcp, unsigned short pPortUdp)
{
	init(pName, pPortTcp, pPortUdp);
}


AbstractKServer::~AbstractKServer(void)
{
    stop();
	delete TcpSrv;
	delete UdpSrv;
}

void AbstractKServer::init(string* pName, unsigned short pPortTcp, unsigned short pPortUdp)
{
    KUtils::mustntBeNull(pName);
    name = pName;
	logger = new Logger("KController ");
    portUdp.store(pPortUdp);
    portTcp.store(pPortTcp);
    stopUdp.store(true);
	stopTcp.store(true);
    respond.store(true);
	createTcp();
    UdpSrv = new UdpServer(&respond, &stopUdp, name, &portTcp, &portUdp);
}

void AbstractKServer::stop()
{
	if (!stopUdp.load() && !stopTcp.load())
	{
		stopUdp.store(true);
		stopTcp.store(true);
		KUtils::sleep(700);
		TcpSrv->closeSkt();
		KUtils::sleep(350);
		UdpSrv->closeSkt();
	}
}

void AbstractKServer::start()
{
    if (stopUdp &&	stopTcp)
    {
        TcpSrv->initSrv();
        UdpSrv->initSrv();
        runTcp();
        runUdp();
    }
}


void AbstractKServer::changePort(unsigned short pPortTcp, unsigned short pPortUdp)
{
    if (pPortTcp != portTcp.load())
	{
		portTcp.store(pPortTcp);
		stopTcp.store(true);
		if (pPortUdp != portUdp.load())
        {
			logger->log("Changing port Tcp and Udp",INFO, false);
			stopUdp.store(true);
            portUdp.store(pPortUdp);
            KUtils::sleep(300);
            TcpSrv->closeSkt();
            KUtils::sleep(750);
            UdpSrv->closeSkt();
            start();
		}
		else
        {
			logger->log("Changing port Tcp and Udp",INFO, false);
            KUtils::sleep(300);
			TcpSrv->closeSkt();
            TcpSrv->initSrv();
			runTcp();
		}
	}
	else
	{
		if (pPortUdp != portUdp.load())
        {
			logger->log("Changing port Udp",INFO, false);
			stopUdp.store(true);
			portUdp.store(pPortUdp);
            KUtils::sleep(1100);
			UdpSrv->initSrv();
			runUdp();
		}
	}
    logger->log(" --> Change ended",INFO);
}
