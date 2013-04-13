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

#include "../../includes/ui/bottombar/bottombar.h"

BottomBar::BottomBar(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(52);
    this->setStyleSheet("border: none;");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setContentsMargins(10, 0, 10, 0);

    this->printLeft = false;
    this->printRight = false;
    this->isTopBar = false;
}

void BottomBar::addElement(Element *pButton)
{
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    layout->addWidget(pButton->getWidget());
}

void BottomBar::addSeparator()
{
    BottomBarSeparator* sep = new BottomBarSeparator(this);
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    layout->addWidget(sep);
}

void BottomBar::addLeftLine(bool pPrint)
{
    this->printLeft = pPrint;
}

void BottomBar::addRightLine(bool pPrint)
{
    this->printRight = pPrint;
}

void BottomBar::setTopBar(bool pSetTopBar)
{
     this->isTopBar = pSetTopBar;
}

void BottomBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int offset = 0;

    if(!isTopBar)
    {
        p.setPen(QColor(0, 0, 0, 0.05*255));
        p.drawLine(0, 0, this->width(), 0);
        p.setPen(QColor(0, 0, 0, 0.2*255));
        p.drawLine(0, 1, this->width(), 1);
    }
    else
    {
        offset = 2;
    }

    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#e1e1e1"));
    p.drawRect(0, 2 - offset, this->width(), this->height());

    QLinearGradient g(0, 0, 0, this->height());
    g.setColorAt(0, QColor(255, 255, 255, 0.05*255));
    g.setColorAt(1, QColor(0, 0, 0, 0.1*255));
    p.setBrush(g);
    p.drawRect(0, 2, this->width(), this->height());

    if (this->printRight)
    {
        p.setPen(QColor(0, 0, 0, 0.2*255));
        p.drawLine(this->width() - 1, 2 - offset, this->width() - 1, this->height() - 2);
    }

    if (this->printLeft)
    {
        p.setPen(QColor(0, 0, 0, 0.1*255));
        p.drawLine(0, 2, 0, this->height() - 2);
    }
    p.end();
}
