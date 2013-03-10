#ifndef XMLCONF_H
#define XMLCONF_H

/*!
 * \file xmlconf.h
 * \author Anthony Fourneau
 * \brief configuration of the application
 * \date 2013-02-12
 */

#include "../common/controller.h"

/*!
 * \class XmlConf
 * \brief The class manage the configuration of the application
 */
class XmlConf
{
public :
    /*!
     * \brief constructor
     *
     * The constructor add default values for params
     */
    XmlConf();

    bool firstLaunch; /*!< true if it is the first time that the application is launch, permit to launch the tuto if at true */
    unsigned short tcpPort; /*!< the tcp port for the connection with the controller. It must be between 0 and 65535 */
    unsigned short udpPort; /*!< the udp port of the controller */
    unsigned short udpBindPort; /*!< the udp port for listen */
    QString multicastIp; /*!< the multicast ip for send controller discover */
    QString language; /*!< the language of the application. it can be French or English */
    Controller *controller; /*!<  the configuration of the controller : name, ip and port*/
};

#endif // XMLCONF_H
