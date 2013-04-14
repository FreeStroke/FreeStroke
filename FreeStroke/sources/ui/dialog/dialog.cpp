/*
* Projet de fin d'études LastProject de
* Adrien Broussolle
* Camille Darcy
* Guillaume Demurger
* Sylvain Fay-Chatelard
* Anthony Fourneau
* Aurèle Lenfant
* Adrien Madouasse
*
* Copyright (C) 2013 Université Paris-Est Marne-la-Vallée
*
* FreeStroke is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
*/
#include "../../includes/ui/dialog/dialog.h"
#include "../../includes/common/utils.h"

/* Dialog */

QPixmap * Dialog::pixmapInfos = 0;
QPixmap * Dialog::pixmapTick = 0;
QPixmap * Dialog::pixmapCross = 0;
QPixmap * Dialog::pixmapWarn = 0;

Dialog::Dialog(QString pTitle, QWidget * parent) : QDialog(parent)
{
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setMinimumSize(340, 93);
    this->setMaximumSize(800, 600);

    buttonClose = new QPushButton(QIcon(Utils::getResourcesDirectory() + "dialog-close.png"), "", this);
    buttonClose->setStyleSheet("background: transparent; border: none;");
    buttonClose->setIconSize(QSize(23, 21));
    buttonClose->setCursor(Qt::PointingHandCursor);
    buttonClose->resize(23, 21);
    buttonClose->show();

    mButtons = new QList<DialogButton *>;

    connect(buttonClose, SIGNAL(clicked()), this, SLOT(reject()));

    title = pTitle;
    labelIcon = 0;
    labelQuick = 0;
    pType = 0;
    pLabelText = 0;
    //mFirstEffect = 0;
    //mSecondEffect = 0;

    if( pixmapInfos == 0)
    {
        pixmapInfos = new QPixmap(Utils::getResourcesDirectory() + "infos.png");
        pixmapTick = new QPixmap(Utils::getResourcesDirectory() + "tick.png");
        pixmapCross = new QPixmap(Utils::getResourcesDirectory() + "cross.png");
        pixmapWarn = new QPixmap(Utils::getResourcesDirectory() + "warn.png");
    }
    labelDialogButtonBoxBg = new QBrush(QPixmap(Utils::getResourcesDirectory() + "dialog-button-box-bg.png"));

    origin = QPoint();
    anchor = QPoint();
    moveAllowed = false;
}

Dialog::~Dialog()
{
}

void Dialog::mousePressEvent(QMouseEvent * event)
{
    if (event->button() != Qt::LeftButton)
    {
        return;
    }
    anchor = event->globalPos();
    origin = this->pos();

    QRect r(this->pos(), QPoint(this->pos().x() + this->width(), this->pos().y() + 40));
    if (r.intersects(QRect(anchor, anchor)))
    {
        moveAllowed = true;
    }
}

void Dialog::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() != Qt::LeftButton)
    {
        return;
    }

    if (!moveAllowed)
    {
        return;
    }

    QPoint m = event->globalPos() - anchor;
    QPoint p = origin + m;

    if (p.x() < 0)
    {
        p.setX(0);
    }
    if (p.y() < 0)
    {
        p.setY(0);
    }

    this->move(p);
}

void Dialog::mouseReleaseEvent(QMouseEvent * event)
{
    Q_UNUSED(event);
    moveAllowed = false;
}

