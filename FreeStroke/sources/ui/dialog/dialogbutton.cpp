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
#include "../../includes/ui/dialog/dialogbutton.h"
#include "../../includes/common/utils.h"


/* DialogButton */
DialogButton::DialogButton(const QString & pText,  DialogButton::Type pType, QWidget * parent) : QPushButton(pText, parent)
{
	mPressed = false;
    this->buttonType = pType;
	this->setStyleSheet("border: none; background: transparent; padding-bottom: 5px; color: #fff; font-size: 15px; font-family: Arial; padding-left: 14px; padding-right: 14px;");
	
	QFontMetrics fontSize(this->font());
    QRect rect = fontSize.boundingRect(this->text());
    this->setMinimumWidth(100);
	this->resize(rect.width() + 32, 35);
}

DialogButton::~DialogButton()
{
}

void DialogButton::fix()
{
	QFontMetrics fontSize(this->font());
    QRect rect = fontSize.boundingRect(this->text());
	this->resize(rect.width() + 32, 35);
}

DialogButton::Type DialogButton::type()
{
    return buttonType;
}

void DialogButton::mousePressEvent(QMouseEvent * event)
{
	mPressed = true;
	this->update();

	QPushButton::mousePressEvent(event);
}

void DialogButton::mouseReleaseEvent(QMouseEvent *event)
{
	mPressed = false;
	this->update();

	QPushButton::mouseReleaseEvent(event);
}

void DialogButton::enterEvent(QEvent * event)
{
	Q_UNUSED(event);
	this->setCursor(Qt::PointingHandCursor);
}

void DialogButton::leaveEvent(QEvent * event)
{
	Q_UNUSED(event);
	this->setCursor(Qt::ArrowCursor);
}

void DialogButton::paintEvent(QPaintEvent * event)
{
	/* Create painter */
	QPainter p(this);
	p.setRenderHint(QPainter::SmoothPixmapTransform);
	p.setPen(Qt::NoPen);

	/* FontMetrics */
	QFontMetrics fontSize(this->font());
    QRect rect = fontSize.boundingRect(this->text());

	this->resize(rect.width() + 32, 35);
	
    if (buttonType == DialogButton::Normal)
	{
		if(mPressed)
		{
            p.drawPixmap(0, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-left-inverted.png"));

            p.setBrush(QBrush(QPixmap(Utils::getResourcesDirectory() + "dialog-button-bg-inverted.png")));
			p.drawRect(10, 0, this->width() - 10 - 10, 35);

            p.drawPixmap(10 + this->width() - 10 - 10, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-right-inverted.png"));
		}
		else
		{
            p.drawPixmap(0, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-left.png"));

            p.setBrush(QBrush(QPixmap(Utils::getResourcesDirectory() + "dialog-button-bg.png")));
			p.drawRect(10, 0, this->width() - 10 - 10, 35);

            p.drawPixmap(10 + this->width() - 10 - 10, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-right.png"));
		}
	}
    else if (buttonType == DialogButton::Dark)
	{
		if(mPressed)
		{
            p.drawPixmap(0, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-left-dark-inverted.png"));

            p.setBrush(QBrush(QPixmap(Utils::getResourcesDirectory() + "dialog-button-bg-dark-inverted.png")));
			p.drawRect(10, 0, this->width() - 10 - 10, 35);

            p.drawPixmap(10 + this->width() - 10 - 10, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-right-dark-inverted.png"));
		}
		else
		{
            p.drawPixmap(0, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-left-dark.png"));

            p.setBrush(QBrush(QPixmap(Utils::getResourcesDirectory() + "dialog-button-bg-dark.png")));
			p.drawRect(10, 0, this->width() - 10 - 10, 35);

            p.drawPixmap(10 + this->width() - 10 - 10, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-right-dark.png"));
		}
	}
	else
	{
		if(mPressed)
		{
            p.drawPixmap(0, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-bright-left-inverted.png"));

            p.setBrush(QBrush(QPixmap(Utils::getResourcesDirectory() + "dialog-button-bright-bg-inverted.png")));
			p.drawRect(10, 0, this->width() - 10 - 10, 35);

            p.drawPixmap(10 + this->width() - 10 - 10, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-bright-right-inverted.png"));
		}
		else
		{
            p.drawPixmap(0, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-bright-left.png"));

            p.setBrush(QBrush(QPixmap(Utils::getResourcesDirectory() + "dialog-button-bright-bg.png")));
			p.drawRect(10, 0, this->width() - 10 - 10, 35);

            p.drawPixmap(10 + this->width() - 10 - 10, 0, 10, 35, QPixmap(Utils::getResourcesDirectory() + "dialog-button-bright-right.png"));
		}
	}

	p.setPen(QColor(0, 0, 0));
    p.drawText(0, -1, this->width(), this->height(), Qt::AlignCenter, this->text());

	p.end();

    QPushButton::paintEvent(event);
}
