/*!
 * \file list.h
 * \brief The List class represent a list of Cell
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef LIST_H
#define LIST_H

#include <QtGui/QWidget>
#include <QtGui/QScrollArea>

#include "../cell/cell.h"

/*!
 * \brief The List class represent a list of Cell
 */
class List : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief default List constructor
     * \param parent the container QWidget parent
     */
    List(QWidget *parent = 0);
    /*!
     * \brief add a Cell to the List
     * \param pCell the Cell to add
     */
    void addCell(Cell *pCell);
    /*!
     * \brief Insert a Cell at the head of the list
     * \param pCell the Cell to insert
     */
    void insertCellAtHead(Cell* pCell);    
    /*!
     * \brief select cells depending on the modifiers (ctrl, shift) hold down.
     * \param pCell the Cell to select
     */
    void selectCell(Cell *pCell);
    /*!
     * \brief deselect a Cell
     * \param pCell the Cell to deselect
     */
    void deselectCell(Cell *pCell);
    /*!
     * \brief remove a Cell from the List
     * \param pCell the Cell to remove
     */
    void removeCell(Cell *pCell);
    /*!
     * \brief remove all the Cells from the List
     */
    void removeAllCells();

    /*!
     * \brief Returns the number of Cell in the List
     * \return the number of Cell in the List
     */
    int count();
    /*!
     * \brief identical to count()
     */
    int lenght();

    /*!
     * \brief returns a QList of the selected Cells
     * \return a QList of the selected Cells
     */
    QList<Cell*>* getSelectedCells();

    /*!
     * \brief returns a QList of the Cells
     * \return a QList of the Cells
     */
    QList<Cell*>* getCells();

    /*!
     * \brief unselect all the Cell
     */
    void clearListSelection(bool signal = true);

    /*!
     * \brief containsRecord returns true if the List contains a Record
     * \param pRecord the Record to test
     * \return true if the List contains a Record
     */
    bool containsRecord(Record* pRecord);

    /*!
     * \brief resetFocus reset the focus of the List
     */
    void resetFocus();

public slots:
    /*!
     * \brief private_setFocus set the focus on the scrollWidget of the List
     */
    void private_setFocus();

protected:
    /*!
     * \brief select a Cell if not already selected
     * \param pCell the Cell to select
     */
    void selectOneCell(Cell* pCell);

    /*!
     * \brief the scroll area
     */
    QScrollArea     *scroll;
    /*!
     * \brief the Widget used as a scroll bar
     */
    QWidget         *scrollWidget;
    /*!
     * \brief the QList of the Cell of the List
     */
    QList<Cell*>    *cells;
    /*!
     * \brief the QList of the Cell which are selected of the List
     */
    QList<Cell*>    *selectedCells;

    /*!
     * \brief the index of the last Cell selected without the shift modifier
     */
    int             lastIndex;
    /*!
     * \brief the index of the last Cell selected with the shift modifier with its index superior to lastIndex
     */
    int             lastSuperiorShiftIndex;
    /*!
     * \brief the index of the last Cell selected with the shift modifier with its index inferior to lastIndex
     */
    int             lastInferiorShiftIndex;
    /*!
     * \brief select all the Cell
     */
    void selectAll();
signals:
    /*!
     * \brief selectionChanged signal emmited when the selection of the List has changed
     */
    void selectionChanged();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
};

#endif // LABEL_H
