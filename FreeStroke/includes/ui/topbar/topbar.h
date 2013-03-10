/*!
 * \file topbar.h
 * \brief The TopBar class is a QWidget with no margin and no spacing which is made to hold MenuButtonElement.
 * Its height is fixed to 50. It uses a QButtonGroup so that only one MenuButtonElement can be selected at a time
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef TOPBAR_H
#define TOPBAR_H

#include <QtGui/QWidget>
#include <QtGui/QButtonGroup>

#include "../element/button/menubuttonelement.h"
/*!
 * \brief The TopBar class is a QWidget with no margin and no spacing which is made to hold MenuButtonElement.
 * Its height is fixed to 50. It uses a QButtonGroup so that only one MenuButtonElement can be selected at a time
 */
class TopBar : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief default TopBar constructor
     * \param parent the container QWidget parent
     */
    TopBar(QWidget *parent = 0);
    /*!
     * \brief add a MenuButtonElement to the TopBar
     * \param pButton the desired MenuButtonElement
     */
    void addButton(MenuButtonElement * pButton);

protected:
    void paintEvent(QPaintEvent *e);

private:
    /*!
     * \brief the QButtonGroup used to be able to select only one MenuButtonElement at a time
     */
      QButtonGroup *group;
};

#endif // TOPBAR_H
