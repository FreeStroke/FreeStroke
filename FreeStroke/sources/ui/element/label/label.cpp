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
#include "../../../../includes/ui/element/label/label.h"
#include "../../../../includes/common/utils.h"


#include <QtGui/QPainter>
#include <QtCore/QDebug>


Label::Label(QString pText, QWidget *parent) : QLabel(pText, parent), Element(this)
{
    this->backgroundColor = QColor(255,255,255,0);
    this->textColor = QColor("#636363");
    this->resize(parent->size());
    this->setWordWrap(true);
    this->setAlignment(Qt::AlignCenter);
    this->setEnabled(false);
    this->setMouseTracking(false);

    QFont f = Utils::getFont();
    f.setWeight(QFont::Bold);
    this->setFont(f);
    this->paintShadow = true;
}

Label::Label(QString pText, QColor pBackground, QWidget *parent) : QLabel(pText, parent), Element(this)
{
    this->backgroundColor = pBackground;
    this->textColor = QColor("#636363");
    this->resize(parent->size());
    this->setWordWrap(true);
    QFont f = Utils::getFont();
    f.setBold(true);
    this->setFont(f);
    this->paintShadow = true;
}

void Label::setPaintShadow(bool pPaintShadow)
{
    this->paintShadow = pPaintShadow;
}

void Label::changeFontSize(int pSize)
{
    QFont fText = this->font();
    fText.setPixelSize(pSize);
    this->setFont(fText);
}

void Label::setTextColor(QColor pColor)
{
    this->textColor = pColor;
}

void Label::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing, false);
    p.setPen(Qt::NoPen);

    p.setBrush(this->backgroundColor);
    p.drawRect(this->rect());

    p.setPen(QColor(255,255,255,0.6*255));
    p.translate(0,1);
    if (this->paintShadow)
    {
        p.drawText(this->rect(), this->alignment(), this->text());
    }

    p.setPen(this->textColor);
    p.translate(0,-1);
    p.drawText(this->rect(), this->alignment(), this->text());

    if(this->pixmap() != NULL)
    {
        p.drawPixmap(0,0,this->width(),this->height(),*this->pixmap());
    }

    p.end();
}

