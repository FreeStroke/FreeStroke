/*!
 * \file logisticregressionalgorithm.h
 * \author Guillaume Demurger
 * \brief Algorithm of the neuron network using the logistic regression probabilist law for recognition of gestures.
 * \date 2013-02-12
 */

#ifndef LOGISTICREGRESSIONALGORITHM_H
#define LOGISTICREGRESSIONALGORITHM_H

#include <QtCore/QThread>
#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QList>

#include "../data/inputgesture.h"
#include "../../daolayer/record.h"

/*!
 * \class
 * \brief The LogisticRegressionAlgorithm class encapsulates the neuron network
 * using the logistic regression probabilist law for recognition of gestures.
 * The LRA needs to be trained before be used. Each time a geseture is added
 * or removed from the model, LRA need to be trained to update his internal features.
 */
class LogisticRegressionAlgorithm : public QThread
{
    Q_OBJECT
private:
    /*!
     * \brief Tuple of Gesture record and InputGesture.
     */
    struct LabeledGesture {
        Record* gestureRecord;
        InputGesture *gesture;
    };

public:
    LogisticRegressionAlgorithm(QObject *parent);

    /*!
     * \brief return the names of all registered gestures.
     * \return the list of the names of all gestures.
     */
    QList<Record*>* getGestures();

    /*!
     * \brief Return the three registered gestures closest of the parsed gesture.
     * \param pIGesture an InputGesture built from the Kinect flow by the Segmenter.
     * \return A list containing the three Gestures the most compatible with the pIGesture.
     */
    QList<QPair<Record*, double> *> *recognizeSingleGesture(InputGesture *pIg);

    /*!
     * \brief learnGestureClass
     * \param pFeatureResults
     * \param pInputs
     * \param pClassName
     * \param pMaxIter
     * \return
     */
    int learnGestureClass(QList<QList<float> > pFeatureResults, QList<LabeledGesture> *pInputs, Record* pClassName, int pMaxIter);

    /*!
     * \brief Train the LRA with all the registered gestures for recognition.
     * This method should be called each time a gesture is added or removed
     * to the model.
     * \param pGestures, the list of gestures ordered by their name.
     */
    void train(QHash<Record*, QList<InputGesture *> *> *pGestures);

protected:

    /*!
     * \brief Train the LRA with all the registered gestures for recognition.
     * This method is called by train()
     * \param pGestures, the list of gestures ordered by their name.
     */
    void run();

private:
    QHash<Record*, QList<InputGesture*>*> *gestures; /*!< Map of records and InputGesture associated */
    QHash<Record*, QList<double>*>      weights;  /*!< Map of records and weights associated (updated after training) */
    double                             stepSize; /*!< Size of steps for algorithm training */
    double                             convergenceThreshold; /*!< Threshold of convergence between input gestures*/
    double                             alpha; /*! Factor of weight multiplication */

    /*!
     * \brief converged
     * \param pOldWeights
     * \param pWeights
     * \param pThreshold
     * \return if a train iteration has converged or not.
     */
    bool converged(QList<double> *pOldWeights, QList<double> *pWeights, double pThreshold);

    /*!
     * \brief Work out the result of the pWeights on the pFeatureResult
     * to the logistic regression law.
     * \param pWeights the weights of all
     * \param pFeatureResults
     * \return the probability of the pWeights according to logistic
     * regression law.
     */
    double sigmoid(QList<double> *pWeights, QList<float> pFeatureResults);
};

#endif // LOGISTICREGRESSIONALGORITHM_H