Dialog::DialogCode Dialog::displayNotification(Dialog::Type pType, QString pTitle, QString pContent)
{
    this->pType = 1;

    if(labelIcon==0)
    {
        labelIcon = new QLabel(this);
    }
    if (pType == Dialog::Information)
    {
        labelIcon->setPixmap(*pixmapInfos);
    }
    else if (pType == Dialog::Success)
    {
        labelIcon->setPixmap(*pixmapTick);
    }
    else if (pType == Dialog::Error)
    {
        labelIcon->setPixmap(*pixmapCross);
    }
    else if (pType == Dialog::Warning)
    {
        labelIcon->setPixmap(*pixmapWarn);
    }
    labelIcon->resize(48, 48);
    labelIcon->move(20, 40);
    labelIcon->show();

    if(labelQuick==0)
    {
        labelQuick = new QLabel(this);
        labelQuick->setWordWrap(true);
    }

    labelQuick->setText(pTitle);
    if (pType == Dialog::Information)
    {
        labelQuick->setStyleSheet("QLabel { color: #c3f0fd; font-weight: bold; font-family: Arial; font-size: 17px; }");
    }
    else if (pType == Dialog::Success)
    {
        labelQuick->setStyleSheet("QLabel { color: #cafdc3; font-weight: bold; font-family: Arial; font-size: 17px; }");
    }
    else if (pType == Dialog::Error)
    {
        labelQuick->setStyleSheet("QLabel { color: #fdd1d3; font-weight: bold; font-family: Arial; font-size: 17px; }");
    }
    else if (pType == Dialog::Warning)
    {
        labelQuick->setStyleSheet("QLabel { color: #fff6bf; font-weight: bold; font-family: Arial; font-size: 17px; }");
    }
    int l = labelQuick->heightForWidth(550 - 88 - 20);
    labelQuick->resize(550 - 88 - 20, l);
    labelQuick->move(88, 20);

    labelQuick->show();

    if( pLabelText==0)
    {
        pLabelText = new QLabel(this);
        pLabelText->setWordWrap(true);
    }
    pLabelText->setText(pContent);
    pLabelText->setStyleSheet("QLabel { color: #ffffff; font-size: 16px; font-family: Arial; }");
    l = pLabelText->heightForWidth(550 - 88 - 20);
    pLabelText->resize(550 - 88 - 20, l);
    pLabelText->move(88, labelQuick->y() + labelQuick->height() + 10);
    pLabelText->show();

    this->resize(550, labelQuick->y() + labelQuick->height() + 10 + pLabelText->height() + 20);

    labelIcon->move(20, ((this->height() - 52) / 2) - 24);

    buttonClose->raise();

    return (QDialog::DialogCode)this->exec();
}

void Dialog::addButton(QString pText, Dialog::Role pRole, DialogButton::Type pType, bool pDefault)
{
    DialogButton * b = new DialogButton(pText, pType, this);

    if (pRole == Dialog::Accept)
    {
        connect(b, SIGNAL(clicked()), this, SLOT(accept()));
    }
    else if (pRole == Dialog::Reject)
    {
        connect(b, SIGNAL(clicked()), this, SLOT(reject()));
    }

    this->addButton(b);
    this->setFocus();
    b->setDefault(pDefault);
}

void Dialog::addButton(DialogButton * pButton)
{
    pButton->setParent(this);
    mButtons->push_back(pButton);
    this->buttonHandler();
}

void Dialog::removeButton(DialogButton * pButton)
{
    mButtons->removeOne(pButton);
    delete pButton;
    this->buttonHandler();
}

void Dialog::buttonHandler()
{
    int rightOffset = 10;
    int leftOffset = 10;

    for (int i = 0; i < mButtons->count(); i++)
    {
        if (mButtons->at(i)->type() == DialogButton::Dark || mButtons->at(i)->type() == DialogButton::Bright)
        {
            mButtons->at(i)->move(leftOffset, this->height() - 24 - (mButtons->at(i)->height() / 2));
            leftOffset += mButtons->at(i)->width() + 10;
        }
        else if (mButtons->at(i)->type() == DialogButton::Normal)
        {
            mButtons->at(i)->move(this->width() - rightOffset - mButtons->at(i)->width(), this->height() - 24 - (mButtons->at(i)->height() / 2));
            rightOffset += mButtons->at(i)->width() + 10;
        }
    }
}

void Dialog::resize(int w, int h)
{
    h += 52;
    QDialog::resize(w, h);
}

void Dialog::resize(const QSize & pSize)
{
    QDialog::resize(QSize(pSize.width(), pSize.height() + 52));
}

void Dialog::resizeEvent(QResizeEvent * event)
{
    Q_UNUSED(event);

    buttonClose->move(this->width() - buttonClose->width() - 10, 10);
    buttonHandler();
}

QPushButton * Dialog::closeButton()
{
    return buttonClose;
}

void Dialog::setTitle(QString pTitle)
{
    this->title = pTitle;
    this->update();
}

void Dialog::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);

    /* Create painter */
    QPainter p(this);

    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#3a3c3e"));
    p.drawRect(0, 0, this->width(), this->height());

    if (pType == 0)
    {
        p.setBrush(QBrush(QPixmap(Utils::getResourcesDirectory() + "dialog-title-bg.png")));
        p.drawRect(0, 0, this->width(), 50);

        QFont font = Utils::getFont();
        font.setPixelSize(22);
        font.setWeight(QFont::Bold);
        p.setFont(font);

        p.setBrush(QColor(0, 0, 0));
        p.setPen(QColor(0, 0, 0));
        p.drawText(15, 27, title);

        p.setBrush(QColor(255, 255, 255));
        p.setPen(QColor(255, 255, 255));
        p.drawText(15, 26, title);
    }

    p.setPen(Qt::NoPen);
    p.setBrush(*labelDialogButtonBoxBg);
    p.translate(0, this->height() - 52);
    p.drawRect(0, 0, this->width(), 52);
    p.translate(0, -(this->height() - 52));

    
}
