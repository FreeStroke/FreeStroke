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

