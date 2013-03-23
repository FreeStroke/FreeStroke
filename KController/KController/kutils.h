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
#pragma once
#if defined QT_CREATOR_ENV
	#if defined WIN32
		#include <windows.h>
	#else
    #define ERROR_BAD_ARGUMENTS -3
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>

	#endif
#endif


/*!
 *\file kutils.h
 *\author Bruce
 *\brief contains utils method
 *\date 2013-02-14
 */

/*!
 * \brief The Utils class contains utils methods
 */
class KUtils
{
public:
	/*!
	 * \brief a secured malloc : abort if out of memory
	 * \param pSize the size of memory to malloc
	 */
	static void* securedMalloc(int pSize);

	/*!
	 * \brief test if pointer is null;
	 */
	static void mustntBeNull(void* pPtr);
	static void mustntBeNull(const void* pPtr);

    /*!
     * \brief mysleep multiplatforme sleep
     * \param x time to sleep in millisecond
     */
    static void sleep(int x);

    KUtils(void);
    ~KUtils(void);
};

