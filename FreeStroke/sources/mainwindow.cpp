/*
* Projet de fin d'études LastProject de
* Adrien Broussolle
* Camille Darcy
* Guillaume Demurger
* Sylvain Fay-Chatelard
* Anthony Fourneau
* Aurèle Lenfant
* Adrien Madouasse
*
* Copyright (C) 2013 Université Paris-Est Marne-la-Vallée
*
* FreeStroke is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
*/
#include "../includes/mainwindow.h"
#include "../includes/common/utils.h"

#ifdef Q_OS_DARWIN
#include "../../includes/others/mac/mac.h"
#endif

#include "../../includes/application.h"
#include "../../includes/network/communication.h"
#include "../../includes/network/udpclient.h"
#include "../../includes/ui/element/button/menubuttonelement.h"
#include "../../includes/ui/maincontainer/maincontainer.h"
#include "../../includes/ui/topbar/topbar.h"
#include "../../includes/daolayer/daolayer.h"
#include "../../includes/xml/xml.h"
#include "../../includes/xml/xmlconf.h"

#include "../../includes/ui/notification/notifications.h"

/*!< The execution manager */
static ExecutionManager *executionManager = 0;

/*!< The communication thread */
static Communication *communication = 0;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // To setup the fullscreen mode
#ifdef Q_OS_DARWIN
    Mac m(this);
    Q_UNUSED(m);
#endif
    this->setMinimumSize(800, 600);

    QWidget* topBar = createTopBar();

    MainContainer *container = new MainContainer(this);

    this->executionView = new ExecutionView(container);
    this->executionView->show();
    this->listView = new ListView(container);
    this->listView->hide();
    this->parametersView = new ParametersView(container);
    this->parametersView->hide();

    container->addWidget(this->executionView);
    container->addWidget(this->listView);
    container->addWidget(this->parametersView);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(topBar);
    layout->addWidget(container);
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);

    QIcon icon(QDir::toNativeSeparators(Utils::getResourcesDirectory() + "fs-logo.png"));
    sticon = new QSystemTrayIcon(icon, this);

    QMenu *stmenu = new QMenu(tr("File"), this);
    QAction * openAction = new QAction(tr("Open"),this);
    openAction->setShortcuts(QKeySequence::Open);
    stmenu->addAction(openAction);

#ifdef Q_OS_DARWIN
    QAction * closeWindowAction = new QAction(tr("Close Window"),this);
    closeWindowAction->setShortcuts(QKeySequence::Close);
    stmenu->addAction(closeWindowAction);
    connect(closeWindowAction, SIGNAL(triggered()), this, SLOT(hideWindow()));
#endif

    QAction * closeAction = new QAction(tr("Close"),this);
    closeAction->setShortcuts(QKeySequence::Quit);
    stmenu->addAction(closeAction);

    sticon->setContextMenu(stmenu);
    sticon->show();
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

#ifndef Q_OS_DARWIN
    connect(sticon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(open(QSystemTrayIcon::ActivationReason)));
#endif
#ifdef Q_OS_DARWIN
    this->menuBar()->addMenu(stmenu);
#endif

    Notifications *n = new Notifications(this);
    Q_UNUSED(n);

    XmlConf *conf = Xml().importConfig(Utils::getConfigLocation());
    if (conf->firstLaunch)
    {
        this->showList();
    }

    // UDP and TCP communication thread
    communication = new Communication(conf->multicastIp, conf->udpPort, conf->udpBindPort);
    communication->start();

    executionManager = new ExecutionManager();
    executionManager->start();
    //Train LRA
    executionManager->startTraining();
}

MainWindow::~MainWindow()
{
    communication->close();
}

ParametersView* MainWindow::getParameterView()
{
    return this->parametersView;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    return QMainWindow::event(event);
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::Close)
    {
        QWidget * w = QApplication::focusWidget();
        KeyListener *keyListener = dynamic_cast<KeyListener*>(w);
        if (keyListener != NULL)
        {
            keyListener->keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_F4, Qt::AltModifier));
            event->ignore();
            return true;
        }
    }
    else if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        bool shift = false;
        bool ctrl = false;
        bool meta = false;
        if (keyEvent->key() == Qt::Key_Control)
        {
            ctrl = true;
        }
        if (keyEvent->key() == Qt::Key_Shift)
        {
            shift = true;
        }
        if (keyEvent->key() == Qt::Key_Meta)
        {
            meta = true;
        }
        Application::setModifiers(ctrl, shift, meta);

        QWidget * w = QApplication::focusWidget();
        KeyListener *keyListener = dynamic_cast<KeyListener*>(w);
        if (keyEvent != NULL && (keyEvent->key() == Qt::Key_Tab ||
                                 (keyEvent->key() == Qt::Key_Q && keyEvent->modifiers() == Qt::MetaModifier))
                && keyListener != NULL)
        {
            event->ignore();
            return true;
        }
    }
    else if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        bool shift = false;
        bool ctrl = false;
        bool meta = false;

        if (keyEvent->modifiers() & Qt::ControlModifier)
        {
            ctrl = true;
        }
        if (keyEvent->modifiers() & Qt::ShiftModifier)
        {
            shift = true;
        }
        if (keyEvent->modifiers() & Qt::MetaModifier)
        {
            meta = true;
        }

        if (keyEvent->key() == Qt::Key_Control)
        {
            ctrl = false;
        }
        if (keyEvent->key() == Qt::Key_Shift)
        {
            shift = false;
        }
        if (keyEvent->key() == Qt::Key_Meta)
        {
            meta = false;
        }

        Application::setModifiers(ctrl, shift, meta);
    }
    return QMainWindow::event(event);
}

