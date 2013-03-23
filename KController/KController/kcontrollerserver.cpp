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
 * Copyright (C) 2010 Université Paris-Est Marne-la-Vallée 
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
 *
 */
#include "kcontrollerserver.h"

DWORD WINAPI Tcp(LPVOID lpParameter)
{
	TcpServer* Srv = reinterpret_cast<class TcpServer *>(lpParameter);
	Srv->run();
	return 0;
}

DWORD WINAPI Udp(LPVOID lpParameter)
{
	UdpServer* Srv = reinterpret_cast<class UdpServer *>(lpParameter);
	Srv->run();
	return 0;
}
 
KControllerServer::KControllerServer()
{
}



KControllerServer::~KControllerServer(void)
{
}

void KControllerServer::init(string* pName, HWND *pHwnd, Kinect* pKinect, unsigned short pPortUdp, unsigned short pPortTcp)
{
	this->hwnd = pHwnd;
	this->kinect = pKinect;
	AbstractKServer::init(pName, pPortTcp, pPortUdp);
}

void KControllerServer::runUdp()
{
	UdpHdl = CreateThread(NULL,0,Udp,UdpSrv,0,&UdpId);
}
	
void KControllerServer::runTcp()
{
	TcpHdl = CreateThread(NULL,0,Tcp,TcpSrv,0,&TcpId);
}
	
void KControllerServer::createTcp()
{
	TcpSrv = new TcpServer(kinect, &respond, &stopTcp, &portTcp, hwnd);
}

void KControllerServer::changePort(unsigned short pPortTcp, unsigned short pPortUdp)
{
	AbstractKServer::changePort(pPortTcp, pPortUdp);
}

void KControllerServer::start()
{
	AbstractKServer::start();
	SendMessage((*hwnd), WM_COMMAND, CHANGE_STATE, State::WAITING);
}

void KControllerServer::stop()
{
	AbstractKServer::stop();
	SendMessage((*hwnd), WM_COMMAND, CHANGE_STATE, State::DISCONNECTED);
}