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
#include "../../includes/ui/glview/openglview.h"

#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>

#include <QtCore/QDebug>

OpenGlView::OpenGlView(int pFramesPerSecond, QWidget *parent) : QGLWidget(parent)
{
    if(pFramesPerSecond == 0)
    {
        timer = NULL;
    }
    else
    {
        int second = 1000; // 1 second = 1000 ms
        this->timerInterval = second / pFramesPerSecond;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        timer->start(this->timerInterval);
    }
}

QTimer *OpenGlView::getTimer()
{
    return this->timer;
}

int OpenGlView::getTimerInterval()
{
    return this->timerInterval;
}

void OpenGlView::timeOutSlot()
{
    this->update();
    this->repaint();
}
