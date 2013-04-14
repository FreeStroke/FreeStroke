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
#include "../../includes/ui/notification/notification.h"
#include "../../includes/ui/notification/notifications.h"

#include "../../includes/common/utils.h"

Notification::Notification(Notification::Action t, const  QString & m, int ms, QWidget * w) : QWidget(w)
{
	this->setFixedSize(this->parentWidget()->minimumWidth(), 80);

    this->setFont(Utils::getFont());

	mAction = t;
	mMessage = m;
	mTime = ms;
	mLast = false;
	mIsClosable = true;

	if (mTime != 0)
	{
		if(mTime!=-1)
		{
			QTimer::singleShot(mTime, this, SLOT(destroy()));
		}
	}

	if (mTime == -1)
		mIsClosable = false;

	if (mAction == Notification::Progress)
	{
		QLabel * l = new QLabel(this);
        QMovie * m = new QMovie(Utils::getResourcesDirectory() + "loader.gif", QByteArray(), this);
		l->setMovie(m);
		m->start();
		l->move(QPoint(20, (this->height() / 2) - (32 / 2)));
		l->show();
	}

	this->show();
}

bool Notification::isLast()
{
	return mLast;
}

QString & Notification::message()
{
	return mMessage;
}

void Notification::setLast(bool s)
{
	mLast = s;
	this->update();
}

void Notification::destroy()
{
	Notifications * n = Notifications::address();
	n->notificationList()->removeAll(this);
	n->organize();
	delete this;
}

void Notification::mousePressEvent(QMouseEvent * e)
{
    Q_UNUSED(e)
}

void Notification::mouseReleaseEvent(QMouseEvent * e)
{
    Q_UNUSED(e)

	if (mIsClosable)
		this->destroy();
}

void Notification::paintEvent(QPaintEvent * e)
{
    Q_UNUSED(e)

	QPainter p(this);
	
	int textOffset = 15 + 42 + 15;
	int textMargin = 15;

	QPixmap i;

	switch(mAction)
	{
	case Notification::Download:
		{
            i = QPixmap(Utils::getResourcesDirectory() + "download.png");
			break;
		}
	case Notification::User:
		{
            i = QPixmap(Utils::getResourcesDirectory() + "user.png");
			break;
		}
	case Notification::Settings:
		{
            i = QPixmap(Utils::getResourcesDirectory() + "settings.png");
			break;
		}
	case Notification::Wait:
		{
            i = QPixmap(Utils::getResourcesDirectory() + "wait.png");
			break;
		}
	case Notification::Error:
		{
            i = QPixmap(Utils::getResourcesDirectory() + "error.png");
			break;
		}
	case Notification::Success:
		{
            i = QPixmap(Utils::getResourcesDirectory() + "success.png");
			break;
		}
    case Notification::Progress:
        {
            break;
        }
	}
	
	p.drawPixmap(QPointF(15, (this->height() / 2) - (i.height() / 2)), i);

	p.setPen(QColor("#ffffff"));
	p.drawText(textOffset, textMargin + 1, this->width() - textOffset - textMargin, this->height() - (textMargin * 2), Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignVCenter, mMessage);
	p.setPen(QColor("#3b3c3d"));
	p.drawText(textOffset, textMargin, this->width() - textOffset - textMargin, this->height() - (textMargin * 2), Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignVCenter, mMessage);

	if (!mLast)
	{
		p.setPen(QPen(QBrush(QColor("#d6d6d6")), 1));
		p.drawLine(1, this->height() - 2, this->width() - 2, this->height() - 2);
		p.setPen(QPen(QBrush(QColor("#f1f3f5")), 1));
		p.drawLine(1, this->height() - 1, this->width() - 2, this->height() - 1);
	}
    
}
