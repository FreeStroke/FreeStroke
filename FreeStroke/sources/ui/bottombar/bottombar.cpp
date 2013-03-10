
#include "../../includes/ui/bottombar/bottombar.h"

#include <QtGui/QPainter>
#include <QtGui/QHBoxLayout>

BottomBar::BottomBar(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(52);
    this->setStyleSheet("border: none;");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setContentsMargins(10, 0, 10, 0);

    this->printLeft = false;
    this->printRight = false;
    this->isTopBar = false;
}

void BottomBar::addElement(Element *pButton)
{
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    layout->addWidget(pButton->getWidget());
}

void BottomBar::addSeparator()
{
    BottomBarSeparator* sep = new BottomBarSeparator(this);
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    layout->addWidget(sep);
}

void BottomBar::addLeftLine(bool pPrint)
{
    this->printLeft = pPrint;
}

void BottomBar::addRightLine(bool pPrint)
{
    this->printRight = pPrint;
}

void BottomBar::setTopBar(bool pSetTopBar)
{
     this->isTopBar = pSetTopBar;
}

void BottomBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int offset = 0;

    if(!isTopBar)
    {
        p.setPen(QColor(0, 0, 0, 0.05*255));
        p.drawLine(0, 0, this->width(), 0);
        p.setPen(QColor(0, 0, 0, 0.2*255));
        p.drawLine(0, 1, this->width(), 1);
    }
    else
    {
        offset = 2;
    }

    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#e1e1e1"));
    p.drawRect(0, 2 - offset, this->width(), this->height());

    QLinearGradient g(0, 0, 0, this->height());
    g.setColorAt(0, QColor(255, 255, 255, 0.05*255));
    g.setColorAt(1, QColor(0, 0, 0, 0.1*255));
    p.setBrush(g);
    p.drawRect(0, 2, this->width(), this->height());

    if (this->printRight)
    {
        p.setPen(QColor(0, 0, 0, 0.2*255));
        p.drawLine(this->width() - 1, 2 - offset, this->width() - 1, this->height() - 2);
    }

    if (this->printLeft)
    {
        p.setPen(QColor(0, 0, 0, 0.1*255));
        p.drawLine(0, 2, 0, this->height() - 2);
    }
    p.end();
}
