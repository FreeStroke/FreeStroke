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
#include "kutils.h"

/*!
 *\file kutils.cpp
 *\author Bruce
 *\brief contains utils method
 *\date 2013-02-14
 */

void* KUtils::securedMalloc(int pSize)
{
	void* ret = malloc(pSize);
	if (!ret)
	{
		abort();
	}
	return ret;
}

void KUtils::mustntBeNull(void* pPtr)
{
	if(!pPtr)
	{
		fprintf(stderr, "null pointer \n");
		throw ERROR_BAD_ARGUMENTS;
	}
}

void KUtils::mustntBeNull(const void* pPtr)
{
	mustntBeNull((void*) pPtr);
}

void KUtils::sleep(int x)
{
    #if defined WIN32
        Sleep(x);
    #else
        usleep(1000 * x);
    #endif
}

KUtils::KUtils(void)
{
}


KUtils::~KUtils(void)
{
}
