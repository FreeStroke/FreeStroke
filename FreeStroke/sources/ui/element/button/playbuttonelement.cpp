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
#include "../../../../includes/ui/element/button/playbuttonelement.h"
#include "../../../../includes/common/utils.h"

PlayButtonElement::PlayButtonElement(QWidget * parent) : QAbstractButton(parent), Element(this)
{
    this->setFixedSize(QSize(600,400));
    this->setIconSize(this->size());
    this->setCheckable(true);
    this->setChecked(false);
    this->pixmap = new QPixmap(Utils::getResourcesDirectory()+"/tuto-overlay.png");
    this->pixmapSelected = new QPixmap(Utils::getResourcesDirectory()+"/tuto-overlay-hover.png");
    this->setCursor(Qt::PointingHandCursor);
}

void PlayButtonElement::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setRenderHint(QPainter::Antialiasing, true);

    // Icon
    if (this->isDown())
    {
        p.drawPixmap(this->width()/2-this->pixmapSelected->width()/2,
                     this->height()/2-this->pixmapSelected->height()/2,
                     this->pixmapSelected->width(), this->pixmapSelected->height(), *this->pixmapSelected);
    }
    else
    {
        p.drawPixmap(this->width()/2-this->pixmap->width()/2,
                     this->height()/2-this->pixmap->height()/2,
                     this->pixmap->width(), this->pixmap->height(), *this->pixmap);
    }

    p.end();
}
