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
