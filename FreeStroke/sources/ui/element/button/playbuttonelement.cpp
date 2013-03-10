#include "../../../../includes/ui/element/button/playbuttonelement.h"
#include "../../../../includes/common/utils.h"

#include <QtGui/QPainter>

PlayButtonElement::PlayButtonElement(QWidget * parent) : QAbstractButton(parent), Element(this)
{
    this->setFixedSize(QSize(600,400));
    this->setIconSize(this->size());
    this->setCheckable(true);
    this->setChecked(false);
    this->pixmap = new QPixmap(Utils::getResourcesDirectory()+"/tuto-overlay.png");
    this->pixmapSelected = new QPixmap(Utils::getResourcesDirectory()+"/tuto-overlay-hover.png");
    this->setCursor(Qt::PointingHandCursor);
}

void PlayButtonElement::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setRenderHint(QPainter::Antialiasing, true);

    // Icon
    if (this->isChecked())
    {
        p.drawPixmap(this->width()/2-this->pixmapSelected->width()/2,
                     this->height()/2-this->pixmapSelected->height()/2,
                     this->pixmapSelected->width(), this->pixmapSelected->height(), *this->pixmapSelected);
    }
    else
    {
        p.drawPixmap(this->width()/2-this->pixmap->width()/2,
                     this->height()/2-this->pixmap->height()/2,
                     this->pixmap->width(), this->pixmap->height(), *this->pixmap);
    }

    p.end();
}
