#pragma once

#include "resource.h"

/*!
 * \brief A callback to handle the Kinect state change
 * \param hrStatus The status of the Kinect
 * \param instanceName The name
 * \param uniqueDeviceName The device name
 * \param pUserData Pointer to user data
 */
void CALLBACK statusProc(HRESULT pHrStatus, const OLECHAR* pInstanceName, const OLECHAR* pUniqueDeviceName, void* pUserData);

/*!
 * \brief Save the configuration in a file. The format
 */
void saveConf();

/*!
 * \brief Load the configuration from the  file.
 */
void loadConf();