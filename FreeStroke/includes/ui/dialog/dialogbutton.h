/*!
 * \file dialogbutton.h
 * \brief The DialogButton class represents a special QPushButton used by Dialog
 * \author Aurèle Lenfant (thanks to Romain Etchegoyhen)
 * \date 2013-02-20
 */
#ifndef CUSTOMFORMS_H
#define CUSTOMFORMS_H

#include <QtCore/QObject>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QSpinBox>
#include <QtGui/QPushButton>
#include <QtGui/QPainter>
#include <QtGui/QScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QMessageBox>
#include <QtGui/QDialog>
#include <QtGui/QWheelEvent>

/*!
 * \brief The DialogButton class represents a special QPushButton used by Dialog
 */
class DialogButton : public QPushButton
{
	Q_OBJECT
public:
    /*!
     * \brief The Type enum defines the different type of a DialogButton which changes its color
     */
	enum Type {
		Normal,
		Dark,
        Bright
	};
public:
    /*!
     * \brief the default DialogButton constructor
     * \param text the text to show on the DialogButton
     * \param type the Type of the DialogButton which defins its color
     * \param parent the container QWidget parent
     */
    DialogButton(const QString & text, DialogButton::Type pType = DialogButton::Normal, QWidget * parent = 0);
	~DialogButton();
    /*!
     * \brief type returns the Type of the DialogButton
     * \return the Type of the DialogButton
     */
    DialogButton::Type type();
    /*!
     * \brief fix the size of the DialogButton and its label size
     */
	void fix();
private:
    /*!
     * \brief type the Type of the DialogButton
     */
    DialogButton::Type buttonType;
	bool mPressed;
protected:
	void paintEvent(QPaintEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	void enterEvent(QEvent * event);
	void leaveEvent(QEvent * event);
};

#endif
