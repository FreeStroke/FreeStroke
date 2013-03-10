/*!
 * \file combobox.h
 * \brief The ComboBox class is a QComboBox with a custom skin
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QtGui/QComboBox>

#include "../element.h"

/*!
 * \brief The ComboBox class is a QComboBox with a custom skin
 */
class ComboBox : public QComboBox, public Element
{
	Q_OBJECT
public:
    /*!
     * \brief the default ComboBox constructor
     * \param w the container QWidget parent
     */
	ComboBox(QWidget * w = 0);
protected:
	void paintEvent(QPaintEvent * e);

private:
    QPixmap *pixmap;

};

#endif
