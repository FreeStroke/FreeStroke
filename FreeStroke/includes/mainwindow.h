/*!
 * \file mainwindow.h
 * \brief The MainWindow class represent the main Window. It instanciates the three views (ExecutionView, ExecutionView, ParametersView) of the application.
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtCore/QEvent>
#include <QtGui/QSystemTrayIcon>

#include "../../includes/gestures/executionmanager.h"
#include "../../includes/network/communication.h"
#include "../../includes/ui/executionview.h"
#include "../../includes/ui/listview.h"
#include "../../includes/ui/parametersview.h"

/*!
 * \brief The MainWindow class represent the main Window. It instanciates the three views (ExecutionView, ExecutionView, ParametersView) of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    /*!
     * \brief default MainWindow constructor
     * \param parent the parent of the windows
     */
    MainWindow(QWidget *parent = 0);
    /*!
     * \brief desctructor which close the connection
     */
    ~MainWindow();

    /*!
     * \brief showNotif displays a notification with a title, a message, an icon and the desired displayed time
     */
    void showNotif(QString, QString, QSystemTrayIcon::MessageIcon, int);
    /*!
     * \brief returns the ExecutionManager of the application
     * \return the ExecutionManager of the application
     */
    static ExecutionManager* getExecutionManager();
    /*!
     * \brief returns the Communication of the application
     * \return the Communication of the application
     */
    static Communication* getCommunication();
    /*!
     * \brief returns the ParameterView of the application
     * \return the ParameterView of the application
     */
    ParametersView *getParameterView();

    /*!
     * \brief closeEvent the event which is called when the MainWindow is closed. Ask the user to confirm to close the window.
     */
    void closeEvent(QCloseEvent *);

private:
    /*!
     * \brief createTopBar creates the TopBar which contains the three MenuButtonElement related to the three views
     * \return the TopBar created
     */
    QWidget* createTopBar();

    /*!
     * \brief sticon the system tray icon of the application
     */
    QSystemTrayIcon* sticon;
    /*!
     * \brief executionView the ExecutionView of the application
     */
    ExecutionView* executionView;
    /*!
     * \brief listView the ListView of the application
     */
    ListView* listView;
    /*!
     * \brief parametersView the ParametersView of the application
     */
    ParametersView* parametersView;

protected:
    bool eventFilter(QObject *object, QEvent *event);
    /*!
     * \brief event retrieve all the event sent to the MainWindow and catch the one that close the window as well as modifiers key.
     * \param event the event to catch
     * \return true if the event is recognized
     */
    bool event(QEvent *event);

public slots:
    /*!
     * \brief showExecution show the ExecutionView
     */
    void showExecution();
    /*!
     * \brief showList show the ListView
     */
    void showList();
    /*!
     * \brief showParameters show the ParametersView
     */
    void showParameters();

private slots:
    /*!
     * \brief open the MainWindow, set it visible and raise it
     */
    void open();
    /*!
     * \brief open the MainWindow, set it visible and raise it
     */
    void open(QSystemTrayIcon::ActivationReason);
    /*!
     * \brief hideWindow hide the MainWindow
     */
    void hideWindow();
    /*!
     * \brief close close the MainWindow
     */
    void close();
};

#endif // MAINWINDOW_H
