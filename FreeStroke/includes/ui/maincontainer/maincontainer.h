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
 * \file maincontainer.h
 * \brief The MainContainer class is the QWidget contening all the view of the application
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef MAINCONTAINER_H
#define MAINCONTAINER_H

#include <QtGui/QWidget>
#include <QtCore/QList>
#include <QtCore/QString>

/*!
 * \brief The MainContainer class is the QWidget contening all the view of the application
 */
class MainContainer: public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief default MainContainer constructor
     * \param parent the container QWidget parent
     */
    explicit MainContainer(QWidget *parent);

    /*!
     * \brief addWidget add a Widget to the Container
     * \param pWidget the Widget to add to the Container
     */
    void addWidget(QWidget* pWidget);

protected:
    void resizeEvent(QResizeEvent * e);

private:
    /*!
     * \brief widgets the QList containing all the Widget of the Container
     */
    QList<QWidget*> widgets;


};

#endif // MAINCONTAINER_H
