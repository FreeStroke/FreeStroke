#include "../../../../includes/ui/element/button/menubuttonelement.h"
#include "../../../../includes/common/utils.h"

#include <QtGui/QAbstractButton>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

MenuButtonElement::MenuButtonElement(QPixmap pIcon, QPixmap pIconSelected, QWidget * parent) : QAbstractButton(parent), Element(this)
{
    this->setFixedWidth(49);
    this->setFixedHeight(53);

    this->setCheckable(true);
    this->setChecked(false);
    this->isLast = false;
    this->pixmap = new QPixmap(pIcon);
    this->pixmapSelected = new QPixmap(pIconSelected);

    this->pixmapBackgroundSelected = new QPixmap(Utils::getResourcesDirectory()+"topbar-button-selected.png");

    this->setCursor(Qt::PointingHandCursor);
}

void MenuButtonElement::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        this->setSelected(true);
        this->repaint();

        QAbstractButton::mousePressEvent(e);
    }
}

void MenuButtonElement::setPosition(int pX, int pY)
{
    this->setGeometry(pX, pY, this->geometry().width(), this->geometry().height());
}

void MenuButtonElement::setSelected(bool pSelected)
{
    this->setChecked(pSelected);
}

void MenuButtonElement::setLast(bool pLast)
{
    this->isLast = pLast;
}

void MenuButtonElement::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient g(0, 0, 0, this->height());
    g.setColorAt(0, QColor(140, 140, 140, 0));
    g.setColorAt(0.5, QColor(140, 140, 140, 0.30*255));
    g.setColorAt(1, QColor(140, 140, 140, 255));
    p.setBrush(g);

    // Background if selected
    if (this->isChecked())
    {
        p.drawRect(this->rect());
    }

    p.drawRect(0,0,1,this->height());

    int xOffsetLeft=1;
    if (this->isLast)
    {
        p.drawRect(this->width()-1,0,1,this->height());
        xOffsetLeft=2;
    }

    // White border
    g = QLinearGradient(0, 0, 0, this->height());
    g.setColorAt(0, QColor(255, 255, 255, 0));
    g.setColorAt(0.3, QColor(255, 255, 255, 0.2*255));
    g.setColorAt(1, QColor(255, 255, 255, 0.3*255));
    p.setBrush(g);

    p.drawRect(1, 0, 1, this->height());
    p.drawRect(this->width()-xOffsetLeft, 0, 1, this->height());

    p.setBrush(QColor(255, 255, 255, 0.3*255));
    if (this->isLast)
    {
        xOffsetLeft=4;
    }
    else
    {
        xOffsetLeft=3;
    }
    p.drawRect(2, this->height()-1, this->width()-xOffsetLeft, 1);

    // Icon
    if (this->isChecked())
    {
        p.drawPixmap(this->width()/2-this->pixmapSelected->width()/2,
                     this->height()/2-this->pixmapSelected->height()/2,
                     this->pixmapSelected->width(), this->pixmapSelected->height(), *this->pixmapSelected);
        p.drawPixmap(this->rect(), *this->pixmapBackgroundSelected);
    }
    else
    {
        p.drawPixmap(this->width()/2-this->pixmap->width()/2,
                     this->height()/2-this->pixmap->height()/2,
                     this->pixmap->width(), this->pixmap->height(), *this->pixmap);
    }

    p.end();
}
