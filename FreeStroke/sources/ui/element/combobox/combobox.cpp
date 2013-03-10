#include "../../../../includes/ui/element/combobox/combobox.h"
#include "../../../../includes/common/utils.h"

#include <QtGui/QPainter>
#include <QtDebug>

ComboBox::ComboBox(QWidget * w) : QComboBox(w), Element(this)
{
    QFont f = Utils::getFont();
    f.setWeight(QFont::Bold);
    this->setFont(f);

    this->setFixedHeight(25);
    //this->setMinimumWidth(90);
    this->setCursor(Qt::PointingHandCursor);
    this->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    pixmap = new QPixmap(Utils::getResourcesDirectory()+"combobox.png");
}

void ComboBox::paintEvent(QPaintEvent * e)
{
    Q_UNUSED(e);

    QPainter p(this);

    QRect rect = this->rect();

    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);

    p.setBrush(QColor(255, 255, 255, 0.6*255));
    p.drawRoundedRect(rect, 4, 4);

    rect.setHeight(rect.height()-1);
    p.setBrush(QColor("#959595"));
    p.drawRoundedRect(rect, 4, 4);

    p.setBrush(QColor("#e6e6e6"));
    p.drawRoundedRect(1, 1, rect.width() -2, rect.height() -2, 3, 3);

    p.setRenderHint(QPainter::Antialiasing, false);

    p.setPen(QColor(0, 0, 0, 0.4*255));
    p.drawLine(rect.width() - 23, 1, rect.width() - 23, rect.height() - 2);
	
    p.setPen(QColor(255, 255, 255, 0.6*255));
    p.drawLine(rect.width() - 22, 1, rect.width() - 22, rect.height() - 2);

    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 0.08*255));
    p.drawRect(rect.width() - 21, 1, rect.width() - 21, rect.height() - 2);

    p.setPen(QColor(255,255,255,0.8*255));
    p.drawText(0, 0, rect.width() - 22, rect.height() + 3, Qt::AlignCenter, this->currentText());
    p.translate(0,-1);
    p.setPen(QColor("#535353"));
    p.drawText(0, 0, rect.width() - 22, rect.height() + 3, Qt::AlignCenter, this->currentText());

    p.setRenderHint(QPainter::Antialiasing, true);

    p.drawPixmap(rect.width()- 23, 1, 25, 25, *this->pixmap);

    p.end();
}
