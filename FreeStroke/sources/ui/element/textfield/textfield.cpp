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
#include "../../../../includes/ui/element/textfield/textfield.h"
#include "../../../../includes/common/utils.h"

TextField::TextField(QWidget *parent) : QLineEdit(parent), Element(this)
{
    /* Set font */
    QFont f = Utils::getFont();
    this->setFont(f);
    this->setFixedHeight(25);

    /* Remove focus on Mac */
    this->setAttribute(Qt::WA_MacShowFocusRect, false);

    /* Clear background and left/right padding text */
    this->setStyleSheet("QLineEdit { background: transparent; border: none; padding-left: 3px; padding-right: 5px; color: #747474; }");

    this->setMinimumWidth(50);

    this->setAcceptDrops(true);
    this->setDragEnabled(true);
}

void TextField::setPosition(int pX, int pY)
{
    this->setGeometry(pX, pY, this->geometry().width(), this->geometry().height());
}

void TextField::setText(QString pText)
{
    QLineEdit::setText(pText);
}

void TextField::dragEnterEvent(QDragEnterEvent *e)
{
    // Accept just text/uri-list mime format
    if (e->mimeData()->urls().size() == 1 && e->mimeData()->urls().at(0).scheme() == "file")
    {
        e->acceptProposedAction();
        e->accept();
        return;
    }
    e->ignore();
}

void TextField::dropEvent(QDropEvent *e)
{
    if (e->mimeData()->urls().size() == 1 && e->mimeData()->urls().at(0).scheme() == "file")
    {
        this->setText(e->mimeData()->urls().at(0).path());
        e->acceptProposedAction();
        e->accept();
        return;
    }
    e->ignore();
}

void TextField::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);

    p.setBrush(QColor(255, 255, 255, 0.6 * 255));
    p.drawRoundedRect(0, 0, this->width(), this->height(), 4, 4);

    QLinearGradient gradient(1, 2, 1, this->size().height() - 3);
    gradient.setColorAt(0, QColor("#8b8b8b"));
    gradient.setColorAt(1, QColor("#a8a8a8"));
    p.setBrush(gradient);
    p.drawRoundedRect(0, 0, this->width(), this->height() -1, 4, 4);

    p.setBrush(QColor(255, 255, 255));
    p.drawRoundedRect(1, 1, this->width() -2, this->height() -3, 4, 4);

    

    QLineEdit::paintEvent(e);
}

void TextField::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    emit lostFocus();
}
