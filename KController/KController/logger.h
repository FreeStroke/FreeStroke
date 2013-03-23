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
#ifndef LOGGER_H
#define LOGGER_H

/*!
 *\file logger.h
 *\author Bruce
 *\brief a logger
 *\date 2013-02-24
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "kutils.h"

#define WARNING 1
#define EXCEPTION 2
#define INFO 4
#if defined QT_CREATOR_ENV
    #define ERROR 3
#endif

class Logger {
public:

    /*!
     * \brief Logger build a logger
     */
    Logger(char* pPackageName, char* pFilePat = "KControllerLog.txt");
    ~Logger() ;

    /*!
     * \brief log log data
     * \param pMessage a char* to log
     * \param pType type of log using INFO|WARNING|ERROR|EXCEXPTION
	 * \param backN add a \n at end of the line (true by default)
     */
    void log(const char* pMessage, int pType, bool backN = true);

    /*!
     * \brief log log data
     * \param pMessage an int to log
     * \param pType type of log using INFO|WARNING|ERROR|EXCEXPTION
	 * \param backN add a \n at end of the line (true by default)
     */
    void log(int pMessage, int pType, bool backN = true);
private:
	/*!< name of the package calling this logger */
	char* packageName;
};

#endif // LOGGER_H
