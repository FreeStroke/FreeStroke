#include "../../includes/ui/bottombar/bottombarseparator.h"

#include <QtGui/QPainter>
#include <QtGui/QHBoxLayout>

BottomBarSeparator::BottomBarSeparator(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background: transparent;");
    this->setFixedSize(1, parent->height());
}

void BottomBarSeparator::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 0.2*255));
    p.drawRect(0, 2, this->width(), this->height() - 2);
    p.end();
}
