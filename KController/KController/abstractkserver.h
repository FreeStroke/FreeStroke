#pragma once
/*!
 *\file absractkserver.h
 *\author Bruce
 *\brief contains a udp and tcp server
 *\date 2013-02-14
 */

#include "serverutils.h"
#include "udpserver.h"
#include "tcpserver.h"

/*!
 * \brief The AbsractKserverKServer class launch udp and tcp server in two thread
 * it's an abstract class using tcpserver and udpserver class
 */
class AbstractKServer
{
public:
    AbstractKServer(){}
	
    /*!
     * \brief AbsractKServer initialisation, instanciate a tcp and udp server
     * \param pName KController's name
     * \param pPortUdp udp port where UdpServer listen (47371 by default)
     * \param pPortTcp the tcp port where KController listen (47371 by default)
     */
	AbstractKServer(string* pName, unsigned short pPortUdp = DEFAULT_PORT, unsigned short pPortTcp = DEFAULT_PORT);
	~AbstractKServer(void);

    /*!
     * \brief AbsractKServer initialisation, instanciate a tcp and udp server
     * \param pName KController's name
     * \param pPortUdp udp port where UdpServer listen (47371 by default)
     * \param pPortTcp the tcp port where KController listen (47371 by default)
     */
	void init(string* pName, unsigned short pPortUdp = DEFAULT_PORT, unsigned short pPortTcp = DEFAULT_PORT);

    /*!
     * \brief change port
	 * \param pPortTcp the new port for tcp server
	 * \param pPortUdp the new port for udp server
     */
	void changePort(unsigned short pPortTcp, unsigned short pPortUdp = DEFAULT_PORT);

    /*!
     * \brief stop the two servers
     */
	void stop();
	
	/*!
     * \brief run launch the two servers
     */
    void start();

	/*!
     * \brief runTcp launch Tcp server
     */
	virtual void runTcp() = 0;

	/*!
     * \brief runUdp launch Udp server
     */
	virtual void runUdp() = 0;
	
	/*!
     * \brief createTcp create a Tcp server
     */
	virtual void createTcp() =0;

protected :

	/*!< KController's name*/
	string* name;
	/*!< Tcp server of the KController*/
	TcpServer* TcpSrv;
	/*!< Udp Server of the KController*/
    UdpServer* UdpSrv;
	/*!< bool indicating if udpserver shall answer or not*/
    atomic_bool respond; 
	/*!< bools to stop udp and tcp server*/
    atomic_bool stopUdp, stopTcp;
	/*!< ports on which udp and tcp server are bind*/
    atomic_ushort portUdp, portTcp;

	/*!<the logger*/
    Logger* logger;
};

