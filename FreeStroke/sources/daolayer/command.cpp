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
#include "../../includes/daolayer/command.h"
#include "../../includes/ui/element/keylistener/keyconverter.h"

#if defined(Q_OS_DARWIN)
#include "../../includes/others/mac/mac.h"
#elif defined(Q_OS_UNIX)
#include "../../includes/others/linux/linux.h"
#else
#include "../../includes/others/windows/windows.h"
#endif

Command::Command(QString pDefinition, CommandType pType)
{
    this->definition = pDefinition;
    this->type = pType;
}

QHash<QString, int> Command::specialKeysMap()
{
    static QHash<QString, int> l = QHash<QString, int>();
    if (l.count() == 0)
    {
#if defined(Q_OS_DARWIN)
        l.insert("Space", 0x31);
        l.insert("Return", 0x24);
        l.insert("Backspace", 0x33);
        l.insert("Del", 0x75);
        l.insert("Right", 0x7C);
        l.insert("Left", 0x7B);
        l.insert("Up", 0x7E);
        l.insert("Down", 0x7D);
        l.insert("Tab", 0x30);
        l.insert("Backtab", 0x30);
        l.insert("Esc", 0x35);
        l.insert("F1", 0x7A);
        l.insert("F2", 0x78);
        l.insert("F3", 0x63);
        l.insert("F4", 0x76);
        l.insert("F5", 0x60);
        l.insert("F6", 0x61);
        l.insert("F7", 0x62);
        l.insert("F8", 0x64);
        l.insert("F9", 0x65);
        l.insert("F10", 0x6D);
        l.insert("F11", 0x67);
        l.insert("F12", 0x6F);
#elif defined(Q_OS_UNIX)
        l.insert("Space", 0x20);
        l.insert("Del", 0xFFFF);
        l.insert("Return", 0xFF0D);
        l.insert("Backspace", 0xFF08);
        l.insert("Right", 0xFF53);
        l.insert("Left", 0xFF51);
        l.insert("Up", 0xFF52);
        l.insert("Down", 0xFF54);
        l.insert("Tab", 0xFF09);
        l.insert("Backtab", 0xFF09);
        l.insert("Esc", 0xFF1B);
        l.insert("F1", 0xFFBE);
        l.insert("F2", 0xFFBF);
        l.insert("F3", 0xFFC0);
        l.insert("F4", 0xFFC1);
        l.insert("F5", 0xFFC2);
        l.insert("F6", 0xFFC3);
        l.insert("F7", 0xFFC4);
        l.insert("F8", 0xFFC5);
        l.insert("F9", 0xFFC6);
        l.insert("F10", 0xFFC7);
        l.insert("F11", 0xFFC8);
        l.insert("F12", 0xFFC9);
#else
        l.insert("Space", 0x20);
        l.insert("Del", 0x2E);
        l.insert("Return", 0x0D);
        l.insert("Backspace", 0x08);
        l.insert("Right", 0x27);
        l.insert("Left", 0x25);
        l.insert("Up", 0x26);
        l.insert("Down", 0x28);
        l.insert("Tab", 0x09);
        l.insert("Backtab", 0x09);
        l.insert("Esc", 0x1B);
        l.insert("F1", 0x70);
        l.insert("F2", 0x71);
        l.insert("F3", 0x72);
        l.insert("F4", 0x73);
        l.insert("F5", 0x74);
        l.insert("F6", 0x75);
        l.insert("F7", 0x76);
        l.insert("F8", 0x77);
        l.insert("F9", 0x78);
        l.insert("F10", 0x79);
        l.insert("F11", 0x7A);
        l.insert("F12", 0x7B);
#endif
    }
    return l;
}

QString Command::getDefinition()
{
    return this->definition;
}

CommandType Command::getType()
{
    return this->type;
}

void Command::executeCommand()
{
    switch(this->type)
    {
    case SCRIPT:
    {
        QProcess process;
        QString program;
#if defined(Q_OS_DARWIN)
        if(!this->definition.startsWith("open "))
        {
            program = "open \""+ this->definition + "\"";
        }
        else
        {
            program = this->definition;
        }
#elif defined(Q_OS_UNIX)
        program = this->definition;
#else
        if(!this->definition.startsWith("start "))
        {
            program = "start /B \"FreeStroke\" "+ this->definition;
        }
        else
        {
            program = this->definition;
        }
#endif
        qDebug()<< "Program : "<<program;
#if defined(Q_OS_DARWIN)
        process.startDetached(program);
#else
        process.startDetached(program);
#endif
        break;
    }
    case KEYSTROKE:
    {
        int keycode;
        bool shiftModifier = false;
        bool ctrlModifier= false;
        bool metaModifier= false;
        bool altModifier= false;
        bool altGrModifier= false;

        if(KeyConverter::fromText(this->definition, &keycode, &shiftModifier, &ctrlModifier, &altModifier, &metaModifier, &altGrModifier))
        {
            if(this->definition.length() > 1)
            {
                for(int i = 0; i < this->specialKeysMap().keys().count(); i++)
                {
                    if(this->definition.contains(this->specialKeysMap().keys().at(i)))
                    {
                        keycode = this->specialKeysMap().values().at(i);
                    }
                }
            }
            qDebug()<<"key "<< keycode;
#if defined(Q_OS_DARWIN)
            Mac::generateKeyEvent(keycode, shiftModifier, ctrlModifier, metaModifier, altModifier, altModifier);
#elif defined(Q_OS_UNIX)
            Linux::generateKeyEvent(keycode, shiftModifier, ctrlModifier, metaModifier, altModifier, altGrModifier);
#else
            Windows::generateKeyEvent(keycode, shiftModifier, ctrlModifier, metaModifier, altModifier, altGrModifier);
#endif
        }
        break;
    }
    }
}
