/*!
 * \file steppercontroller.h
 * \brief The Stepper class is a Stepper used for discovering and choosing Controller.
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef STEPPERCONTROLLER_H
#define STEPPERCONTROLLER_H

#include <QtCore/QList>

#include "stepper.h"

#include "../../includes/common/controller.h"
#include "../../includes/ui/cell/cellcontroller.h"

/*!
 * \brief The Stepper class is a Stepper used for discovering and choosing Controller.
*/
class StepperController : public Stepper
{
    Q_OBJECT
public:
    /*!
     * \brief StepperController default constructor
     * \param parent the parent Widget
     */
    explicit StepperController(QWidget *parent = 0);
    /*!
     * \brief getControllers returns a QList of Controller discovered.
     * \return a QList of Controller discovered.
     */
    QList<Controller*>* getControllers();
private:
    /*!
     * \brief controllers QList of Controller discovered.
     */
    QList<Controller*>* controllers;
    /*!
     * \brief cells QList of the Cell containing Controller
     */
    QList<Cell*>* cells;
    /*!
     * \brief communication the Communication
     */
    void *communication ;

signals:
    /*!
     * \brief requestDiscover signal emitted when the StepperController need to discover Controller
     */
    void requestDiscover(QList<Controller*>*);
    /*!
     * \brief controllerChosen signal emitted when the Controller has been chosen.
     */
    void controllerChosen(Controller*);

private slots:
    /*!
     * \brief discoverResponse slot is called when all the Controller have been discovered. It displays found Controller
     * and allow to select one.
     */
    void discoverResponse();
    /*!
     * \brief chooseController slot is called when a Controller has been chosen. It emit a controllerChose signal and go
     * to the next Step.
     */
    void chooseController();
    /*!
     * \brief previousStep slot is called when the  previous DialogButton is clicked on the Step displaying available Controller.
     * it relaunch a discover.
     */
    void previousStep();

};

#endif // STEPPERCONTROLLER_H
