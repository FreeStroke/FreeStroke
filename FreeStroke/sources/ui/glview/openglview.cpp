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
