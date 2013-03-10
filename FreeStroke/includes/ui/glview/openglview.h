/*!
 * \file openglview.h
 * \brief The OpenGlView class is the container of the GlView
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QtOpenGL>

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
