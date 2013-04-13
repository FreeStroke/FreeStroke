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
#include "../../includes/ui/gestureparams/gestureparams.h"

GestureParams::GestureParams(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(35);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 0, 10, 0);
    layout->setAlignment(Qt::AlignVCenter);
}

void GestureParams::addElement(Element *pElement)
{
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    layout->addWidget(pElement->getWidget());
}

void GestureParams::addSpacer()
{
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    layout->addSpacerItem(new QSpacerItem(this->width(), this->height(), QSizePolicy::MinimumExpanding));
}

void GestureParams::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setPen(Qt::NoPen);

    p.setBrush(QColor("#dbdbdb"));
    p.drawRect(this->rect());

    p.setPen(QColor("#7d7d7d"));
    p.drawLine(0, this->height()-1, this->width(), this->height()-1);
    p.end();
}
