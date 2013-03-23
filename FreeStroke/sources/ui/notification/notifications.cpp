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
#include "../../includes/ui/notification/notifications.h"
#include "../../includes/mainwindow.h"

#include <QtCore/QDebug>
#include <QtCore/QPropertyAnimation>
#include <QtGui/QSystemTrayIcon>

#ifdef Q_OS_DARWIN
#include "../../includes/others/mac/mac.h"
#endif

Notifications * Notifications::mAdress = 0;

Notifications::Notifications(QWidget * w) : QWidget(w)
{
    this->setFixedWidth(300);

    mNotificationList = new QList<Notification *>;

    mAdress = this;

    this->move(w->width() - this->width() - 20, 60);
    this->organize();
}

Notification * Notifications::add(Notification::Action t, const  QString & m, int ms)
{
    Notifications * nInstance = Notifications::address();
    if (nInstance == NULL)
    {
        return NULL;
    }
    MainWindow *mw =  (MainWindow *) nInstance->parentWidget();
    if ( mw == NULL)
    {
        qDebug() << "MainWindow null";
        return NULL;
    }
    if(mw->isVisible() == false)
    {
        QSystemTrayIcon::MessageIcon icon;
        switch (t)
        {
        case Notification::Error:
            icon = QSystemTrayIcon::Critical;
            break;
        case Notification::Wait:
            icon = QSystemTrayIcon::Warning;
            break;
        default:
            icon = QSystemTrayIcon::Information;
            break;
        }
#ifdef Q_OS_DARWIN
        if (QSysInfo::MacintoshVersion >= QSysInfo::MV_10_7)
        {
            Mac *mac = new Mac(0);
            mac->showNotification((char*)"FreeStroke", (char*)QString(m).toUtf8().constData());
            delete mac;
        }
        else
        {
            mw->showNotif(QString("FreeStroke"),m, icon,ms);
        }
#else
        mw->showNotif(QString("FreeStroke"),m, icon,ms);
#endif
        return NULL;
    }

#ifdef Q_OS_DARWIN
    if (QSysInfo::MacintoshVersion >= QSysInfo::MV_10_7)
    {
        Mac *mac = new Mac(0);
        mac->showNotification((char*)"FreeStroke", (char*)QString(m).toUtf8().constData());
        delete mac;
        return NULL;
    }
    else
    {
        Notification * n = new Notification(t, m, ms, nInstance);
        nInstance->notificationList()->push_back(n);
        nInstance->organize();
        return n;
    }
#else
    Notification * n = new Notification(t, m, ms, nInstance);
    nInstance->notificationList()->push_back(n);
    nInstance->organize();
    return n;
#endif
}

void Notifications::organize()
{
    if (mNotificationList->count() == 0)
    {
        this->hide();
        return;
    }

    QPropertyAnimation * size = new QPropertyAnimation(this, "size");
    size->setDuration(80);
    size->setStartValue(QSize(this->size()));
    size->setEndValue(QSize(this->minimumWidth(), mNotificationList->count() * 80));
    size->setEasingCurve(QEasingCurve::Linear);
    size->start(QAbstractAnimation::DeleteWhenStopped);

    Notification * n;
    for (int i = 0; i < mNotificationList->count(); i++)
    {
        n = mNotificationList->at(i);
        n->move(0, i*n->minimumHeight());
        if (n == mNotificationList->last())
            n->setLast(true);
        else
            n->setLast(false);
    }

    //this->resize(this->minimumWidth(), mNotificationList->count() * 80);

    if (!this->isVisible())
        this->show();
}

QList<Notification *> * Notifications::notificationList()
{
    return mNotificationList;
}

Notifications * Notifications::address()
{
    return mAdress;
}

void Notifications::paintEvent(QPaintEvent * e)
{
    QPainter p(this);

    p.setPen(Qt::NoPen);
    p.setRenderHint(QPainter::Antialiasing);

    p.setBrush(QColor("#d9d9d9"));
    p.drawRoundedRect(this->rect(), 6, 6);

    p.setBrush(QColor("#ffffff"));
    p.drawRoundedRect(1, 1, this->width() - 2, this->height() - 2, 6, 6);

    QLinearGradient g(this->rect().topLeft(), this->rect().bottomLeft());
    g.setColorAt(0, QColor("#f5f5f5"));
    g.setColorAt(1, QColor("#e5e5e5"));

    p.setBrush(g);
    p.drawRoundedRect(1, 2, this->width() - 2, this->height() - 3, 6, 6);

    p.end();
}
