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
 * \file mainwindow.h
 * \brief
 * \author Sylvain Fay-Châtelard
 * \date 2013-02-20
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QtGui/QApplication>
#include <QtGui/QKeyEvent>
#include "mainwindow.h"

/*!
 * \brief The Application class represent the main application.
 *          It contains static method for restarting the application and get keyboard modifiers.
 */
class Application : public QApplication
{
	Q_OBJECT
public:

    /*!
     * \brief default Application constructor
     * \param argc form the main parameters
     *\param argv form the main parameters
     */
    Application(int &argc, char **argv);

    /*!
     * \brief restart the application
     */
    static void restart();

    /*!
     * \brief getModifiers
     * \return current status of all modifiers
     */
    static Qt::KeyboardModifier getModifiers();

    /*!
     * \brief setModifiers to update current modifiers
     * \param pCtrl CTRL modifier state
     * \param pShift SHIFT modifier state
     * \param pMeta META modifier state
     */
    static void setModifiers(bool pCtrl, bool pShift, bool pMeta);

protected:

    /*!
     * \brief notify event
     * \param receiver who will receive the event
     * \param e event
     * \return if the nofication must be send
     */
    bool notify (QObject * receiver, QEvent *e);
};

#endif
