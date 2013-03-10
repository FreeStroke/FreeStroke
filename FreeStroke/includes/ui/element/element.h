/*!
 * \file element.h
 * \brief The Element class is the super class of custom basic UI elements (buttons, labels, textfield ...)
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtGui/QWidget>

/*!
 * \brief The Element class is the super class of custom basic UI elements (buttons, labels, textfield ...)
 */
class Element
{
public:
    Element(QWidget * pWidget);
    QWidget *getWidget();
private:
    QWidget * widget;
};

#endif // ELEMENT_H
