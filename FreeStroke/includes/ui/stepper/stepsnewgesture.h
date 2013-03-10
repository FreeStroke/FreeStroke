/*!
 * \file stepsnewgesture.h
 * \brief The StepsNewGesture class contains all the Step to add a new Gesture with the StepperNewGesture
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef STEPSNEWGESTURE_H
#define STEPSNEWGESTURE_H

#include <QtGui/QWidget>
#include <QtCore/QList>

#include "../../includes/daolayer/record.h"
#include "../../includes/common/gesture.h"
#include "../../includes/gestures/executionmanager.h"
#include "steppernewgesture.h"
#include "../../includes/ui/glview/glview.h"
#include "../../includes/ui/commandchooser/commandchooser.h"

#include "stepper.h"

/*!
 * \brief The StepsNewGesture class contains all the Step to add a new Gesture with the StepperNewGesture
 */
class StepsNewGesture : QObject
{
    Q_OBJECT
public:
    /*!
     * \brief StepsNewGesture default constructor
     * \param pExecutionManager the ExecutionManager which will be used to recognize Gesture
     * \param pNumberOfGesture the desired number of Gesture to do to train the model
     * \param parent the QWidget parent
     */
    explicit StepsNewGesture(ExecutionManager *pExecutionManager, int pNumberOfGesture, QWidget *parent = 0);
    /*!
     * \brief show display the StepperNewGesture
     * \return a QDialogCode result
     */
    int show();

private:
    /*!
     * \brief stepper the StepperNewGesture which will be displayed
     */
    StepperNewGesture* stepper;
    /*!
     * \brief executionManager the ExecutionManager which will be used to recognize Gesture
     */
    ExecutionManager* executionManager;
    /*!
     * \brief glViewStep4 the GLView of the forth Step
     */
    GlView* glViewStep4;
    /*!
     * \brief commandChooser the CommandChooser which will be used to choose the Command
     */
    CommandChooser* commandChooser;

private slots:
    /*!
     * \brief gestureReceived slot called when a Gesture is received by the ExecutionManager. It set the Gesture to the
     * GLView of the forth Step to display it.
     * \param pGesture the Gesture received.
     */
    void gestureReceived(Gesture *pGesture);

};

#endif // STEPSNEWGESTURE_H
