#ifndef VIDEOCOMPONENT_H
#define VIDEOCOMPONENT_H

#include "../../includes/ui/element/button/playbuttonelement.h"

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QAbstractButton>
#include <QtGui/QMovie>

/*!
 * \brief Encapsulate
 */
class VideoComponent : public QLabel
{
    Q_OBJECT
public:
    explicit VideoComponent(const QString &pFileName, QWidget *parent = 0);
private:
    PlayButtonElement *button;

private slots:
    void videoStateChanged(QMovie::MovieState);
    void startVideo();
    void pauseVideo();
    void stopVideo();
};

#endif // VIDEOCOMPONENT_H