void MainWindow::closeEvent(QCloseEvent * e)
{
    QWidget * w = QApplication::focusWidget();
    KeyListener *keyListener = dynamic_cast<KeyListener*>(w);
    if(keyListener != NULL)
    {
#if !defined(Q_OS_WIN32)
        keyListener->keyPressEvent(new QKeyEvent(QEvent::KeyPress, Qt::Key_Q, Qt::ControlModifier));
#endif
        return;
    }
    Dialog *d = new Dialog("", this);
    d->addButton(tr("Yes"), Dialog::Accept, DialogButton::Normal, true);
    d->addButton(tr("No"), Dialog::Reject, DialogButton::Normal);
    Dialog::DialogCode dc;
    dc = d->displayNotification(Dialog::Information, tr("This application should not be closed."), tr("Do you really want to close FreeStroke ?"));
    if (dc == Dialog::Accepted)
    {
        DAOLayer *dao = DAOLayer::getInstance();
        if(dao != NULL)
        {
            delete dao;
        }
        delete this->sticon;
        QCoreApplication::quit();
    }
    if (e != NULL)
    {
        e->ignore();
    }
    this->hideWindow();
}

void MainWindow::open(QSystemTrayIcon::ActivationReason reason)
{
    if(reason != QSystemTrayIcon::Context)
    {
        this->open();
    }
}

void MainWindow::open()
{
    this->setVisible(true);
    this->show();
    this->raise();
}

void MainWindow::hideWindow()
{
    this->hide();
}

void MainWindow::close()
{
    this->closeEvent(NULL);
}

QWidget* MainWindow::createTopBar()
{
    QWidget *topBarWidget = new QWidget(this);
    QHBoxLayout *topBarLayout = new QHBoxLayout(topBarWidget);

    topBarLayout->setSpacing(0);
    topBarLayout->setMargin(0);

    TopBar *topBar = new TopBar(topBarWidget);
    MenuButtonElement *menuExecution = new MenuButtonElement(QPixmap(Utils::getResourcesDirectory()+"topbar-realtime.png"),
                                                             QPixmap(Utils::getResourcesDirectory()+"topbar-realtime-selected.png"),
                                                             topBar);

    MenuButtonElement *menuList = new MenuButtonElement(QPixmap(Utils::getResourcesDirectory()+"topbar-list.png"),
                                                        QPixmap(Utils::getResourcesDirectory()+"topbar-list-selected.png"),
                                                        topBar);

    MenuButtonElement *menuSettings = new MenuButtonElement(QPixmap(Utils::getResourcesDirectory()+"topbar-settings.png"),
                                                            QPixmap(Utils::getResourcesDirectory()+"topbar-settings-selected.png"),
                                                            topBar);

    XmlConf *conf = Xml().importConfig(Utils::getConfigLocation());
    if (conf->firstLaunch)
    {
        menuList->setChecked(true);
    }
    else
    {
        menuExecution->setChecked(true);
    }

    menuSettings->setLast(true);

    connect(menuExecution, SIGNAL(clicked()), this, SLOT(showExecution()));
    connect(menuList, SIGNAL(clicked()), this, SLOT(showList()));
    connect(menuSettings, SIGNAL(clicked()), this, SLOT(showParameters()));

    topBar->addButton(menuExecution);
    topBar->addButton(menuList);
    topBar->addButton(menuSettings);
    topBarLayout->addWidget(topBar);
    topBarWidget->setFixedHeight(topBar->height());
    return topBarWidget;
}

void MainWindow::showExecution()
{
    this->listView->hide();
    this->parametersView->hide();
    this->executionView->show();
    this->listView->getGestureListView()->resetFocus();
}

void MainWindow::showList()
{
    this->executionView->hide();
    this->parametersView->hide();
    this->listView->show();
    this->listView->getGestureListView()->resetFocus();
}

void MainWindow::showParameters()
{
    this->executionView->hide();
    this->listView->hide();
    this->parametersView->show();
}

void MainWindow::showNotif(QString title, QString message, QSystemTrayIcon::MessageIcon icon, int ms)
{
    sticon->showMessage(title,message,icon,ms);
}

ExecutionManager* MainWindow::getExecutionManager()
{
    return executionManager;
}

Communication* MainWindow::getCommunication()
{
    return communication;
}
