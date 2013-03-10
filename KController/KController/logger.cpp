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
