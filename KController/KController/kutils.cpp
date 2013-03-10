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
