/*!
 * \file stepstutorial.h
 * \brief The StepsNewGesture class contains all the Step to display in the tutorial Stepper
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef STEPSTUTORIAL_H
#define STEPSTUTORIAL_H

#include <QtCore/QObject>
#include <QtGui/QWidget>

#include "../../includes/ui/stepper/stepper.h"

/*!
 * \brief The StepsNewGesture class contains all the Step to display in the tutorial Stepper
 */
class StepsTutorial : QObject
{
    Q_OBJECT
public:
    /*!
     * \brief StepsTutorial default constructor
     * \param pParent the QWidget parent
     * \param isFirstLaunch boolean determining if this is the first launch of the application. If so, ask to add a Controller.
     */
    explicit StepsTutorial(QWidget *pParent = 0, bool isFirstLaunch = true);
    /*!
     * \brief Launch the execution of the stepper associated to the StepsTutorial instance.
     * \return The exit code of the process.
     */
    int show();

private:
    /*!
     * \brief stepper the Stepper which will be displayed
     */
    Stepper* stepper;
    //ExecutionManager* executionManager;
    //GlView* glViewStep4;

private slots:
    /*!
     * \brief Discover the KController ready to connect with a Freestroke Client.
     */
    void discoverController();
};

#endif // STEPSTUTORIAL_H
