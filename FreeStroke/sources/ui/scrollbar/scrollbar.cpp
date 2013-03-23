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
#include "../../includes/ui/scrollbar/scrollbar.h"

ScrollBar::ScrollBar(QWidget * w) : QScrollBar(w)
{
}

ScrollBar::ScrollBar(Qt::Orientation pOrientation, QWidget * w) : QScrollBar(pOrientation, w)
{
    this->setStyleSheet("QScrollBar { background: transparent; border: none; padding-left: 4px; padding-right: 4px; padding-top: 3px; padding-bottom: 3px; width: 16px; }");
    this->setStyleSheet(this->styleSheet() + "QScrollBar::handle { background: rgba(0, 0, 0, 50); width: 8px; border-radius: 4px; min-height: 30px; }");
    this->setStyleSheet(this->styleSheet() + "QScrollBar::down-arrow { background: transparent; border: none; }");
    this->setStyleSheet(this->styleSheet() + "QScrollBar::up-arrow { background: transparent; border: none; }");
    this->setStyleSheet(this->styleSheet() + "QScrollBar::add-line { background: transparent; border: none; }");
    this->setStyleSheet(this->styleSheet() + "QScrollBar::sub-line { background: transparent; border: none; }");
    this->setStyleSheet(this->styleSheet() + "QScrollBar::add-page { background: transparent; border: none; }");
    this->setStyleSheet(this->styleSheet() + "QScrollBar::sub-page { background: transparent; border: none; }");
    this->setFixedWidth(16);
    this->setSingleStep(20);
}

void ScrollBar::wheelEvent(QWheelEvent * e)
{
	QScrollBar::wheelEvent(e);
}

void ScrollBar::paintEvent(QPaintEvent * e)
{
    QScrollBar::paintEvent(e);

    QPainter p(this);

    p.setPen(QColor(0, 0, 0, 0.2*255));
    p.drawLine(this->width() - 2, 0, this->width() - 2, this->height());

    p.setPen(QColor(0, 0, 0, 0.1*255));
    p.drawLine(this->width() - 1, 0, this->width() - 1, this->height());

    p.end();
}
