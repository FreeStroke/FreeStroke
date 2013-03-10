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

