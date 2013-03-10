/*!
 * \file bottombar.h
 * \author Sylvain Fay-Châtelard
 * \date 2013/03/07
 * \brief The BottomBarSeparator class represent a separator (a line of pixel with margin) of Element to be used in the BottomBar.
 */
#ifndef BOTTOMBARSEPARATOR_H
#define BOTTOMBARSEPARATOR_H


#include <QtGui/QWidget>

#include "../element/button/buttonelement.h"

/*!
 * \brief The BottomBarSeparator class represent a separator (a line of pixel with margin) of Element to be used in the BottomBar.
 */
class BottomBarSeparator : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief The default BottomBarSeparator constructor
     * \param parent the parent container QWidget
     */
    BottomBarSeparator(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // BOTTOMBARSEPARATOR_H
