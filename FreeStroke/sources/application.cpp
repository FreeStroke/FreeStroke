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

#include "../../includes/application.h"
#include "../../includes/ui/element/keylistener/keylistener.h"

static bool control = false;
static bool meta = false;
static bool shift = false;

Application::Application(int &argc, char **argv) : QApplication(argc, argv)
{}

void Application::restart()
{
    //TODO missing linux
    QProcess	mProcess;
    QString str = "";
#if defined(Q_OS_WIN32)
    str = QString("\"%1\"").arg(QApplication::arguments().at(0);
#elif defined(Q_OS_DARWIN)
    str = QString(QApplication::arguments().at(0));
    str.replace(" ","\\ ");
#else
    str = QString(QApplication::arguments().at(0));
#endif
    mProcess.startDetached(str);
    QApplication::quit();
}

void Application::setModifiers(bool pCtrl, bool pShift, bool pMeta)
{
    control = pCtrl;
    shift = pShift;
    meta = pMeta;
}

Qt::KeyboardModifier Application::getModifiers()
{
    int modifiers = Qt::NoModifier;
    if (control)
    {
        modifiers |= Qt::ControlModifier;
    }
    if (shift)
    {
        modifiers |= Qt::ShiftModifier;
    }
    if (meta)
    {
        modifiers |= Qt::MetaModifier;
    }
    return (Qt::KeyboardModifier)modifiers;
}

bool Application::notify (QObject * receiver, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

        QWidget * w = QApplication::focusWidget();
        KeyListener *keyListener = dynamic_cast<KeyListener*>(w);
        if ( (keyEvent->key() == Qt::Key_Tab ||
              keyEvent->key() == Qt::Key_Backtab ||
              (keyEvent->key() == Qt::Key_Q && keyEvent->modifiers() == Qt::MetaModifier))
             && keyListener != NULL)
        {
            qDebug()<<"Tab";
            keyListener->keyPressEvent(keyEvent);
            e->ignore();
            return false;
        }
    }
    return QApplication::notify(receiver,e);
}
