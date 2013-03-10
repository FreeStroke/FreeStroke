/*!
 * \file cellcontroller.h
 * \brief The Cell controller class represent a specific cell used to display available controllers
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */
#ifndef CELLCONTROLLER_H
#define CELLCONTROLLER_H

#include "../../includes/ui/cell/cell.h"
#include "../../includes/common/controller.h"

/*!
 * \brief The Cell controller class represent a specific cell used to display available controllers
 */
class CellController : public Cell
{
public:
    /*!
     * \brief Main controller
     * \param pList list of available controllers
     */
    explicit CellController(void* pList);

    /*!
     * \brief Setter for controller association to the ell
     * \param pController the controller to associate
     */
    void setController(Controller* pController);

private:
    Label* labelController; /*!< The label used to display the controllers name */
    QLabel* iconChoose;  /*!< The icon used displayed next to the controllers name */

protected:
    void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent *e);
};

#endif // CELLCONTROLLER_H
