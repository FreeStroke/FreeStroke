/*!
 * \file stepper.h
 * \brief The Stepper class is a Dialog which permit to easily create series of modal with QWidget and 3 DialogButton
 * to either go to the next Step, go back to the previous one or close the Dialog. The last Step will automatically
 * have a finish DialogButton instead of the next one.
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef STEPPER_H
#define STEPPER_H

#include <QtGui/QWidget>

#include "../dialog/dialog.h"

/*!
 * \brief The Step class is used to define each step of a Stepper. It is composed of a main
 * QWidget and 3 DialogButton (previous, cancel, next) which can be disabled.
 */
class Step
{
public:
    /*!
     * \brief default Step constructor
     * \param pTitle the title of the Step
     * \param pNextVisible defines whether or not the "next" DialogButton is visible
     * \param pPreviousVisible defines whether or not the "previous" DialogButton is visible
     * \param pCancelVisible defines whether or not the "cancel" DialogButton is visible
     * \param pWidget the QWidget contained in the Step
     */
    explicit Step(QString pTitle, bool pNextVisible, bool pPreviousVisible, bool pCancelVisible, QWidget* pWidget);

    /*!
     * \brief defines whether or not the "next" DialogButton is visible
     * \param pShowNext  defines whether or not the "next" DialogButton is visible
     */
    void nextVisible(bool pShowNext);
    /*!
     * \brief defines whether or not the "close" DialogButton is visible
     * \param pShowCancel defines whether or not the "next" DialogButton is visible
     */
    void closeVisible(bool pShowCancel);
    /*!
     * \brief defines whether or not the "previous" DialogButton is visible
     * \param pShowPrevious defines whether or not the "previous" DialogButton is visible
     */
    void previousVisible(bool pShowPrevious);

public:
    /*!
     * \brief defines whether or not the "nect" DialogButton is visible
     */
    bool showNext;
    /*!
     * \brief defines whether or not the "cancel" DialogButton is visible
     */
    bool showCancel;
    /*!
     * \brief defines whether or not the "previous" DialogButton is visible
     */
    bool showPrevious;
    /*!
     * \brief the title of the Step
     */
    QString title;
    /*!
     * \brief the main QWidget of the Step
     */
    QWidget* widget;
};

/*!
 * \brief The Stepper class is a Dialog which permit to easily create series of modal with QWidget and 3 DialogButton
 * to either go to the next Step, go back to the previous one or close the Dialog. The last Step will automatically
 * have a finish DialogButton instead of the next one.
 */
class Stepper : public Dialog
{
    Q_OBJECT
public:

    /*!
     * \brief The Role enum defines three possibles roles of DialogButton
     */
    enum Role
    {
        Next,
        Previous,
        Cancel
    };

    /*!
     * \brief default Stepper constructor
     * \param parent container QWidget parent
     */
    explicit Stepper(QWidget *parent = 0);
    /*!
     * \brief Returns the current Step
     * \return the current Step
     */
    Step *getCurrentStep();

    /*!
     * \brief Returns the steps of the Stepper
     * \return the steps
     */
    QList<Step*> *getSteps();

    /*!
     * \brief Add a Step to the Stepper
     * \param pTitle the title of the Stepper
     * \param pNextVisible defines whether or not the next DialogButton is visible
     * \param pPreviousVisible defines whether or not the previous DialogButton is visible
     * \param pCancelVisible defines whether or not the cancel DialogButton is visible
     * \param pWidget the QWidget to add to the Step
     */
    void addStep(QString pTitle, bool pNextVisible, bool pPreviousVisible, bool pCancelVisible, QWidget* pWidget);

    void setButtonPreviousName(QString);
    void setButtonNextName(QString);
    void setButtonCancelName(QString);

protected:
    /*!
     * \brief QList containing the Step of the Stepper
     */
    QList<Step*> *steps;
    /*!
     * \brief the index of the current Step
     */
    int currentStep;
    /*!
     * \brief The previous DialogButton
     */
    DialogButton* buttonPrevious;
    /*!
     * \brief The next DialogButton
     */
    DialogButton* buttonNext;
    /*!
     * \brief The cancel DialogButton
     */
    DialogButton* buttonCancel;
    /*!
     * \brief organize the DialogButton on the Stepper
     */
    void organize();

    void keyPressEvent(QKeyEvent *);
private:
    /*!
     * \brief Add a DialogButton to the Stepper
     * \param pLabelText the text of the DialogButton
     * \param pRole the Role of the DialogButton
     * \param pType the Type if the DialogButton
     * \param pDefault defines whether or not this is the default DialogButton of the Stepper
     */
    void addButton(QString pLabelText, Stepper::Role pRole, DialogButton::Type pType, bool pDefault);
public slots:
    /*!
     * \brief next slot is called when the next DialogButton is clicked. It go to the next step.
     */
    void next();
    /*!
     * \brief previous slot is called when the previous DialogButton is clicked. It go to the previous step.
     */
    void previous();
    /*!
     * \brief cancel slot is called when the previous DialogButton is clicked. It close the Stepper and send a reject.
     */
    void cancel();
};

#endif // STEPPER_H
