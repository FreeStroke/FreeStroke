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
 * \file utils.h
 * \author Sylvain Fay-Chatelard
 * \brief Utiliy class for freestroke application
 * \date 2013-02-12
 */
#ifndef UTILS_H
#define UTILS_H

#include <QtCore/QObject>
#include <QtGui/QFont>

/*!
 * \brief Utiliy class for freestroke application
 */
class Utils : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Gets the default font for freestroke
     * \return the default QFont object
     */
    static QFont getFont();

    /*!
     * \brief Gets the resources directory of freestroke
     * \return a path to the resources directory
     */
    static QString getResourcesDirectory();

    /*!
     * \brief Gets the database directory of freestroke
     * \return a path to the database directory
     */
    static QString getDatabaseDirectoryLocation();

    /*!
     * \brief Gets the location of freestroke database
     * \return a path to the freestroke database
     */
    static QString getDatabaseLocation();

    /*!
     * \brief Gets the configuration file path
     * \return a path to the configuration file
     */
    static QString getConfigLocation();


    /*!
     * \brief Gets the application root path of freestroke
     * \return a path to the application root directory of freestroke
     */
    static QString getApplicationDirectoryRoot();

    /*!
     * \brief This function does a malloc and check the result, if the malloc failed, the application
     * is killed with abort() because there is not enough memory.
     * \param size The size to allocate
     * \return The created pointer, the application can be killed
     */
    static void* secureMalloc(int size);

    /*!
     * \brief This function free a pointer
     * \param ptr The pointer to free
     */
    static void secureFree(void *ptr);
    
signals:
    
public slots:
    
};

#endif // UTILS_H
