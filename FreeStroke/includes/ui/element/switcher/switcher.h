/*!
 * \file switcher.h
 * \brief The Switcher class which represents custom checkbox with a Cursor to move to set the value
 * \author Aurèle Lenfant (thanks to Romain Etchegoyhen)
 * \date 2013-02-20
*/
#ifndef SWITCHER_H
#define SWITCHER_H

#include <QAbstractButton>

#include "../element.h"
#include "../../../ui/element/label/label.h"


/*!
 * \brief The Cursor class of the Switcher wich represent the movable cursor to set the value
 */
class Cursor : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief the default Cursor constructor
     * \param parent the container QWidget parent
     */
    Cursor(QWidget * parent = 0);
protected:
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void paintEvent(QPaintEvent * e);
private:
    QPoint mMousePos;
    QPoint mOriginPos;
};

/*!
 * \brief The Switcher class is a custom checkbox
 */
class Switcher : public QAbstractButton, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief Switcher the default constructor
     * \param parent the container QWidget parent
     * \param pState the state of the Switcher (selected or not)
     */
    Switcher(QWidget * parent = 0, bool pState = false);
    /*!
     * \brief set the state of the Switcher
     * \param pState the desired state
     * \param pMoveCursor boolean which defines whether or not the Cursor will move accordingly to the state value
     */
    void setState(bool pState, bool pMoveCursor = true);
    /*!
     * \brief emit a toogle event
     */
    void eventToggle(bool pState);
    /*!
     * \brief returns the state of the Switcher
     * \return the state of the Switcher
     */
    bool state();
public slots:
    /*!
     * \brief Slot that change the state of the Switcher
     */
    void toggleState();
signals:
    /*!
     * \brief the toggle signal
     */
    void toggle();
    /*!
     * \brief the toggle signal with the boolean representing the value of the switcher
     */
    void toggle(bool);
protected:
    void paintEvent(QPaintEvent * e);
private:
    /*!
     * \brief the state of the Switcher
     */
    bool mState;
    /*!
     * \brief the Cursor of the Switcher
     */
    Cursor *cursor;
    /*!
     * \brief the label which is visible while the Switcher is On
     */
    Label *labelTrue;
    /*!
     * \brief the label which is visible while the Switcher is Off
     */
    Label *labelFalse;
};

#endif // SWITCHER_H
