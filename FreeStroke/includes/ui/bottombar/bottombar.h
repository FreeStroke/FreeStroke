/*!
 * \file bottombar.h
 * \author Sylvain Fay-Châtelard
 * \date 2013/03/07
 * \brief The BottomBar class represent a container for Element and BottomBarSeparator of 52 pixels heights.
 *  It has no external margin and contents margin of 10,0,10,0 (left, top, right, bottom).
 *
 */
#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QtGui/QWidget>

#include "../element/element.h"
#include "../bottombar/bottombarseparator.h"

/*!
 * \brief The BottomBar class represent a container for Element and BottomBarSeparator of 52 pixels heights.
 *  It has no external margin and contents margin of 10,0,10,0 (left, top, right, bottom).
 */
class BottomBar : public QWidget
{

    Q_OBJECT
public:
    /*!
     * \brief The BottomBar default constructor
     * \param parent the parent container QWidget
     */
    BottomBar(QWidget *parent = 0);
    /**
     * @brief add an Element to the BottomBar
     */
    void addElement(Element *);
    /**
     * @brief add a BottomBarSeparator to the BottomBar
     */
    void addSeparator();

    /*!
     * \brief defines whether or not the BottomBar will have a line painted to its right border
     * \param pPrint the boolean defining whether or not the BottomBar will have a line painted to its right border
     */
    void addLeftLine(bool pPrint);
    /*!
     * \brief defines whether or not the BottomBar will have a line painted to its right border
     * \param pPrint the boolean defining whether or not the BottomBar will have a line painted to its right border
     */
    void addRightLine(bool pPrint);

    /*!
     * \brief defines whether or not the BottomBar's bottom border will be painted to its top border instead
     * \param pSetTopBar the boolean defining whether or not the BottomBar's bottom border will be painted to its top border instead
     */
    void setTopBar(bool pSetTopBar);

protected:
    void paintEvent(QPaintEvent *);

private:
    bool printLeft; /*!< the boolean defining whether or not the BottomBar will have a line painted to its right border*/
    bool printRight; /*!< the boolean defining whether or not the BottomBar will have a line painted to its left border*/
    bool isTopBar; /*!< the boolean defining whether or not the BottomBar's bottom border will be painted to its top border instead*/
};

#endif // BOTTOMBAR_H
