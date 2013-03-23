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
#include "../../includes/ui/topbar/topbar.h"
#include <QtGui/QPainter>
#include <QtGui/QHBoxLayout>

TopBar::TopBar(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(50);

    group = new QButtonGroup(this);
    group->setExclusive(true);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignHCenter);
}

void TopBar::addButton(MenuButtonElement *pButton)
{
    group->addButton(pButton);
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    layout->addWidget(pButton);
}

void TopBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setPen(Qt::NoPen);

    QLinearGradient g(0, 0, 0, this->height());
    g.setColorAt(0, QColor("#e8e8e8"));
    g.setColorAt(0.01, QColor("#ebebeb"));
    g.setColorAt(1, QColor("#b2b2b2"));
    p.setBrush(g);

    p.drawRect(this->rect());

    p.setPen(QColor("#7d7d7d"));
    p.drawLine(0, this->height()-1, this->width(), this->height()-1);
    p.end();
}
