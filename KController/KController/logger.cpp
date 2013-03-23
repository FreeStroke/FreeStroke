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
#include "stdafx.h"
#include "logger.h"

/*!
 *\file logger.cpp
 *\author Bruce
 *\brief a logger
 *\date 2013-02-24
 */

static std::ofstream file;

Logger::Logger(char* pPackageName, char* pFilePath)
{
/*	packageName = pPackageName;
	if (!file.is_open())
	{
		file.open (pFilePath);
	}*/
}

Logger::~Logger()
{
    file.close();
}

void Logger::log(int pMessage, int pType, bool backN)
{
    if(!file.is_open())
	{
        return;
    }
	switch (pType)
	{
	case WARNING:
		  {
			file << packageName << ": " << "WARNING" << ": " << pMessage;
              break;
		  }
	case EXCEPTION:
		  {
			file << packageName << ": " << "EXCEPTION" << ": " << pMessage;
              break;
		  }
	case ERROR:
		  {
			file << packageName << ": " << "ERROR" << ": " << pMessage;
              break;
		  }
	case INFO:
		  {
			file << packageName << ": " << pMessage;
              break;
		  }
	default:
		{
			file << packageName << ": " << pType << ": " << pMessage;
			break;
		}
	}
	if (backN)
	{
		file << "\n";
	}
	KUtils::sleep(1);
}

void Logger::log(const char* pMessage, int pType, bool backN)
{
    if(!file.is_open() || (pMessage == NULL))
	{
        return;
    }
	switch (pType)
	{
	case WARNING:
		  {
			file << packageName << ": " << "WARNING" << ": " << pMessage;
              break;
		  }
	case EXCEPTION:
		  {
			file << packageName << ": " << "EXCEPTION" << ": " << pMessage;
              break;
		  }
	case ERROR:
		  {
			file << packageName << ": " << "ERROR" << ": " << pMessage;
              break;
		  }
	case INFO:
		  {
			file << packageName << ": " << pMessage;
              break;
		  }
	default:
		{
			file << packageName << ": " << pType << ": " << pMessage;
			break;
		}
	}
	if (backN)
	{
		file << "\n";
	}
	KUtils::sleep(1);
}
