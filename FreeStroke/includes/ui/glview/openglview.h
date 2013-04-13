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
/*!
 * \file openglview.h
 * \brief The OpenGlView class is the container of the GlView
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QtOpenGL>

#include <math.h>

#ifdef Q_OS_MAC
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

/*!
 * \brief The OpenGlView class is the container of the GlView
 */
class OpenGlView : public QGLWidget
{
    Q_OBJECT
public:
    /*!
     * \brief default OpenGlView constructor
     * \param pFramesPerSecond the desired FPS
     * \param parent the container QWidget parent
     */
    OpenGlView(int pFramesPerSecond = 25, QWidget *parent = 0);
    virtual void initializeGL() = 0;
    virtual void resizeGL(int pWidth, int pHeight) = 0;
    virtual void paintGL() = 0;
    virtual void update() = 0;
    QTimer *getTimer();
    int getTimerInterval();

public slots:
    virtual void timeOutSlot();

private:
    QTimer *timer;
    int     timerInterval;
};

#endif // OPENGLVIEW_H
