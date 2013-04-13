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
#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QtWidgets>

class Notification : public QWidget
{
	Q_OBJECT
public:
	enum Action {
		Settings,
		Download,
		User,
		Progress,
		Error,
		Success,
		Wait
	};
    Notification(Notification::Action t, const  QString & m, int ms = 0, QWidget * w = 0);
	bool isLast();
	void setLast(bool s);
	QString & message();
public slots:
	void destroy();
protected:
	void mousePressEvent(QMouseEvent * e);
	void mouseReleaseEvent(QMouseEvent * e);
	void paintEvent(QPaintEvent * e);
private:
	Notification::Action mAction;
	QString mMessage;
	int mTime;
	bool mLast;
	bool mIsClosable;
};

#endif
