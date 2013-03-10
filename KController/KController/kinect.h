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

