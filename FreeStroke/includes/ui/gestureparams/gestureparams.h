/*!
 * \file gestureparams.h
 * \brief The GestureParams class represent the bar at the top of the GlView which should contain the different
 * Element to control the selected Gesture.
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef GESTUREPARAMS_H
#define GESTUREPARAMS_H

#include <QtGui/QWidget>

#include "../element/element.h"

/*!
 * \brief The GestureParams class represent the bar at the top of the GlView which should contain the different
 * Element to control the selected Gesture.
 */
class GestureParams : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief default GestureParams constructor
     * \param parent the container QWidget parent
     */
    GestureParams(QWidget *parent = 0);
    /*!
     * \brief add an Element to the GestureParams
     * \param pElement the Element to add
     */
    void addElement(Element * pElement);
    /*!
     * \brief add a QSpacerItem to the GestureParams
     */
    void addSpacer();

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // TOPBAR_H
