/*!
 * \file mainwindow.h
 * \brief
 * \author Sylvain Fay-Châtelard
 * \date 2013-02-20
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QtGui/QApplication>
#include <QtGui/QKeyEvent>
#include "mainwindow.h"

class Application : public QApplication
{
	Q_OBJECT
public:
    Application(int &argc, char **argv);
    void setMainWindow(MainWindow *pMainWindow);

    static void restart();
    static Qt::KeyboardModifier getModifiers();
    static void setModifiers(bool pCtrl, bool pShift, bool pMeta);
protected:
    bool notify (QObject * receiver, QEvent *e);
};

#endif
