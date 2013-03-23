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
#ifndef QT_CREATOR_ENV
    #define KINECT 1
#endif
#include <iostream>
#include <fstream>
#if defined KINECT
    #include <NuiApi.h>
#endif

#include <string>
#include "kutils.h"

#define CHANGE_STATE 102

using namespace std;

/*!
 *\file kinect.h
 *\author Bruce
 *\brief handle the kinect
 *\date 2013-02-20
 */

static const int corres[20] = { 2, 3, 8, 9, 10, 11, 4, 5, 6, 7, 16, 17, 18, 19, 12 ,13, 14, 15, 1, 0 };

/*!
 * The states of the controller
 */
typedef enum {
	DISCONNECTED,
	WAITING,
	CONNECTED
} State;

/*!
 * \brief The Kinect class handle the kniect sdk to read data of the kinect
 * if KINECT is not defined it read data from a saved scenario
 */
class Kinect
{
public:
	Kinect();
	~Kinect();

    /*!
     * \brief Intialize Kinect connection
     */
     bool init();

    /*!
     * \brief Get Kinect skeleton
     */
    const char* getData();

	/*!
	 * \brief Get the initialization state
	 */
	bool isInitialized();

	/*!
	 * \brief Uninitialize the Kinect
	 */
	void close();

private:
	State state;
#if defined WIN32
    HWND *hwnd;
#endif
	/*!< Initialization state */
	bool initialized;

    // Kinect variables
#if defined KINECT
	// The identifier of the Kinect's RGB Camera
    HANDLE skeletonStream;
	// The kinect sensor
    INuiSensor* sensor;
#else
    string line;
    int   i;
    ifstream* source;
#endif
};

