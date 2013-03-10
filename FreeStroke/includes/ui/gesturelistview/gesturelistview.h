/*!
 * \file gesturelistview.h
 * \brief The GestureListView class represents a view of a List of Gesture
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef GESTURELISTVIEW_H
#define GESTURELISTVIEW_H

#include "../list/list.h"
#include "../../daolayer/daolayer.h"

/*!
 * \brief The GestureListView class represents a view of a List of Gesture
 */
class GestureListView : public List
{
public:
    /*!
     * \brief GestureListView the default contructor
     * \param parent the parent of the GestureListView
     */
    GestureListView(QWidget *parent);
};

#endif // GESTURELISTVIEW_H
