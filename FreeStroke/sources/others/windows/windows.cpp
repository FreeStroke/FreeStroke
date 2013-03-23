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
#include "../../includes/others/windows/windows.h"

#define WINVER 0x0500
#include <windows.h>
#include <iostream>

Windows::Windows(QWidget* w)
{

}


void Windows::generateKeyEvent(unsigned short keyCode, bool shiftModifier, bool ctrlModifier, bool metaModifier, bool altModifier,  bool altGrModifier)
{
    Sleep(5000);
    INPUT * keystroke;

    UINT  characterCount = 0;
    UINT keystrokeToSend = 0;
    UINT i = 0;

    std::cout << keyCode << std::endl;
    if(keyCode != 0)
    {
        characterCount = characterCount+1;
    }
    if(shiftModifier == true)
    {
        characterCount = characterCount+1;
    }
    if(ctrlModifier == true)
    {
        characterCount = characterCount+1;
    }
    if(metaModifier == true)
    {
        characterCount = characterCount+1;
    }
    if(altModifier == true)
    {
        characterCount = characterCount+1;
    }
    if(altGrModifier == true)
    {
        characterCount = characterCount+1;
    }

    keystrokeToSend = characterCount*2;

    keystroke = new INPUT[keystrokeToSend];


    if(shiftModifier == true)
    {
        keystroke[ i ].type = INPUT_KEYBOARD;
        keystroke[ i ].ki.wVk = 0x10;
        keystroke[ i ].ki.wScan = 0;
        keystroke[ i ].ki.dwFlags = 0;
        keystroke[ i ].ki.time = 0;
        keystroke[ i ].ki.dwExtraInfo = GetMessageExtraInfo();

        keystroke[ keystrokeToSend - i - 1 ].type = INPUT_KEYBOARD;
        keystroke[ keystrokeToSend - i - 1 ].ki.wVk = 0x10;
        keystroke[ keystrokeToSend - i - 1 ].ki.wScan = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwFlags =  KEYEVENTF_KEYUP;
        keystroke[ keystrokeToSend - i - 1 ].ki.time = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwExtraInfo = GetMessageExtraInfo();
        i = i + 1;
    }
    if(ctrlModifier == true)
    {
        keystroke[ i ].type = INPUT_KEYBOARD;
        keystroke[ i ].ki.wVk = 0x11;
        keystroke[ i ].ki.wScan = 0;
        keystroke[ i ].ki.dwFlags = 0;
        keystroke[ i ].ki.time = 0;
        keystroke[ i ].ki.dwExtraInfo = GetMessageExtraInfo();

        keystroke[ keystrokeToSend - i - 1 ].type = INPUT_KEYBOARD;
        keystroke[ keystrokeToSend - i - 1 ].ki.wVk = 0x11;
        keystroke[ keystrokeToSend - i - 1 ].ki.wScan = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwFlags =  KEYEVENTF_KEYUP;
        keystroke[ keystrokeToSend - i - 1 ].ki.time = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwExtraInfo = GetMessageExtraInfo();
        i = i + 1;
    }
    if(metaModifier == true)
    {
        keystroke[ i ].type = INPUT_KEYBOARD;
        keystroke[ i ].ki.wVk = 0x5B;
        keystroke[ i ].ki.wScan = 0;
        keystroke[ i ].ki.dwFlags = 0;
        keystroke[ i ].ki.time = 0;
        keystroke[ i ].ki.dwExtraInfo = GetMessageExtraInfo();

        keystroke[ keystrokeToSend - i - 1 ].type = INPUT_KEYBOARD;
        keystroke[ keystrokeToSend - i - 1 ].ki.wVk = 0x10;
        keystroke[ keystrokeToSend - i - 1 ].ki.wScan = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwFlags =  KEYEVENTF_KEYUP;
        keystroke[ keystrokeToSend - i - 1 ].ki.time = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwExtraInfo = GetMessageExtraInfo();
        i = i + 1;
    }
    if(altModifier == true)
    {
        keystroke[ i ].type = INPUT_KEYBOARD;
        keystroke[ i ].ki.wVk = 0x12;
        keystroke[ i ].ki.wScan = 0;
        keystroke[ i ].ki.dwFlags = 0;
        keystroke[ i ].ki.time = 0;
        keystroke[ i ].ki.dwExtraInfo = GetMessageExtraInfo();

        keystroke[ keystrokeToSend - i - 1 ].type = INPUT_KEYBOARD;
        keystroke[ keystrokeToSend - i - 1 ].ki.wVk = 0x12;
        keystroke[ keystrokeToSend - i - 1 ].ki.wScan = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwFlags =  KEYEVENTF_KEYUP;
        keystroke[ keystrokeToSend - i - 1 ].ki.time = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwExtraInfo = GetMessageExtraInfo();
        i = i + 1;
    }
    if(altGrModifier == true)
    {
        // Alt Gr seems to act like Alt on windows
        keystroke[ i ].type = INPUT_KEYBOARD;
        keystroke[ i ].ki.wVk = 0x12;
        keystroke[ i ].ki.wScan = 0;
        keystroke[ i ].ki.dwFlags = 0;
        keystroke[ i ].ki.time = 0;
        keystroke[ i ].ki.dwExtraInfo = GetMessageExtraInfo();

        keystroke[ keystrokeToSend - i - 1 ].type = INPUT_KEYBOARD;
        keystroke[ keystrokeToSend - i - 1 ].ki.wVk = 0x12;
        keystroke[ keystrokeToSend - i - 1 ].ki.wScan = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwFlags =  KEYEVENTF_KEYUP;
        keystroke[ keystrokeToSend - i - 1 ].ki.time = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwExtraInfo = GetMessageExtraInfo();
        i = i + 1;
    }
    if(keyCode != 0)
    {
        std::cout << keyCode << std::endl;
        keystroke[ i ].type = INPUT_KEYBOARD;
        keystroke[ i ].ki.wVk = keyCode;
        keystroke[ i ].ki.wScan = 0;
        keystroke[ i ].ki.dwFlags = 0;
        keystroke[ i ].ki.time = 0;
        keystroke[ i ].ki.dwExtraInfo = GetMessageExtraInfo();

        keystroke[ keystrokeToSend - i - 1 ].type = INPUT_KEYBOARD;
        keystroke[ keystrokeToSend - i - 1 ].ki.wVk = keyCode;
        keystroke[ keystrokeToSend - i - 1 ].ki.wScan = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwFlags =  KEYEVENTF_KEYUP;
        keystroke[ keystrokeToSend - i - 1 ].ki.time = 0;
        keystroke[ keystrokeToSend - i - 1 ].ki.dwExtraInfo = GetMessageExtraInfo();
        i = i + 1;
    }

    SendInput(characterCount,keystroke, sizeof(*keystroke));
}

