#include "../../includes/common/utils.h"

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
    else if (!dataLocation.endsWith(QDir::toNativeSeparators("/")))
    {
        dataLocation  = dataLocation + QDir::toNativeSeparators("/");
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

