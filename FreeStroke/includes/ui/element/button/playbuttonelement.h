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
 * \file playbuttonelement.h
 * \brief The PlayButtonElement class represent a custom play button.
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */
#ifndef PLAYBUTTONELEMENT_H
#define PLAYBUTTONELEMENT_H

#include "../element.h"

/*!
 * \brief The PlayButtonElement class represent a custom play button.
 */
class PlayButtonElement : public QAbstractButton, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief the default PlayButtonElement constructor
     * \param parent the container QWidget parent
     */
    PlayButtonElement(QWidget *parent = 0);
private:
    /*!
     * \brief the icon of the PlayButtonElement while not selected
     */
    QPixmap *pixmap;
    /*!
     * \brief the icon of the PlayButtonElement while selected
     */
    QPixmap *pixmapSelected;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // PLAYBUTTONELEMENT_H
