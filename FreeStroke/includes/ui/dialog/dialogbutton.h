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
 * \file dialogbutton.h
 * \brief The DialogButton class represents a special QPushButton used by Dialog
 * \author Aurèle Lenfant (thanks to Romain Etchegoyhen)
 * \date 2013-02-20
 */
#ifndef CUSTOMFORMS_H
#define CUSTOMFORMS_H

#include <QtWidgets>

/*!
 * \brief The DialogButton class represents a special QPushButton used by Dialog
 */
class DialogButton : public QPushButton
{
	Q_OBJECT
public:
    /*!
     * \brief The Type enum defines the different type of a DialogButton which changes its color
     */
	enum Type {
		Normal,
		Dark,
        Bright
	};
public:
    /*!
     * \brief the default DialogButton constructor
     * \param text the text to show on the DialogButton
     * \param type the Type of the DialogButton which defins its color
     * \param parent the container QWidget parent
     */
    DialogButton(const QString & text, DialogButton::Type pType = DialogButton::Normal, QWidget * parent = 0);
	~DialogButton();
    /*!
     * \brief type returns the Type of the DialogButton
     * \return the Type of the DialogButton
     */
    DialogButton::Type type();
    /*!
     * \brief fix the size of the DialogButton and its label size
     */
	void fix();
private:
    /*!
     * \brief type the Type of the DialogButton
     */
    DialogButton::Type buttonType;
	bool mPressed;
protected:
	void paintEvent(QPaintEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	void enterEvent(QEvent * event);
	void leaveEvent(QEvent * event);
};

#endif
