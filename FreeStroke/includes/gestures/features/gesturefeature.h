/*!
 * \file gesturefeature.h
 * \brief Abstract class for gesture-oriented features
 * \author Camille.D
 * \date 2013-02-12
 */
#ifndef GESTUREFEATURE_H
#define GESTUREFEATURE_H

#include "../../includes/gestures/data/inputgesture.h"

#include <QtCore/QDebug>

/*!
 * \class GestureFeature
 * \brief Abstract class for gesture-oriented features
 * Contains functions for querying and printing feature results
 */
class GestureFeature
{
public:
    /*!
     * \brief Executes the feature algo on an input gesture
     * \param pIg the input gesture used to compute the result
     * \return a float representing the result of the query
     */
    virtual float queryGesture(InputGesture *pIg) = 0;

    /*!
     * \brief Get a formal QString representing the object
     * \return QString representing the object
     */
    virtual QString toString(){return QString();}
};

#endif // GESTUREFEATURE_H
