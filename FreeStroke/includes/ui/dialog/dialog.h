/*!
 * \file dialog.h
 * \brief The Dialog class represents a modal dialog which has a top bar (with a close button and a title),
 * a main content, and a bottom bar (with a close button) in which DialogButton can be added.
 * \author Aurèle Lenfant (thanks to Romain Etchegoyhen)
 * \date 2013-02-20
 */
#ifndef DIALOG_H
#define DIALOG_H

#include <QtCore/QObject>
#include <QtGui/QDialog>
#include <QtGui/QPainter>
#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtCore/QHash>
#include <QtGui/QLabel>
#include <QtCore/QList>
#include <QtGui/QGraphicsDropShadowEffect>

#include "dialogbutton.h"

#include "../../includes/ui/element/label/label.h"

/*!
 * \brief The Dialog class represents a modal dialog which has a top bar (with a close button and a title),
 * a main content, and a bottom bar (with a close button) in which DialogButton can be added.
 *
 */
class Dialog : public QDialog
{
	Q_OBJECT
public:
    /*!
     * \brief The Type enum represents the type of the DialogButton which defines its icon.
     */
	enum Type
	{
		Information,
		Error,
		Warning,
        Success
	};
    /*!
     * \brief The Role enum represents the role of the DialogButton.
     */
	enum Role
	{
        Accept,
        Reject
	};
public:
    /*!
     * \brief the default Dialog constructor.
     * \param pTitle the title of the Dialog
     * \param parent the container QWidget parent
     */
    Dialog(QString pTitle, QWidget * parent = 0);
	~Dialog();
    /*!
     * \brief addButton adds a DialogButton to the bottom bar of the Dialog
     * \param pButton the DialogButton to add
     */
    void addButton(DialogButton * pButton);
    /*!
     * \brief addButton adds a DialogButton to the bottom bar of the Dialog
     * \param pText the text on the DialogButton
     * \param pRole the Role of the DialogButton
     * \param pType the Type of the DialogButton which defines its color
     * \param pDefault defines whether or not the DialogButton is the default button
     */
    void addButton(QString pText, Dialog::Role pRole, DialogButton::Type pType, bool pDefault = false);
    /*!
     * \brief removeButton removes the DialogButton from the Dialog
     * \param pButton the DialogButton to remove
     */
    void removeButton(DialogButton * pButton);
    /*!
     * \brief buttonHandler position the DialogButton of the Dialog
     */
	void buttonHandler();
    /*!
     * \brief resize the Dialog accordingly to the parameters
     * \param w the desired width
     * \param h the desired height
     */
	void resize(int w, int h);
    /*!
     * \brief resize the Dialog accordingly to the parameter
     * \param pSize the desired size
     */
    void resize(const QSize & pSize);
    /*!
     * \brief closeButton returns the QPushButton with the Reject event
     * \return the QPushButton with the Reject event
     */
	QPushButton * closeButton();
    /*!
     * \brief displayNotification a static method that display a notification (Type = information)
     * \param pType the Type of the notification to display
     * \param pTitle the title of the notification to display
     * \param pContent the content of the notification to display
     * \return the DialogCode of the notification once validated or closed
     */
    Dialog::DialogCode displayNotification(Dialog::Type pType, QString pTitle, QString pContent);
    /*!
     * \brief setTitle set the Title of the Dialog
     * \param title the desired title
     */
    void setTitle(QString pTitle);
protected:
	void paintEvent(QPaintEvent * event);
	void resizeEvent(QResizeEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);

    /*!
     * \brief buttonClose the QPushButton with the Reject event
     */
    QPushButton * buttonClose;
    /*!
     * \brief mButtons the DialogButtons contained in the Dialog
     */
    QList<DialogButton *> * mButtons;

private:
    /*!
     * \brief title the title of the Dialog
     */
    QString title;
    /*!
     * \brief type the type of the Dialog which defines its icon
     */
    int pType;
    /*!
     * \brief labelIcon the label of the icon
     */
    QLabel * labelIcon;
    /*!
     * \brief labelQuick the label representing the title of the Dialog
     */
    QLabel * labelQuick;
    /*!
     * \brief labelText the label representing the content text of the Dialog
     */
    QLabel * pLabelText;
    /*!
     * \brief labelDialogButtonBoxBg the label representing the DialogButton text of the Dialog
     */
    QBrush * labelDialogButtonBoxBg;

    static QPixmap * pixmapInfos;
    static QPixmap * pixmapTick;
    static QPixmap * pixmapCross;
    static QPixmap * pixmapWarn;

    QPoint origin;
    QPoint anchor;
    /*!
     * \brief moveAllowed boolean defining whether or not the Dialog is movable
     */
    bool moveAllowed;
};

#endif
