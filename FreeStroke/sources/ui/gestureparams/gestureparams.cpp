#include "../../includes/ui/gestureparams/gestureparams.h"

#include <QtGui/QPainter>
#include <QtGui/QHBoxLayout>

GestureParams::GestureParams(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(35);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 0, 10, 0);
    layout->setAlignment(Qt::AlignVCenter);
}

void GestureParams::addElement(Element *pElement)
{
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    layout->addWidget(pElement->getWidget());
}

void GestureParams::addSpacer()
{
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    layout->addSpacerItem(new QSpacerItem(this->width(), this->height(), QSizePolicy::MinimumExpanding));
}

void GestureParams::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setPen(Qt::NoPen);

    p.setBrush(QColor("#dbdbdb"));
    p.drawRect(this->rect());

    p.setPen(QColor("#7d7d7d"));
    p.drawLine(0, this->height()-1, this->width(), this->height()-1);
    p.end();
}
