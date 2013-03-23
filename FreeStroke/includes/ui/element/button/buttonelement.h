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
 * \file buttonelement.h
 * \brief The ButtonElement class is a button with a custom look
 * \author Aurèle Lenfant (thanks to Romain Etchegoyhen)
 * \date 2013-02-20
 */
#ifndef BUTTONELEMENT_H
#define BUTTONELEMENT_H

#include <QtGui/QAbstractButton>

#include "../element.h"

/*!
 * \brief The ButtonElement class is a QPushButton with a custom look
 */
class ButtonElement : public QAbstractButton, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief the default ButtonElement constructor
     * \param parent the QWidget container parent
     */
    ButtonElement(QWidget *parent = 0);
    /*!
     * \brief set the position of the ButtonElement
     * \param pX the desired x
     * \param pY the desired y
     */
    void setPosition(int pX, int pY);
    /*!
     * \brief adjust the size of the ButtonElement
     */
    void adjustSize();
    /*!
     * \brief set the text of the ButtonElement
     * \param title the desired text
     */
    void setText(QString title);
    /*!
     * \brief set the icon of the ButtonElement
     * \param icon the desired icon
     */
    void setIcon(QPixmap icon);

private:
    /*!
     * \brief hasIcon boolean that determined if the ButtonElement has an icon
     */
    bool hasIcon;
    /*!
     * \brief hasText boolean that determined if the ButtonElement has a text
     */
    bool hasText;

    /*!
     * \brief pixmap the icon of the ButtonElement
     */
    QPixmap pixmap;
    /*!
     * \brief text the text of the ButtonElement
     */
    QString text;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // BUTTONELEMENT_H
