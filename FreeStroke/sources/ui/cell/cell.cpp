#include "../../includes/ui/cell/cell.h"
#include "../../includes/common/utils.h"

#include <QtGui/QPainter>

#include <QtCore/QDebug>

#include "../../includes/ui/list/list.h"

#include "../../includes/application.h"

Cell::Cell(void* pList, int pHeight) : QAbstractButton((QWidget*)pList)
{
    this->init(pList, pHeight);
    this->record = NULL;
}

Cell::Cell(Record* pRecord, void* pList, int pHeight) : QAbstractButton((QWidget*)pList)
{
    this->init(pList, pHeight);
    this->setText(pRecord->getName());
    this->record = pRecord;
    this->gesture = pRecord->getGestures()->at(0);
    this->glView->setGesture(this->gesture);
}

Cell::Cell(HistoryRecord* pHistoryRecord, void *pList, int pHeight) : QAbstractButton((QWidget*)pList)
{
    this->init(pList, pHeight);
    this->setText(pHistoryRecord->getRecordExecuted()->getName());
    this->record = NULL;
    this->gesture = pHistoryRecord->getRecordExecuted()->getGestures()->at(0);
    this->glView->setGesture(this->gesture);
    this->setDetailedText(pHistoryRecord->getExecutionDate());
}


Cell::Cell(void* pList, bool noGl) : QAbstractButton((QWidget*)pList)
{
    Q_UNUSED(noGl);
    this->list = pList;
    this->alternateColor = false;
    this->selected = false;
    this->glView = NULL;
    this->text = NULL;
    this->detailedText = NULL;
}

Cell::~Cell()
{
    //Utils::secureFree(this->record);
    //Utils::secureFree(this->historyRecord);
}

void Cell::init(void* pList, int pHeight)
{
    this->list = pList;

    this->setFixedHeight(pHeight);
    this->resize(170, pHeight);

    this->alternateColor = false;
    this->selected = false;

    /* GlView */
    this->glView = new GlView(this, GlView::SMALL);
    this->glView->setFixedSize(36, 36);
    this->glView->move(this->width() - this->glView->width() - 30 + 1, this->height()/2 - this->glView->height()/2 + 1);
    this->glView->animateOnMouseEnter(true);
    this->glView->hide();

    /* Label */
    this->text = new Label("",this);
    this->text->setAlignment(Qt::AlignVCenter);
    this->text->setTextColor(QColor(0,0,0));
    this->text->move(10, 0);
    this->text->resize(this->glView->pos().x() - 20, this->height());
    QFont fText = this->text->font();
    fText.setPixelSize(16);
    this->text->setFont(fText);

    /* Detailed Text */
    this->detailedText = new Label("",this);
    this->detailedText->setAlignment(Qt::AlignVCenter);
    this->detailedText->setTextColor(QColor(95,95,95));
    this->detailedText->move(15, 15);
    this->detailedText->resize(this->width()/3*2 - 25, this->height());
    QFont fDetailedText = this->detailedText->font();
    fDetailedText.setWeight(QFont::Normal);
    this->detailedText->setFont(fDetailedText);
}

void Cell::setText(QString pText)
{
    this->text->setText(pText);
}

Label* Cell::getDetailedText()
{
    return this->detailedText;
}

GlView* Cell::getGlView()
{
    return this->glView;
}

bool Cell::getAlternate()
{
    return this->alternateColor;
}

Gesture* Cell::getGesture()
{
    return this->gesture;
}

Record* Cell::getRecord()
{
    return this->record;
}

void Cell::setRecord(Record* pRecord)
{
    this->record = pRecord;
}


void Cell::setDetailedText(QString pDetailedText)
{
    this->detailedText->setText(pDetailedText);
    if(this->detailedText->text() != "")
    {
        this->text->move(10, -10);
        this->detailedText->move(15, 10);
    }
}

void Cell::setAlternate(bool pAlternate)
{
    this->alternateColor = pAlternate;
}

void Cell::setSelectedState(bool pSelected)
{
    this->selected = pSelected;
}

void Cell::setSelected(bool pSelected)
{
    List * l = static_cast<List*>(this->list);
    if (pSelected)
    {
        l->selectCell(this);
    }
    else
    {
        l->deselectCell(this);
    }
}

void Cell::mousePressEvent(QMouseEvent *e)
{
    if (this->detailedText->text() != "")
    {
        return;
    }
    if(this->selected)
    {
        ((List*)this->list)->deselectCell(this);
    }
    else
    {
        ((List*)this->list)->selectCell(this);
    }

//    this->setSelected(!this->selected);

    int modifiers = Application::getModifiers();
    if (modifiers & Qt::ShiftModifier)
    {
        this->setSelected(true);
    }
    QAbstractButton::mousePressEvent(e);
    e->ignore();
}

void Cell::paintEvent(QPaintEvent * e)
{
    Q_UNUSED(e);

    int translateY = 0;

    QPainter p(this);
    p.setPen(Qt::NoPen);

    if (this->selected)
    {
        p.setBrush(QColor("#5b6b96"));
    }
    else
    {
        p.setBrush(QColor("#ffffff"));
    }
    p.drawRect(this->rect());

    p.translate(0, -1);
    translateY += -1;
    p.setBrush(QColor("#cfcfcf"));
    p.drawRect(this->rect());

    p.translate(0, -1);
    translateY += -1;
    if (this->selected)
    {
        p.translate(0, 1);
        translateY += 1;
        QLinearGradient gradient(1, 2, 1, this->size().height());
        gradient.setColorAt(0, QColor("#8ca7ec"));
        gradient.setColorAt(1, QColor("#7b93cf"));
        p.setBrush(gradient);
    }
    else
    {
        if (this->alternateColor == true)
        {
            p.setBrush(QColor("#e6e6e6"));
        }
        else
        {
            p.setBrush(QColor("#e0e5e9"));
        }
    }
    p.drawRect(this->rect());

    /* GlView */
    p.translate(0, -translateY);
    QPoint pos = mapToParent(this->parentWidget()->pos());
    if (pos.y() < 0 || pos.y() > this->parentWidget()->parentWidget()->height() - this->height())
    {
        this->glView->hide();
    }
    else
    {
        this->glView->show();
        p.setBrush(QColor("#b6bbbf"));
        p.drawRoundedRect(this->glView->pos().x()-1, this->glView->pos().y()-1, this->glView->size().width()+2, this->glView->size().height()+2, 4, 4);
    }

    p.end();
}
