//------------------------------------------------------------------------------
// <copyright file="stdafx.h" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

// include file for standard system and project includes

#pragma once
#ifndef QT_CREATOR_ENV
    #include "targetver.h"

    #define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

    // Windows Header Files
    #include <windows.h>
    #include <ole2.h>

    // C RunTime Header Files
    #include <stdlib.h>
    #include <malloc.h>
    #include <memory.h>
    #include <tchar.h>
    #include <iostream>
    #include <time.h>
    #include "kutils.h"

    #pragma comment ( lib, "winmm.lib" )
    #pragma comment ( lib, "d2d1.lib" )

    #ifdef _UNICODE
    #if defined _M_IX86
    #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
    #elif defined _M_X64
    #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
    #else
    #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
    #endif
    #endif

    // Safe release for interfaces
    template<class Interface>
    inline void SafeRelease( Interface *& pInterfaceToRelease )
    {
        if ( pInterfaceToRelease != NULL )
        {
            pInterfaceToRelease->Release();
            pInterfaceToRelease = NULL;
        }
    }

#endif
