#include "../../includes/ui/topbar/topbar.h"

#include <QtGui/QPainter>
#include <QtGui/QHBoxLayout>

TopBar::TopBar(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(50);

    group = new QButtonGroup(this);
    group->setExclusive(true);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignHCenter);
}

void TopBar::addButton(MenuButtonElement *pButton)
{
    group->addButton(pButton);
    QHBoxLayout *layout = (QHBoxLayout*)this->layout();
    layout->addWidget(pButton);
}

void TopBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setPen(Qt::NoPen);

    QLinearGradient g(0, 0, 0, this->height());
    g.setColorAt(0, QColor("#e8e8e8"));
    g.setColorAt(0.01, QColor("#ebebeb"));
    g.setColorAt(1, QColor("#b2b2b2"));
    p.setBrush(g);

    p.drawRect(this->rect());

    p.setPen(QColor("#7d7d7d"));
    p.drawLine(0, this->height()-1, this->width(), this->height()-1);
    p.end();
}
