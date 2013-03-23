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
#ifndef COMMAND_H
#define COMMAND_H

/*!
 * \file command.h
 * \author Anthony Fourneau
 * \brief Representation of a command
 * \date 2013-02-12
 */

#include "commandtype.h"
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QHash>

/*!
 * \class Command
 * \brief The class is the representation of a command
 *
 */
class Command
{
public:
    /*!
     * \brief constructor of Command
     * \param The definition of the command : it can be keys combinaison or a script with arguments
     * \param The type of the command \see CommandType
     */
    Command(QString, CommandType);

    /*!
     * \brief get the definition of the command
     * \return the definition of the command :  it can be keys combinaison or a script with arguments
     */
    QString getDefinition();

    /*!
     * \brief get the type of the command
     * \return the type of the command \see CommandType
     */
    CommandType getType();

    /*!
     * \brief execute the command declare in the definition
     */
    void executeCommand();

    /*!
     * \brief This method construct a map corresponding to a special key and his value according to the system
     * \return a map corresponding to a special key and his value according to the system
     */
    static QHash<QString, int> specialKeysMap();
private:
    QString definition; /*!< The definition of the command */
    CommandType type; /*!< The type of the command */
};

#endif // COMMAND_H
