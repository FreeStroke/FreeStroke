#include "stdafx.h"
#include "serverutils.h"

/*!
 *\file serverutils.cpp
 *\author Bruce
 *\brief contains utils methods for server
 *\date 2013-02-14
 */

ServerUtils::ServerUtils(atomic_bool* pRespondToClient, atomic_bool* pStop, atomic_ushort* pPort)
{
    KUtils::mustntBeNull(pRespondToClient);
    KUtils::mustntBeNull(pStop);
    KUtils::mustntBeNull(pPort);
	checkPort(pPort->load());
    respondToClient = pRespondToClient;
    stopLoop = pStop;
	port = pPort;
	// Open windows connection
}


ServerUtils::~ServerUtils()
{
    closeSkt();
}

void ServerUtils::initSrv()
{
    #if defined WIN32
	if (WSAStartup(0x0101, &w) != 0)
	{
		fprintf(stderr, "Could not open Windows connection.\n");
		throw SOCKET_ERROR;
    }
	#else
	signal(SIGPIPE, SIG_IGN);
    #endif
	stopLoop->store(false);
	memset((void *)&serverInfo, '\0', sizeof(struct sockaddr_in));
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = htonl(INADDR_ANY); 
    serverInfo.sin_port = htons((int) port->load());
}

void ServerUtils::closeSkt()
{
    char error = 0;
    socklen_t len = sizeof (error);
    int open = !getsockopt (sockt, SOL_SOCKET, SO_ERROR, &error, &len );
    if (open)
    {
        closesocket(sockt);
		#if defined WIN32
			WSACleanup();
		#endif
    }
}

/**************************
protected
***************************/


void ServerUtils::checkSkt(int pX, const char* pStr, int pY)
{
    KUtils::mustntBeNull(pStr);
	if (pX != pY)
    {
        fprintf(stderr, "\n");
        fprintf(stderr, pStr);
		closeSkt();
		throw SOCKET_ERROR;
	}
}

void ServerUtils::checkPort(int pPort)
{
	if ((pPort < 1) || (pPort > 65535))
	{
        fprintf(stderr, "\n wrong port\n");
		throw ERROR_BAD_ARGUMENTS;
	}
}

long long ServerUtils::loadBinaryLong(unsigned char* pStr)
{	
    KUtils::mustntBeNull(pStr);
	long long ret = 0;
	for (int i = 0; i < sizeof(long long); i++)
	{
		ret <<= 8;
		ret += pStr[i];
	}
	return ret;
}

void ServerUtils::saveBinaryInt(char* pStr,int pX)
{	
    KUtils::mustntBeNull(pStr);
	pStr[0] = pX >> 8;
	pStr[1] = pX;
}

void ServerUtils::saveBinaryLong(char* pStr,long long pX)
{
    KUtils::mustntBeNull(pStr);
	for (int i = 0; i < sizeof(pX); i++)
	{
		pStr[7-i] = (char) (pX >>(8 * i));
	}
}
