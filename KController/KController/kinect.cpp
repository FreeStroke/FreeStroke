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
#include "kinect.h"
#include <sstream>


/*!
 *\file kinect.cpp
 *\author Bruce
 *\brief handle the kinect
 *\date 2013-02-20
 */

Kinect::Kinect()
{
	this->initialized = false;
}


#if defined KINECT

Kinect::~Kinect()
{
	this->close();
}

void Kinect::close()
{
	if (skeletonStream && ( skeletonStream != INVALID_HANDLE_VALUE ))
    {
        CloseHandle(skeletonStream);
        skeletonStream = NULL;
    }
    if (sensor != NULL)
    {
		SafeRelease(sensor);
    }
	this->initialized = false;
}

bool Kinect::init()
{
	this->initialized = false;

    // Get a working kinect sensor
    int numSensors;
    if (!SUCCEEDED(NuiGetSensorCount(&numSensors)) || numSensors < 1) 
	{
		return false;
	}
    if (!SUCCEEDED(NuiCreateSensorByIndex(0, &sensor)))
	{
		return false;
	}

	if (sensor == NULL)
	{
		return false;
	}
	
    // Initialize sensor
    if (SUCCEEDED(sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON)))
    {
		// Create an event that will be signaled when skeleton data is available
        skeletonStream = CreateEventW(NULL, TRUE, FALSE, NULL);

		this->initialized = SUCCEEDED(sensor->NuiSkeletonTrackingEnable(skeletonStream, 0));

        // Open a skeleton stream to receive skeleton data
		return this->initialized;
    }
	return false;
}

const char* Kinect::getData()
{
	// Wait for 0ms, just quickly test if it is time to process a skeleton
    if ( WAIT_OBJECT_0 == WaitForSingleObject(skeletonStream, 500) )
    {
		NUI_SKELETON_FRAME skeletonFrame = { 0 };

        // Get the skeleton frame that is ready
        if (SUCCEEDED(sensor->NuiSkeletonGetNextFrame(0, &skeletonFrame)))
        {
            // Process the skeleton frame
			string skeletons = "";
			for (int i = 0; i < NUI_SKELETON_COUNT; i++)
			{
				const NUI_SKELETON_DATA & skeleton = skeletonFrame.SkeletonData[i];
 
				switch (skeleton.eTrackingState)
				{
				case NUI_SKELETON_TRACKED:
					{
					ostringstream sT;
					sT << clock();
					skeletons.append(sT.str());
					skeletons.append(" ");

					// Joints x y z x y z x y z ...
					for(int j = 0; j < 20; j++)
					{
						if (skeleton.eSkeletonPositionTrackingState[corres[j]] == NUI_SKELETON_POSITION_NOT_TRACKED)
						{
							return NULL;
						}
						ostringstream sX;
						sX.precision(std::numeric_limits<double>::digits10);
						sX << skeleton.SkeletonPositions[corres[j]].x;
						skeletons.append(sX.str());
						skeletons.append(" ");

						std::ostringstream sY;
						sY.precision(std::numeric_limits<double>::digits10);
						sY << skeleton.SkeletonPositions[corres[j]].y;
						skeletons.append(sY.str());
						skeletons.append(" ");

						std::ostringstream sZ;
						sZ.precision(std::numeric_limits<double>::digits10);
						sZ << skeleton.SkeletonPositions[corres[j]].z;
						skeletons.append(sZ.str());
						skeletons.append(" ");
					}
					break;
					}
				}
			}
			char* skeleton = (char*)KUtils::securedMalloc(skeletons.length() + 1);
			strcpy_s(skeleton, skeletons.length() + 1, skeletons.c_str());
			return skeleton;
        }
	}
	return NULL;
}

bool Kinect::isInitialized()
{
	return initialized;
}

#else

Kinect::~Kinect()
{
    source->close();
}

bool Kinect::init()
{
    i = 0;
    #if defined QT_CREATOR_ENV
        source = new ifstream("../../../../../KController/KController/defaultKController.txt",  ios::in);
    #else
        source = new ifstream("defaultKController.txt",  ios::in);
    #endif
	return (source->is_open());
}

const char* Kinect::getData()
{
    KUtils::sleep(100);
    getline((*source), line);
	if (i++ > 400)
	{
		i = 0;
        source->seekg(ios_base::beg);
	}
    return line.c_str();
}
#endif
