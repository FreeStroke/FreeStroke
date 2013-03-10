/*!
 * \file buttonelement.h
 * \brief The ButtonElement class is a button with a custom look
 * \author Aurèle Lenfant (thanks to Romain Etchegoyhen)
 * \date 2013-02-20
 */
#ifndef BUTTONELEMENT_H
#define BUTTONELEMENT_H

#include <QtGui/QAbstractButton>

#include "../element.h"

/*!
 * \brief The ButtonElement class is a QPushButton with a custom look
 */
class ButtonElement : public QAbstractButton, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief the default ButtonElement constructor
     * \param parent the QWidget container parent
     */
    ButtonElement(QWidget *parent = 0);
    /*!
     * \brief set the position of the ButtonElement
     * \param pX the desired x
     * \param pY the desired y
     */
    void setPosition(int pX, int pY);
    /*!
     * \brief adjust the size of the ButtonElement
     */
    void adjustSize();
    /*!
     * \brief set the text of the ButtonElement
     * \param title the desired text
     */
    void setText(QString title);
    /*!
     * \brief set the icon of the ButtonElement
     * \param icon the desired icon
     */
    void setIcon(QPixmap icon);

private:
    /*!
     * \brief hasIcon boolean that determined if the ButtonElement has an icon
     */
    bool hasIcon;
    /*!
     * \brief hasText boolean that determined if the ButtonElement has a text
     */
    bool hasText;

    /*!
     * \brief pixmap the icon of the ButtonElement
     */
    QPixmap pixmap;
    /*!
     * \brief text the text of the ButtonElement
     */
    QString text;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // BUTTONELEMENT_H
