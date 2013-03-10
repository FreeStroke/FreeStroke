/*!
 * \file scrollbar.h
 * \brief The ScrollBar class is a QScrollBar with a custom skin
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QScrollBar>

/*!
 * \brief The ScrollBar class is a QScrollBar with a custom skin
 */
class ScrollBar : public QScrollBar
{
	Q_OBJECT
public:
    /*!
     * \brief default ScrollBar constructor
     * \param w container QWidget parent
     */
	ScrollBar(QWidget * w = 0);
    /*!
     * \brief ScrollBar constructor which specified the scroll orientation
     * \param pOrientation the desired Orientation
     * \param w container QWidget parent
     */
    ScrollBar(Qt::Orientation pOrientation, QWidget * w = 0);
    void wheelEvent(QWheelEvent * e);
protected:
    void paintEvent(QPaintEvent * e);
};

#endif
