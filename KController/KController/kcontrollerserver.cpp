#include "stdafx.h"
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