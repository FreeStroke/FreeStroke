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
#include "../../../../includes/ui/element/button/buttonelement.h"
#include "../../../../includes/common/utils.h"

ButtonElement::ButtonElement(QWidget *parent) : QAbstractButton(parent), Element(this)
{
    QFont f = Utils::getFont();
    f.setWeight(QFont::Bold);
    this->setFont(f);

    this->setFixedHeight(25);

    this->setCursor(Qt::PointingHandCursor);

    hasText = false;
    hasIcon = false;
}

void ButtonElement::setPosition(int pX, int pY)
{
    this->setGeometry(pX, pY, this->geometry().width(), this->geometry().height());
}

void ButtonElement::adjustSize()
{
    int textWidth = (hasText)?fontMetrics().size(0, this->text).width()+10:0;
    int iconWidth = (hasIcon)?pixmap.size().width():0;
    this->setFixedWidth(textWidth + iconWidth);
}

void ButtonElement::setText(QString title)
{
    if(title.isEmpty() || title.isNull())
        hasText = false;
    else
        hasText = true;

    this->text = title;

    this->adjustSize();
}

void ButtonElement::setIcon(QPixmap icon)
{
    if(icon.isNull())
        hasIcon = false;
    else
        hasIcon = true;

    this->pixmap = icon;
    this->adjustSize();
}

void ButtonElement::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);

    if (!this->isEnabled())
    {
        p.setOpacity(0.6);
        this->setCursor(Qt::ArrowCursor);
    }
    else
    {
        this->setCursor(Qt::PointingHandCursor);
    }

    p.setBrush(QColor(255, 255, 255, 0.6*255));
    p.drawRoundedRect(this->rect(), 3, 3);

    QRect rect = this->rect();
    rect.setHeight(rect.height()-1);
    p.setBrush(QColor("#959595"));
    p.drawRoundedRect(rect, 4, 4);

    if (!this->isDown())
        p.setBrush(QColor("#d6d6d6"));
    else
        p.setBrush(QColor("#c0c0c0"));
    p.drawRoundedRect(1, 1, rect.width() -2, rect.height() -2, 3, 3);

    p.setRenderHint(QPainter::Antialiasing, false);

    int xOffset = 0;
    if (hasIcon)
    {
        p.drawPixmap(0, 0, this->height(), this->height(), pixmap);
        xOffset = pixmap.size().width();
    }

    if(hasText)
    {
        p.translate(xOffset, 1);
        p.setPen(QColor(255,255,255,0.8*255));

        int align = Qt::AlignVCenter;
        if (!hasIcon)
            align = Qt::AlignCenter;

        p.drawText(rect.x(), rect.y() + 1, rect.width()-xOffset, rect.height(), align, this->text);
        p.translate(0,-1);
        p.setPen(QColor("#535353"));
        p.drawText(rect.x(), rect.y() + 1, rect.width()-xOffset, rect.height(), align, this->text);
    }

    
}
