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
