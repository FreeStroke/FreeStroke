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
#include "../../../../includes/ui/element/switcher/switcher.h"
#include "../../../../includes/common/utils.h"

#include <QtGui/QWidget>
#include <QtGui/QAbstractButton>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtCore/QDebug>
#include <QtGui/QApplication>
#include <QtCore/QPropertyAnimation>

Cursor::Cursor(QWidget * parent) : QWidget(parent)
{
    this->setFixedSize(parent->minimumHeight()-1, parent->minimumHeight()-1);
    this->setCursor(Qt::PointingHandCursor);
}

void Cursor::mousePressEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton)
    {
        mMousePos = e->pos();
        mOriginPos = this->pos();
    }
}

void Cursor::mouseMoveEvent(QMouseEvent * e)
{
    if (e->buttons() == Qt::LeftButton)
    {
        Switcher *switcher = (Switcher *)this->parentWidget();
        QPoint currentMousePos = this->mapTo(switcher, e->pos());
        QPoint currentPos = currentMousePos - mMousePos;

        if (currentPos.x() < 0)
            currentPos.setX(0);
        else if (currentPos.x() > (switcher->width() - this->width()))
            currentPos.setX(switcher->width() - this->width());

        if ((currentPos.x() + (this->width() / 2)) > (switcher->width() / 2))
            switcher->setState(true, false);
        else if ((currentPos.x() + (this->width() / 2)) < (switcher->width() / 2))
            switcher->setState(false, false);

        this->move(currentPos.x(), this->pos().y());
    }
}

void Cursor::mouseReleaseEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton)
    {
        Switcher *switcher = (Switcher *)this->parentWidget();

        if (switcher->state() && (this->pos() == QPoint(switcher->width() - this->width(), 0)))
            return;
        if (!switcher->state() && (this->pos() == QPoint(0, 0)))
            return;

        QPropertyAnimation * a = new QPropertyAnimation(this, "pos");
        a->setStartValue(this->pos());

        if (switcher->state())
            a->setEndValue(QPoint(switcher->width() - this->width(), 0));
        else
            a->setEndValue(QPoint(0, 0));

        a->setEasingCurve(QEasingCurve::Linear);
        a->setDuration(0);
        a->start(QAbstractAnimation::DeleteWhenStopped);

        switcher->eventToggle(!switcher->state());
    }
}

void Cursor::paintEvent(QPaintEvent * e)
{
    Q_UNUSED(e);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);

    p.setBrush(QColor(0, 0, 0, 0.4*255));
    p.drawEllipse(0, 0, this->width(), this->height());

    p.setBrush(QColor("#f5f8f9"));
    p.drawEllipse(1, 1, this->width() - 2, this->height() - 2);

    QLinearGradient g(1, 2, 1, this->height() - 3);
    g.setColorAt(0, QColor("#fefefe"));
    g.setColorAt(1, QColor("#ebebeb"));

    p.setBrush(g);
    p.drawEllipse(1, 2, this->width() - 2, this->height() - 3);

    p.setBrush(QColor(0, 0, 0, 0.45*255));
    p.drawEllipse(this->width()/2-(this->width()/2 - 2)/2, this->height()/2-(this->height()/2 - 2)/2, this->width()/2 - 2, this->height()/2 - 2);

    g = QLinearGradient(0, 0, 1, this->height());
    g.setColorAt(0, QColor("#474747"));
    g.setColorAt(1, QColor("#e0e0e0"));

    p.setBrush(g);
    p.drawEllipse(this->width()/2 - (this->width()/2 - 2)/2 + 1,
                  this->height()/2 - (this->height()/2 - 4)/2,
                  this->width()/2 - 4,
                  this->height()/2 - 4);

    p.end();
}

Switcher::Switcher(QWidget * parent, bool pState) : QAbstractButton(parent), Element(this)
{
    this->setFixedSize(50, 25);

    this->setCursor(Qt::PointingHandCursor);

    QFont f = Utils::getFont();
    this->setFont(f);

    mState = pState;

    this->labelTrue = new Label("I", this);
    this->labelFalse = new Label("O", this);
    this->labelTrue->setGeometry(this->labelTrue->x()+this->labelTrue->width()/2,this->labelTrue->y(),this->labelTrue->width()/2,this->labelTrue->height());
    this->labelFalse->resize(this->labelFalse->width()/2, this->labelFalse->height());

    cursor = new Cursor(this);
    if (!mState)
        cursor->move(this->width() - cursor->width(), 0);
    else
        cursor->move(0, 0);

    connect(this, SIGNAL(clicked()), this, SLOT(toggleState()));
}

void Switcher::eventToggle(bool pState)
{
    emit toggle(pState);
}

void Switcher::setState(bool pState, bool pMoveCursor)
{
    this->mState = pState;

    if (pMoveCursor)
    {
        QPropertyAnimation * a = new QPropertyAnimation(cursor, "pos");
        a->setStartValue(cursor->pos());

        if (!mState)
            a->setEndValue(QPoint(this->width() - cursor->width(), 0));
        else
            a->setEndValue(QPoint(0, 0));

        a->setEasingCurve(QEasingCurve::Linear);
        a->setDuration(120);
        a->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

bool Switcher::state()
{
    return mState;
}

void Switcher::toggleState()
{
    this->setState(!this->state());
    this->eventToggle(this->state());
}

void Switcher::paintEvent(QPaintEvent * e)
{
    Q_UNUSED(e);

    int extRadius = 12;
    int intRadius = 10;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);

    QRect rect = this->rect();
    rect.setHeight(rect.height()-1);

    p.translate(0, 1);
    p.setBrush(QColor(255,255,255, 0.6*255));
    p.drawRoundedRect(rect, extRadius, extRadius);

    p.translate(0, -1);
    QLinearGradient gradient(1, 2, 1, this->size().height() - 3);
    gradient.setColorAt(0, QColor("#8b8b8b"));
    gradient.setColorAt(1, QColor("#a8a8a8"));
    p.setBrush(gradient);
    p.drawRoundedRect(rect, extRadius, extRadius);

    p.setBrush(QColor("#ffffff"));
    p.drawRoundedRect(1, 1, rect.width() - 2, rect.height() - 2, extRadius, extRadius);

    QLinearGradient g(1, 2, 1, this->height() - 3);
    g.setColorAt(0, QColor("#f2f2f2"));
    g.setColorAt(1, QColor("#ebebeb"));

    p.setBrush(g);
    p.drawRoundedRect(1, 2, rect.width() - 2, rect.height() - 3, extRadius, extRadius);

    p.setBrush(QColor("#b9b9b9"));
    p.drawRoundedRect(1, 1, this->cursor->pos().x()+this->cursor->size().width() - 2, rect.height() - 2, intRadius, intRadius);

    p.setBrush(QColor("#e4e4e4"));
    p.drawRoundedRect(this->cursor->pos().x(), 1, rect.width() - this->cursor->pos().x() - 1, rect.height() - 2, intRadius, intRadius);

    if (!mState)
        p.translate(12, 0);
    else
        p.translate(-12, 0);
    p.setPen(QColor("#333333"));

    if (!mState)
        p.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, this->text());
    else
        p.drawText(rect, Qt::AlignRight | Qt::AlignVCenter, this->text());

    p.end();
}
