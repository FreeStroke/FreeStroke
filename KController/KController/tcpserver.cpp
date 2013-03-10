#include "stdafx.h"
#include "tcpserver.h"


/*!
 *\file tcpserver.cpp
 *\author Bruce
 *\brief contains a tcp server
 *\date 2013-02-14
 */

#if defined WIN32
    TcpServer::TcpServer(Kinect* pKinect, atomic_bool* pRespondToClient, atomic_bool* pStop, atomic_ushort* pPort, HWND *pHwnd)
        :ServerUtils(pRespondToClient, pStop, pPort)
{
    this->hwnd = pHwnd;
#else
    TcpServer::TcpServer(Kinect* pKinect, atomic_bool* pRespondToClient, atomic_bool* pStop, atomic_ushort* pPort)
        :ServerUtils(pRespondToClient, pStop, pPort)
{
#endif
    KUtils::mustntBeNull(pKinect);
    kinect = pKinect;
}

TcpServer::~TcpServer(void)
{
}


void TcpServer::initSrv()
{
	ServerUtils::initSrv();
    oldPort = port->load();
	sockt = socket(AF_INET, SOCK_STREAM, 0);	
	if (sockt == INVALID_SOCKET)
	{
        fprintf(stderr, "Could not create socket.\n");
        #if defined WIN32
            WSACleanup();
        #endif
		throw SOCKET_ERROR;
    }
    /*int on = 1;
    checkSkt(setsockopt( sockt, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) ), "Reuse TCP socket");
    */
    checkSkt(bind(sockt, (struct sockaddr *)&serverInfo, sizeof(struct sockaddr_in)),"Could not bind TCP socket.\n");
    checkSkt(listen(sockt, MAX_CLIENTS), "Could not liten socket.\n");
    //logger = new Logger("logTcpServer.txt");
	logger = new Logger("tcpServer");
}

void TcpServer::run()
{
    socklen_t crecsize = sizeof(struct sockaddr_in);
    while(!stopLoop->load())
    {
        csock = 0;
        try
        {
            csock = accept(sockt, (SOCKADDR*)&serverInfo, &crecsize);
        }
        catch (int x)
        {
			logger->log(x, EXCEPTION);
            break;
        }
        respondToClient->store(false);
        bool keepSending = initSecuredConnection();
		logger->log("key exchange succesfully ",INFO);
        #if defined WIN32
            SendMessage(*(this->hwnd), WM_COMMAND, CHANGE_STATE, State::CONNECTED);
        #endif
		while (keepSending)
        {
			const char* msg = kinect->getData();
            logger->log("receve msg from kinect = ", INFO, false);
            int length = FormatAndCryptMsg(msg);
            //logger->log(msg,0);
            logger->log("  length ",INFO, false);
            logger->log(length,INFO );
            if (length > 20)
            {
                keepSending = dataSend(csock, (char *) bufferO, length);
                if (!keepSending)
                {
					logger->log("socket disconnect",WARNING);
                }
			}
			else
			{
                saveBinaryInt((char* )bufferO, 0);                 
                keepSending = dataSend(csock, (char *) bufferO, 2);
				if (!keepSending)
                {
                    logger->log("socket disconnect",WARNING);
				}
            }
            changePort(keepSending);
            logger->log("",0);
        }
        logger->log("telling udp to accept new client",INFO);
        #if defined WIN32
			SendMessage(*(this->hwnd), WM_COMMAND, CHANGE_STATE, State::WAITING);
        #endif
        respondToClient->store(true);
        logger->log("client disconnect",INFO);
		closesocket(csock);
    }
    logger->log("shutting server dow",0);
}

/*
 ***************************************************
 *  Network Methods  (private/protected)
 *****************************************************
 */

void TcpServer::changePort(bool& keepSending)
{
    if (port->load() != oldPort)
    {
        logger->log("changePort",0);
        saveBinaryInt((char *)&bufferO, 1);
        saveBinaryInt((char *) &(bufferO[2]), (int) port->load());
        send(csock, (char *) bufferO, 4, 0);
        closesocket(csock);
        oldPort=port->load();
        keepSending = false;
    }
}


bool TcpServer::initSecuredConnection()
{
	//Diffie-Hellman
	int bytes_received = recv(csock, (char *) bufferI, BUFFER_SIZE,0);
	if (bytes_received != 24)
    {
	   return false;
    }
	long long g,m,A,B,K;
	g = loadBinaryLong(bufferI);
	m = loadBinaryLong(&(bufferI[8]));
	A = loadBinaryLong(&(bufferI[16]));
	DH.CreateRecipientInterKey(B,g,m);
	saveBinaryLong((char *) bufferO, B);
	if (send(csock, (char *) bufferO, 8, 0) != 8)
    {
		return false;
    }
	DH.CreateRecipientEncryptionKey(K,A);    

	//AES
	unsigned char cryptedKey[32];
	unsigned char key[32];
	unsigned char keyRow[8];
	saveBinaryLong((char *) keyRow, K);
	srand((unsigned int) K);
    unsigned int r = rand();
    for(int i = 0; i < 32; i++)
    {
		key[i] = (r << 16) ^ rand();
		cryptedKey[i] = keyRow[4+i%4]^key[i];
	}
	if (send(csock,(char*) cryptedKey, 32, 0) != 32)
    {
		return false;
    }
	aes.MakeKey((char*) key, AES::sm_chain0, 32, 16);
	return true;
}

int TcpServer::FormatAndCryptMsg(const char * pMsg)
{
	if (pMsg == NULL)
    {
        return 0;
    }
	unsigned short length = strlen(pMsg);
	if ((!length) || ((length + 2) > BUFFER_SIZE))
    {
		return 0;
    }
	int sizeModulo = length + ((16-(length%16))%16);
	saveBinaryInt((char*)bufferO, length);		
	memset(bufferI, 0, sizeModulo + 1);
    #if defined WIN32
        strcpy_s((char *) &bufferI[0], sizeModulo + 1, pMsg);
    #else
        strcpy((char *) &bufferI[0], pMsg);
    #endif
    aes.Encrypt((char*)bufferI, (char*)(bufferO +2), sizeModulo,AES::ECB);
    return sizeModulo + 2;
}

bool TcpServer::dataSend(int csock, char* buff, int length)
{
    int sended;
   /* try
    {*/
        sended = send(csock, buff, length, 0);
    /*}
    catch (int x)
    {
        return false;
    }*/
    if (sended < length)
    {
        KUtils::sleep(100);
    }
    logger->log(sended,3);
    logger->log(" sended",0);
    return (sended != -1);
}
