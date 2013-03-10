/*!
 * \file menubuttonelement.h
 * \brief The MenuButtonElement class represent a custom button that is either selected or not and has a different look
 *  dependant to its state. Such buttons are made to be placed in a menu side by side.
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef MENUBUTTONELEMENT_H
#define MENUBUTTONELEMENT_H

#include <QtGui/QAbstractButton>

#include "../element.h"

/*!
 * \brief The MenuButtonElement class represent a custom button that is either selected or not and has a different look
 *  dependant to its state. Such buttons are made to be placed in a TopBar side by side.
 */
class MenuButtonElement : public QAbstractButton, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief the default MenuButtonElement constructor
     * \param pIcon the icon of the MenuButtonElement while not selected
     * \param pIconSelected the icon of the MenuButtonElement while selected
     * \param parent the container QWidget parent
     */
    MenuButtonElement(QPixmap pIcon, QPixmap pIconSelected, QWidget *parent = 0);
    /*!
     * \brief set the position of the MenuButtonElement
     * \param pX the desired x
     * \param pY the desired y
     */
    void setPosition(int pX, int pY);
    /*!
     * \brief set whether or not the MenuButtonElement is selected
     * \param pSelected boolean that set whether or not the MenuButtonElement is selected
     */
    void setSelected(bool pSelected);
    /*!
     * \brief set the MenuButtonElement as the last one of the menu which add a line of pixel to its right border
     * \param pLast boolean which set the MenuButtonElement as the last one of the menu
     */
    void setLast(bool pLast);

private:
    /*!
     * \brief boolean which hold the value of wether or not the MenuButtonElement is the last one of the menu
     */
    bool isLast;
    /*!
     * \brief the icon of the MenuButtonElement while not selected
     */
    QPixmap *pixmap;
    /*!
     * \brief the icon of the MenuButtonElement while selected
     */
    QPixmap *pixmapSelected;
    /*!
     * \brief the background of the MenuButtonElement while selected
     */
    QPixmap *pixmapBackgroundSelected;

protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
};

#endif // MENUBUTTONELEMENT_H
