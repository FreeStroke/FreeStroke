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
#include "../../includes/ui/list/list.h"
#include <QtGui/QKeyEvent>
#include <QtGui/QVBoxLayout>
#include <QtGui/QResizeEvent>
#include <QtGui/QPainter>

#include <QtCore/QDebug>

#include "../../includes/ui/scrollbar/scrollbar.h"
#include "../../includes/application.h"

List::List(QWidget *parent) : QWidget(parent)
{
    this->setFixedWidth(171);
    this->scroll = new QScrollArea(this);

    ScrollBar* verticalScrollBar = new ScrollBar(Qt::Vertical, this);
    this->scroll->setVerticalScrollBar(verticalScrollBar);
    this->scroll->setStyleSheet("QScrollArea {background-color: transparent; border-right: none; border-left: none; border-top: none; border-bottom: none;}");
    this->scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    this->scrollWidget = new QWidget(this);
    this->scrollWidget->setFixedWidth(this->width() - verticalScrollBar->width());
    QVBoxLayout *v = new QVBoxLayout(this->scrollWidget);
    v->setMargin(0);
    v->setSpacing(0);
    v->setContentsMargins(0,0,0,0);

    this->scroll->setWidget(this->scrollWidget);

    this->cells = new QList<Cell*>();
    this->selectedCells = new QList<Cell*>();

    this->lastIndex = 0;
    this->lastSuperiorShiftIndex = -1;
    this->lastInferiorShiftIndex = -1;
}

void List::resetFocus()
{
    QTimer::singleShot(80, this, SLOT(private_setFocus()));
}

void List::private_setFocus()
{
    this->scrollWidget->setFocus();
}

void List::keyPressEvent(QKeyEvent *e)
{
    e->ignore();
    if(this->cells->count()>0 && this->cells->at(0)->getDetailedText()->text() != "")
        return;
    if (e->key() == Qt::Key_A && (e->modifiers() & Qt::ControlModifier))
    {
        this->selectAll();
    }
}

void List::keyReleaseEvent(QKeyEvent *e)
{
    e->ignore();
    if(this->cells->count()>0 && this->cells->at(0)->getDetailedText()->text() != "")
        return;
}

void List::mousePressEvent(QMouseEvent *e)
{
    this->setFocus();
    e->accept();
}

void List::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    this->scroll->resize(this->size());
    this->scrollWidget->setFixedWidth(this->width() - ScrollBar(Qt::Vertical, this).width());
}

bool List::containsRecord(Record* pRecord)
{
    if(this->cells->count() == 0)
    {
        return false;
    }
    foreach(Cell* c, *this->cells)
    {
        if(c->getRecord()->getId() == pRecord->getId())
        {
            return true;
        }
    }
    return false;
}

void List::addCell(Cell *pCell)
{
    QVBoxLayout* layout = (QVBoxLayout*)this->scrollWidget->layout();
    layout->addWidget(pCell);
    this->cells->append(pCell);
    if (this->cells->count()%2 != 0)
    {
        pCell->setAlternate(true);
    }
    this->scrollWidget->resize(pCell->width(), pCell->height() * this->cells->count()+1);
}

void List::insertCellAtHead(Cell* pCell)
{
    QVBoxLayout* layout = (QVBoxLayout*)this->scrollWidget->layout();
    layout->insertWidget(0, pCell);
    this->cells->insert(0,pCell);

    for(int i=1; i< this->cells->count(); i++)
    {
        Cell* c = this->cells->at(i);
        c->setAlternate(!c->getAlternate());
    }
    this->scrollWidget->resize(pCell->width(), pCell->height() * this->cells->count());
}

void List::selectAll()
{
    foreach(Cell* c, *this->cells)
    {
        this->selectOneCell(c);
    }
    emit selectionChanged();
}

void List::clearListSelection(bool signal)
{
    for(int i=0; i<this->selectedCells->count(); i++)
    {
        Cell *c = this->selectedCells->at(i);
        c->setSelectedState(false);
        c->repaint();
    }
    this->selectedCells->clear();
    if (signal)
    {
        emit selectionChanged();
    }
}

