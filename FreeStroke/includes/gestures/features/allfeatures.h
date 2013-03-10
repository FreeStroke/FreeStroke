/*!
 * \file allfeatures.h
 * \brief Access point to all gesture features and neutral stance feature
 * \author Camille.D
 * \date 2013-02-12
 */
#ifndef ALLFEATURES_H
#define ALLFEATURES_H

#include <QtCore/QList>

#include "../data/inputgesture.h"
#include "gesturefeature.h"
#include "neutralfeature.h"

/*! \class AllFeatures
   * \brief Access point to all gesture features and neutral stance feature
   * Contains functions to access features, load and save neutral stance model and to compute gesture feature results
   */
class AllFeatures
{
public:
    /*!
     * \brief Access all static gesture features
     * \return a pointer to the list of all gesture features used
     */
    static QList<GestureFeature*> allFeatures();


    /*!
     * \brief Computes all gesture feature query results on an input gesture
     * \param pGest inpute gesture to execute queries functions
     * \return  a list containing all the feature results for the gesture
     */
    static QList<float> gestureFeatureResults(InputGesture *pGest);

    /*!
     * \brief Access to the neutral stance feature
     * \return a pointer on the neutral feature
     */
    static NeutralFeature* getNeutralFeature();

    /*!
     * \brief Loads neutral feature from database (Dao)
     * \return the list of weights returned after neutral stance model training
     */
    static QList<float> * loadNeutralFeature();

    /*!
     * \brief Saves neutral stances in database (Dao)
     * \param neutrals neutral stances gestures to save in database
     */
    static void saveNeutralFeature(QList<Gesture *> *neurals);


};


#endif // ALLFEATURES_H
