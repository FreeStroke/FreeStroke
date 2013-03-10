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