void List::selectOneCell(Cell* pCell)
{
    if (!this->selectedCells->contains(pCell))
    {
        pCell->setSelectedState(true);
        this->selectedCells->append(pCell);
        pCell->repaint();
    }
}

void List::selectCell(Cell *pCell)
{
    bool shiftKey = false;
    bool ctrlKey = false;
    int modifiers = Application::getModifiers();
    if (modifiers & Qt::ShiftModifier)
    {
        shiftKey = true;
    }
    if (modifiers & Qt::ControlModifier)
    {
        ctrlKey = true;
    }
    if (ctrlKey == false && shiftKey == false)
    {
        if (this->selectedCells->contains(pCell))
        {
            return;
        }
        this->lastSuperiorShiftIndex = -1;
        this->lastInferiorShiftIndex = -1;
        this->clearListSelection(false);
        this->lastIndex = this->cells->indexOf(pCell);
        selectOneCell(pCell);
    }
    else if(ctrlKey == true)
    {
        this->lastSuperiorShiftIndex = -1;
        this->lastInferiorShiftIndex = -1;
        this->lastIndex = this->cells->indexOf(pCell);
        selectOneCell(pCell);
    }
    else if(shiftKey == true)
    {
        this->clearListSelection();
        int index = cells->indexOf(pCell);

        if(index <= this->lastIndex)
        {
            for(int i = this->lastIndex; i>=index;i--)
            {
                selectOneCell(cells->at(i));
            }
            for (int i = this->lastInferiorShiftIndex;i<index && this->lastInferiorShiftIndex != -1;i++)
            {
                selectOneCell(cells->at(i));
            }
            this->lastInferiorShiftIndex = index;
        }
        else
        {
            for(int i = this->lastIndex; i<=index;i++)
            {
                selectOneCell(cells->at(i));
            }
            for (int i = this->lastSuperiorShiftIndex;i>index && this->lastSuperiorShiftIndex != -1;i--)
            {
                selectOneCell(cells->at(i));
            }
            this->lastSuperiorShiftIndex = index;
        }
    }
    emit selectionChanged();
}

void List::removeCell(Cell *pCell)
{
    this->deselectCell(pCell);
    pCell->hide();
    QVBoxLayout* layout = (QVBoxLayout*)this->scrollWidget->layout();
    layout->removeWidget(pCell);
    this->cells->removeOne(pCell);
    for(int i = this->cells->indexOf(pCell) + 1; i<this->cells->count(); i++)
    {
        this->cells->at(i)->setAlternate(!this->cells->at(i)->getAlternate());
    }
    this->scrollWidget->resize(pCell->width(), pCell->height() * this->cells->count());
}

void List::removeAllCells()
{
    foreach(Cell* cell, *this->cells)
    {
        this->removeCell(cell);
    }
}

void List::deselectCell(Cell *pCell)
{
    bool shiftKey = false;
    bool ctrlKey = false;
    int modifiers = Application::getModifiers();
    if (modifiers & Qt::ShiftModifier)
    {
        shiftKey = true;
    }
    if (modifiers & Qt::ControlModifier)
    {
        ctrlKey = true;
    }
    if (!this->selectedCells->contains(pCell))
    {
        return;
    }
    if (ctrlKey)
    {
        pCell->setSelectedState(false);
        this->selectedCells->removeAt(this->selectedCells->indexOf(pCell));
    }
    else if(shiftKey)
    {
        return;
    }
    else
    {
        this->clearListSelection();
        this->selectCell(pCell);
    }
    emit selectionChanged();
}

int List::count()
{
    return this->cells->count();
}

int List::lenght()
{
    return this->count();
}

QList<Cell*>* List::getSelectedCells()
{
    return this->selectedCells;
}

QList<Cell*>* List::getCells()
{
    return this->cells;
}
