#include "../../../../includes/ui/element/label/label.h"
#include "../../../../includes/common/utils.h"


#include <QtGui/QPainter>
#include <QtCore/QDebug>


Label::Label(QString pText, QWidget *parent) : QLabel(pText, parent), Element(this)
{
    this->backgroundColor = QColor(255,255,255,0);
    this->textColor = QColor("#636363");
    this->resize(parent->size());
    this->setWordWrap(true);
    this->setAlignment(Qt::AlignCenter);
    this->setEnabled(false);
    this->setMouseTracking(false);

    QFont f = Utils::getFont();
    f.setWeight(QFont::Bold);
    this->setFont(f);
    this->paintShadow = true;
}

Label::Label(QString pText, QColor pBackground, QWidget *parent) : QLabel(pText, parent), Element(this)
{
    this->backgroundColor = pBackground;
    this->textColor = QColor("#636363");
    this->resize(parent->size());
    this->setWordWrap(true);
    QFont f = Utils::getFont();
    f.setBold(true);
    this->setFont(f);
    this->paintShadow = true;
}

void Label::setPaintShadow(bool pPaintShadow)
{
    this->paintShadow = pPaintShadow;
}

void Label::changeFontSize(int pSize)
{
    QFont fText = this->font();
    fText.setPixelSize(pSize);
    this->setFont(fText);
}

void Label::setTextColor(QColor pColor)
{
    this->textColor = pColor;
}

void Label::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing, false);
    p.setPen(Qt::NoPen);

    p.setBrush(this->backgroundColor);
    p.drawRect(this->rect());

    p.setPen(QColor(255,255,255,0.6*255));
    p.translate(0,1);
    if (this->paintShadow)
    {
        p.drawText(this->rect(), this->alignment(), this->text());
    }

    p.setPen(this->textColor);
    p.translate(0,-1);
    p.drawText(this->rect(), this->alignment(), this->text());

    if(this->pixmap() != NULL)
    {
        p.drawPixmap(0,0,this->width(),this->height(),*this->pixmap());
    }

    p.end();
}

