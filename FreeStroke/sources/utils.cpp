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
#include "../includes/utils.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>

QFont Utils::getFont()
{
    QFont f("Arial");
    f.setPixelSize(12);
    return f;
}

QString Utils::getDatabaseDirectoryLocation()
{
#if defined(Q_OS_UNIX) && !defined(Q_OS_DARWIN) && defined(UNITTEST)
    return QDir::toNativeSeparators(Utils::getApplicationDirectoryRoot() + "FreeSoft/FreeStroke/");
#elif defined(Q_OS_DARWIN)
    return QDir::toNativeSeparators(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "/FreeSoft/FreeStroke/");
#else
    // @see https://bugreports.qt-project.org/browse/QTBUG-10772
    QString dataLocation = QDir::toNativeSeparators(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    if(dataLocation.endsWith(QDir::toNativeSeparators("//")))
    {
        dataLocation.chop(1);
    }
    return dataLocation + QDir::toNativeSeparators("FreeSoft/FreeStroke/");
#endif
}

QString Utils::getDatabaseLocation()
{
#ifdef UNITTEST
    return QDir::toNativeSeparators(Utils::getDatabaseDirectoryLocation() + "freesoft-tests.db");
#else
    return QDir::toNativeSeparators(Utils::getDatabaseDirectoryLocation() + "freesoft.db");
#endif
}

QString Utils::getConfigLocation()
{
    return QDir::toNativeSeparators(Utils::getDatabaseDirectoryLocation() + "config.xml");
}

QString Utils::getApplicationDirectoryRoot()
{
#if defined(Q_OS_DARWIN)
    return QCoreApplication::applicationDirPath()+"/../../../";
#elif defined(Q_OS_UNIX)
    return QCoreApplication::applicationDirPath() + "/";
#else
    return QCoreApplication::applicationDirPath() + "/";
#endif
}

QString Utils::getResourcesDirectory()
{
    return ":/";//QCoreApplication::applicationDirPath()+"/../Resources/resources/";
}

void* Utils::secureMalloc(int size)
{
    void* ptr;
    if ((ptr = malloc(size)) == NULL)
    {
        QCoreApplication::quit();
    }

    return ptr;
}

void Utils::secureFree(void *ptr)
{
    if (ptr != NULL)
    {
        free(ptr);
    }
}

