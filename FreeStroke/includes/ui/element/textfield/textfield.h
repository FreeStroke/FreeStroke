/*!
 * \file textfield.h
 * \brief The TextField class is a QLineEdit with a custom skin
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef TEXTFIELDELEMENT_H
#define TEXTFIELDELEMENT_H

#include <QtGui/QLineEdit>

#include "../element.h"

/*!
 * \brief The TextField class is a QLineEdit with a custom skin
 */
class TextField : public QLineEdit, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief default TextField constructor
     * \param parent the container QWidget parent
     */
    TextField(QWidget *parent = 0);
    /*!
     * \brief set the position of the TextField
     * \param pX the desired x
     * \param pY the desired y
     */
    void setPosition(int pX, int pY);
    /*!
     * \brief set the text of the TextField
     * \param pText the desired text
     */
    void setText(QString pText);

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void paintEvent(QPaintEvent *e);
    void focusOutEvent(QFocusEvent *);

signals:
    /*!
     * \brief lostFocus is the signal sent when the focus has been lost
     */
    void lostFocus();
};

#endif // TEXTFIELDELEMENT_H
