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
