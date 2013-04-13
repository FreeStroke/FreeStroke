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
/*!
 * \file cell.h
 * \brief The Cell class represent a cell of a List. It has a fixed width of 170 and is composed of 2 Label and a GlView.
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */
#ifndef CELL_H
#define CELL_H

#include "../element/label/label.h"
#include "../glview/glview.h"
#include "../../daolayer/historyrecord.h"

/*!
 * \brief The Cell class represent a cell of a List. It has a fixed width of 170 and is composed of 2 Label and a GlView.
 */
class Cell : public QAbstractButton
{
    Q_OBJECT
public:

    /*!
     * \brief The default Cell constructor.
     * \param pList the List in wich the Cell will be added
     * \param pHeight the desired height of the Cell
     */
    Cell(void* pList = 0, int pHeight = 47);
    /*!
     * \brief The default Cell constructor. Create a Cell with a GlView using the Record which contains the Gesture to display
     * \param pList the List in wich the Cell will be added
     * \param pHeight the desired height of the Cell
     * \param pRecord the Record to display in the GlView
     */
    Cell(Record* pRecord, void* pList = 0, int pHeight = 47);
    /*!
     * \brief Cell constructor. Create a Cell with a GlView using the HistoryRecord which contains the Gesture to display as well as the lastExecutedDate to display as detailedText
     * \param pList the List in wich the Cell will be added
     * \param pHeight the desired height of the Cell
     * \param pHistoryRecord the Record to display in the GlView
     */
    Cell(HistoryRecord* pHistoryRecord, void* pList = 0, int pHeight = 47);

    /*!
     * \brief Cell destructor. Remove all none Qt objects
     */
    ~Cell();

    /*!
     * \brief Initialisation
     * \param pList
     * \param pHeight
     */
    void init(void* pList, int pHeight);

    /*!
     * \brief setAlternate defines whether or not this Cell is an alternate cell, in that case the background color of the Cell will change.
     * \param invert the boolean defining whether or not this Cell is an alternate cell.
     */
    void setAlternate(bool pAlternate);
    /*!
     * \brief setSelectedState defines whether or not this Cell is in an selected state.
     * \param pSelected the boolean defining whether or not this Cell is in an selected state.
     */
    void setSelectedState(bool pSelected);
    /*!
     * \brief setSelected defines whether or not this Cell is selected.
     * \param pSelected the boolean defining whether or not this Cell is selected.
     */
    void setSelected(bool pSelected);
    /*!
     * \brief setText set the text of the text label.
     * \param pText the desired text.
     */
    void setText(QString text);
    /*!
     * \brief setDetailedText set the text of the detailedtext label. If this detailed text is set, the Cell will not be selectable.
     * \param pDetailedText the desired text.
     */
    void setDetailedText(QString pDetailedText);

    /*!
     * \brief Returns the detailed text of the Cell
     * \return the detailed text of the Cell
     */
    Label* getDetailedText();

    /*!
     * \brief return the GlView of the Cell
     * \return the GlView of the Cell
     */
    GlView* getGlView();
    /*!
     * \brief returns a boolean representing the alternate state of the Cell
     * \return a boolean representing the alternate state of the Cell
     */
    bool getAlternate();
    /*!
     * \brief return the Gesture displayed in the GlView
     * \return the Gesture displayed in the GlView
     */
    Gesture* getGesture();

    /*!
     * \brief Gets the record associated with the current cell
     * \return the record associated
     */
    Record* getRecord();

    /*!
     * \brief Sets the record to associate with the current cell
     * \param pRecord the record to associate
     */
    void setRecord(Record* pRecord);

    /*!
     * \brief Gets the history record associated to the cell
     * \return the history record associated
     */
    HistoryRecord* getHistoryRecord();

protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent * e);
    Cell(void* pList, bool noGl);
    /*!
     * \brief alternateColor representing the alternate state of the Cell.
     */
    bool alternateColor;
private:
    /*!
     * \brief list void* representing the List in which the Cell will be added.
     */
    void *list;
    /*!
     * \brief selected boolean representing the selected state of the Cell.
     */
    bool selected;
    /*!
     * \brief text the text of the text Label.
     */
    Label *text;
    /*!
     * \brief detailedText the text of the detailed text Label.
     */
    Label *detailedText;
    /*!
     * \brief glView the GlView of the Cell.
     */
    GlView *glView;

    /*!
     * \brief gesture the Gesture which is displayed in the GlView
     */
    Gesture *gesture;

    HistoryRecord* historyRecord; /*!< history record associated to the cell */
    Record* record; /*!< record associated to the cell */
};

#endif
