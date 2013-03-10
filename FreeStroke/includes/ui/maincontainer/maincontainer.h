/*!
 * \file maincontainer.h
 * \brief The MainContainer class is the QWidget contening all the view of the application
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef MAINCONTAINER_H
#define MAINCONTAINER_H

#include <QtGui/QWidget>
#include <QtCore/QList>
#include <QtCore/QString>

/*!
 * \brief The MainContainer class is the QWidget contening all the view of the application
 */
class MainContainer: public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief default MainContainer constructor
     * \param parent the container QWidget parent
     */
    explicit MainContainer(QWidget *parent);

    /*!
     * \brief addWidget add a Widget to the Container
     * \param pWidget the Widget to add to the Container
     */
    void addWidget(QWidget* pWidget);

protected:
    void resizeEvent(QResizeEvent * e);

private:
    /*!
     * \brief widgets the QList containing all the Widget of the Container
     */
    QList<QWidget*> widgets;


};

#endif // MAINCONTAINER_H
