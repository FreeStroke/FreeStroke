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
/*!
 * \file controller.h
 * \author Adrien Madouasse
 * \brief Describe a controller
 * \date 2013-02-14
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtCore>

/*!
 * \class Controller
 * \brief The Controller class contains information of a controller
 */
class Controller
{
public :
    /*!
     * \brief The constructor, initialize attributes
     * \param pIpAddr The IP address of the controller
     * \param pPort The TCP port of the controller
     * \param pName The name of the controller
     */
    Controller(QString pIpAddr, unsigned short pPort, QString pName);

    /*!
     * \brief Retrieve the IP address of the controller
     * \return The IP addres
     */
    QString getIpAddr();

    /*!
     * \brief Retrieve the TCP port of the controller
     * \return The TCP port
     */
    unsigned short getPort();

    /*!
     * \brief Retrieve the name of the controller
     * \return The name
     */
    QString getName();

private :
    /*!< The IP address of the controller */
    QString ipAddr;
    /*!< The TCP port of the controller */
    unsigned short port;
    /*!< The name of the controller */
    QString name;
};

#endif // CONTROLLER_H
