/*!
 * \file executionview.h
 * \brief The ExecutionView class hold all the component of the excution view of the application
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */
#ifndef EXECUTIONVIEW_H
#define EXECUTIONVIEW_H

#include <QtGui/QWidget>

#include "gesturelistview/gesturelistview.h"
#include "../../includes/ui/element/label/label.h"
#include "../../includes/ui/element/button/buttonelement.h"

/*!
 * \brief The ExecutionView class hold all the component of the excution view of the application. It display a GLView with a realtime
 * representation of the user as well as the history of all the Gesture recognized.
 */
class ExecutionView : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief default ExecutionView constructor
     * \param parent the container QWidget parent
     */
    explicit ExecutionView(QWidget *parent = 0);
    /*!
     * \brief getGlView returns the GLView of the ExecutionView
     * \return the GLView of the ExecutionView
     */
    GlView* getGlView();

private:
    /*!
     * \brief create the view
     */
    void createView();
    /*!
     * \brief historyChanged is called when the contents of the List containing the HistoryRecord has changed.
     * It shows or hides a label saying that there is no history and enable or disable the button allowing to empty the
     * history.
     */
    void historyChanged();
    /*!
     * \brief gestureListView the GestureListView containing the HistoryRecord
     */
    GestureListView* gestureListView;
    /*!
     * \brief dao the DAOLayer used by the GestureListView
     */
    DAOLayer* dao;
    /*!
     * \brief glView the GLView used to represent the real time view of the user
     */
    GlView* glView;
    /*!
     * \brief labelNoHistory the label visible when there is no HistoryRecord to display
     */
    Label* labelNoHistory;
    /*!
     * \brief btnTrash the ButtonElement used to empty the history
     */
    ButtonElement* btnTrash;

private slots:
    /*!
     * \brief skeletonDataRecieved slot called when a SkeletonData has been recieved. It sends it to the GlView to display it
     * \param pData the QString representing the SkeletonData
     */
    void skeletonDataRecieved(QString pData);
    /*!
     * \brief historyRecordAdded slot called when a HistoryRecord has been added to the DAOLayer. It insert it to the GestureListView
     */
    void historyRecordAdded(HistoryRecord*);
    /*!
     * \brief historyRecordDeleted slot called when a HistoryRecord has been deleted to the DAOLayer. It remove it from the GestureListView
     */
    void historyRecordDeleted();
    /*!
     * \brief deleteHistoryRecord slot called when the history has been emptied. It removes all the HistoryRecord from the GestureListView
     */
    void deleteHistoryRecord();
};

#endif // EXECUTIONVIEW_H
