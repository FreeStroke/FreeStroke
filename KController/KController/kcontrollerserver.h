#pragma once

/*!
 *\file kcontrollerpserver.h
 *\author Bruce
 *\brief contains a udp server
 *\date 2013-02-14
 */
#ifndef QT_CREATOR_ENV
#include "abstractkserver.h"
#include "kinect.h"
#endif
/*!
 * \brief The KControllerServer class launch udp and tcpserver in two thread
 * specialisation of AbsractKserver
 */
class KControllerServer : public AbstractKServer
{
public:
	KControllerServer();
	~KControllerServer();

    /*!
     * \brief run launch the two server
     */
	void run();

	
    /*!
     * \brief KControllerServer initialisation, instanciate a tcp and udp server
     * \param pName KController's name
	 * \param pHwnd The window element
	 * \param pKinect the kinec that'll provide data to the tcpserver
     * \param pPortUdp udp port where UdpServer listen (47371 by default)
     * \param pPortTcp the tcp port where KController listen (47371 by default)
     */
	void init(string* pName, HWND *pHwnd, Kinect* pKinect, unsigned short pPortUdp = DEFAULT_PORT, unsigned short pPortTcp = DEFAULT_PORT);

	/*!
     * \brief change port
	 * \param pPortTcp the new port for tcp server
	 * \param pPortUdp the new port for udp server
     */
	void changePort(unsigned short pPortTcp, unsigned short pPortUdp);

	/*!
     * \brief run launch Tcp server
     */
	void runTcp();

	/*!
     * \brief run launch Udp server
     */
	void runUdp();

	/*!
     * \brief run create a Tcp server
     */
	void createTcp();

    /*!
     * \brief stop the two servers
     */
	void stop();
	
	/*!
     * \brief run launch the two servers
     */
    void start();

private:
	DWORD UdpId;
	DWORD TcpId;
	HANDLE UdpHdl;
	HANDLE TcpHdl;
	HWND *hwnd;
	Kinect *kinect;
};