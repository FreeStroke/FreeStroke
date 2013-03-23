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
#include "../../includes/ui/cell/cellcontroller.h"
#include "../../includes/common/utils.h"

CellController::CellController(void* pList) : Cell(pList, true)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    this->labelController = new Label("",this);
    this->labelController->changeFontSize(14);
    this->labelController->setTextColor(QColor(230,230,230));
    this->labelController->setPaintShadow(false);
    this->iconChoose = new QLabel(this);
    this->iconChoose->setPixmap(QPixmap(Utils::getResourcesDirectory() + "arrow-right.png"));
    this->iconChoose->setFixedSize(10,15);
    this->setFixedHeight(47);
    layout->addWidget(labelController);
    layout->addWidget(iconChoose);
}

void CellController::setController(Controller* pController)
{
    this->labelController->setText(pController->getName() + " : " + pController->getIpAddr() + ":" + QString::number(pController->getPort()));
}

void CellController::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    emit clicked();
}

void CellController::paintEvent(QPaintEvent * e)
{
    Q_UNUSED(e);

    QPainter p(this);
    p.setPen(Qt::NoPen);

    p.setBrush(QColor(162,162,162));
    p.drawRect(this->rect());

    p.translate(0, -1);
    p.setBrush(QColor(39,39,39));
    p.drawRect(this->rect());

    p.translate(0, -1);

    if (this->alternateColor)
    {
        p.setBrush(QColor(86,96,106));
    }
    else
    {
        p.setBrush(QColor(99,103,106));
    }
    p.drawRect(this->rect());
    p.end();
}
