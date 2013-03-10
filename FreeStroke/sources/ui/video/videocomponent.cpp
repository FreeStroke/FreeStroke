#include "../../includes/ui/video/videocomponent.h"
#include "../../includes/common/utils.h"

#include <QtGui/QPixmap>
#include <QtGui/QIcon>
#include <QtCore/QDebug>

VideoComponent::VideoComponent(const QString &pFileName, QWidget *parent) :
    QLabel(parent)
{
    this->setMovie(new QMovie(pFileName));
    this->button = new PlayButtonElement((QWidget*)this);
    QObject::connect(this->button, SIGNAL(clicked()), this, SLOT(startVideo()));
    QObject::connect(this->movie(), SIGNAL(stateChanged(QMovie::MovieState)), this, SLOT(videoStateChanged(QMovie::MovieState)));
    QObject::connect(this->movie(), SIGNAL(finished()), this, SLOT(stopVideo()));
}

void VideoComponent::videoStateChanged(QMovie::MovieState pState)
{
    switch(pState)
    {
    case QMovie::Running:
        this->button->setVisible(false);
        break;
    case QMovie::NotRunning:
        this->button->setVisible(true);
    }
}

void VideoComponent::startVideo()
{
    this->movie()->start();
}

void VideoComponent::stopVideo()
{
    this->movie()->stop();
}

void VideoComponent::pauseVideo()
{
    this->movie()->setPaused(true);
}
