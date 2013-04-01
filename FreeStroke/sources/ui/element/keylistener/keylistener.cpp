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
#include "../../../../includes/ui/element/keylistener/keylistener.h"
#include "../../../../includes/common/utils.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QPainter>
#include <QtGui/QtEvents>

#include <QtCore/QDebug>

#include "../../includes/ui/element/keylistener/keyconverter.h"

Key::Key(QString pKey, QWidget *parent) : QWidget(parent)
{
    this->key = pKey;

    int textWidth = fontMetrics().size(0, this->key).width() + 15;
    this->setFixedSize(textWidth, this->parentWidget()->size().height() - 7);
}

QString Key::getKey()
{
    return this->key;
}

void Key::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);

    p.setBrush(QColor(0, 0, 0, 0.3 * 255));
    p.drawRoundedRect(0, 0, this->width(), this->height(), 4, 4);

    QLinearGradient gradient(1, 2, 1, this->size().height() - 3);
    gradient.setColorAt(0, QColor("#e8e8e8"));
    gradient.setColorAt(1, QColor("#dbdbdb"));
    p.setBrush(gradient);
    p.drawRoundedRect(1, 1, this->width() - 2, this->height() - 2, 4, 4);

    //p.setBrush(QColor(255, 255, 255));
    //p.drawRoundedRect(1, 1, this->width() -2, this->height() -3, 4, 4);

    p.setPen(Qt::black);
    p.drawText(this->rect(), Qt::AlignCenter, this->key);

    p.end();
}

KeyListener::KeyListener(QWidget *parent) : QWidget(parent), Element(this)
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

    /* Create registered keys list */
    this->keys = new QList<Key*>();
    this->oldKeys = new QList<Key*>();

    /* Setup layout */
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(1);
    layout->setContentsMargins(4, 0, 20, 0);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

QString KeyListener::getKeys()
{
    QString s;
    for(int i=0; i<this->keys->count(); i++)
    {
        s.append(this->keys->at(i)->getKey());
        if (i<this->keys->count()-1)
        {
            s.append("\t");
        }
    }
    return s;
}

void KeyListener::setKeys(QString pKeys)
{
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();

    this->clearKeys();
    QStringList listKeys = pKeys.split("\t");
    foreach(QString s, listKeys)
    {
        this->keys->append(new Key(s, this));
        layout->addWidget(this->keys->last());
    }
}

void KeyListener::clearKeys()
{
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    for(int i = this->keys->count() - 1; i >= 0; i--)
    {
        layout->removeWidget(this->keys->at(i));
        this->keys->at(i)->hide();
        this->keys->removeAt(i);
    }
}

void KeyListener::keyPressEvent(QKeyEvent *e)
{
    e->ignore();
    this->clearKeys();
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    QString key = KeyConverter::textFromKey((Qt::Key)e->key());

    if (e->modifiers() & Qt::ShiftModifier && e->key() != Qt::Key_Shift)
    {
        this->keys->append(new Key(KeyConverter::textFromKey(Qt::Key_Shift), this));
        layout->addWidget(this->keys->last());
    }
    if (e->modifiers() & Qt::AltModifier && e->key() != Qt::Key_Alt)
    {
        this->keys->append(new Key(KeyConverter::textFromKey(Qt::Key_Alt), this));
        layout->addWidget(this->keys->last());
    }
    if (e->modifiers() & Qt::ControlModifier && e->key() != Qt::Key_Control)
    {
        this->keys->append(new Key(KeyConverter::textFromKey(Qt::Key_Control), this));
        layout->addWidget(this->keys->last());
    }
    if (e->modifiers() & Qt::MetaModifier && e->key() != Qt::Key_Meta)
    {
        this->keys->append(new Key(KeyConverter::textFromKey(Qt::Key_Meta), this));
        layout->addWidget(this->keys->last());
    }
    this->keys->append(new Key(key, this));
    layout->addWidget(this->keys->last());
}

void KeyListener::focusOutEvent(QFocusEvent *e)
{
    bool flagHasEmit = false;

    for(int i = 0; i < this->keys->count() && !flagHasEmit; i++)
    {
        if(!this->oldKeys->contains(this->keys->at(i)))
        {
            flagHasEmit = true;
            emit(keysChanged());
        }
        QWidget::focusOutEvent(e);
    }
}

void KeyListener::focusInEvent(QFocusEvent *e)
{
    this->oldKeys->clear();
    foreach(Key* k, *this->keys)
    {
        this->oldKeys->append(k);
    }
    QWidget::focusOutEvent(e);
}


void KeyListener::mousePressEvent(QMouseEvent *e)
{
    this->setFocus();
    e->accept();
}

void KeyListener::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

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

    if (this->hasFocus())
    {
        p.setBrush(QColor(131, 131, 131, 0.4 * 255));
    }
    else
    {
        p.setBrush(QColor(255, 255, 255));
    }
    p.drawRoundedRect(1, 1, this->width() -2, this->height() -3, 4, 4);

    p.end();
}

