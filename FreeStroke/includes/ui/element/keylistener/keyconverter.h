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
/*!
 * \file keyconverter.h
 * \brief The KeyConverter class is used to convert KeyCode to Text and Text to KeyCode for saving keystroke Command
 * in the database and generate them.
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/

#ifndef KEYCONVERTER_H
#define KEYCONVERTER_H

#ifdef Q_OS_DARWIN
#include "../../../others/mac/mac.h"
#endif

/*!
 * \brief The KeyConverter class is used to convert KeyCode to Text and Text to KeyCode for saving keystroke Command
 */
class KeyConverter
{
public:
    /*!
     * \brief textFromKey convert a Qt::Key to a QString
     * \param pKey the key to convert
     * \return the QString representing the key
     */
    static QString textFromKey(Qt::Key pKey)
    {
        switch (pKey)
        {
        case Qt::Key_Shift:
            return QString::fromUtf8("Shift");
        case Qt::Key_Control:
            return QString::fromUtf8("Ctrl");
        case Qt::Key_Meta:
            return QString::fromUtf8("Meta");
        case Qt::Key_Alt:
            return QString::fromUtf8("Alt");
        case Qt::Key_AltGr:
            return QString::fromUtf8("AltGr");
        default:
            if( QKeySequence(pKey).toString() == "ៀ") // DAT IS BIOU TI FOULLE
            {
                return "UNKNOWN";
            }
            return QKeySequence(pKey).toString();
        }
        return "UNKNOWN";
    }

    /*!
     * \brief keyFromText convert a QString representing a Key to a Qt::Key
     * \param pText the QString representing a Key
     * \return the Qt::Key represented by the QString
     */
    static Qt::Key keyFromText(QString pText)
    {
        if (pText == QString::fromUtf8("Shift"))
        {
            return Qt::Key_Shift;
        }
        else if (pText == QString::fromUtf8("Ctrl"))
        {
            return Qt::Key_Control;
        }
        else if (pText == QString::fromUtf8("Alt"))
        {
            return Qt::Key_Alt;
        }
        else if (pText == QString::fromUtf8("Meta"))
        {
            return Qt::Key_Meta;
        }
        else if (pText == QString::fromUtf8("AltGr"))
        {
            return Qt::Key_AltGr;
        }

        QKeySequence seq = QKeySequence::fromString(pText);
        int keyCode;
        keyCode = seq[0];

#ifdef Q_OS_DARWIN
        return (Qt::Key)Mac::convertToCGKeyCode(pText.at(0).unicode());
#elif defined(Q_OS_UNIX)
        return (Qt::Key)pText.at(0).unicode();
#else
        return (Qt::Key)keyCode;
#endif
    }

    /*!
     * \brief fromText convert a String which represent a KeyStroke (a Key and / or Modifiers) to the Qt::Key
     * \param pText the text representing the KeyStroke
     * \param pKeyCode the pointer of the Key which will be filled
     * \param pShift the pointer of the shift modifier which will be filled (true if shift is present)
     * \param pCtrl the pointer of the ctrl modifier which will be filled (true if ctrl is present)
     * \param pAlt the pointer of the alt modifier which will be filled (true if alt is present)
     * \param pMeta the pointer of the meta modifier which will be filled (true if meta is present)
     * \param pAltGr the pointer of the altgr modifier which will be filled (true if altgr is present)
     * \return true if a key have been converted, false otherwise
     */
    static bool fromText(QString pText, int* pKeyCode, bool* pShift, bool* pCtrl, bool* pAlt, bool* pMeta, bool *pAltGr)
    {
        bool returnFlag = false;
        QStringList l = pText.split("\t", QString::SkipEmptyParts);
        for(int i = 0; i < l.length(); i++ )
        {
            if (l.at(i) == QString::fromUtf8("Shift"))
            {
                *pShift = true;
                returnFlag = true;
            }
            else if (l.at(i) == QString::fromUtf8("Ctrl"))
            {
                *pCtrl = true;
                returnFlag = true;
            }
            else if (l.at(i) == QString::fromUtf8("Alt"))
            {
                *pAlt = true;
                returnFlag = true;
            }
            else if (l.at(i) == QString::fromUtf8("Meta"))
            {
                *pMeta = true;
                returnFlag = true;
            }
            else if (l.at(i) == QString::fromUtf8("AltGr"))
            {
                *pAltGr = true;
                returnFlag = true;
            }
            else
            {
                *pKeyCode = KeyConverter::keyFromText(l.at(i));
                returnFlag = true;
            }
        }
        return returnFlag;
    }
};

#endif // KEYCONVERTER_H
