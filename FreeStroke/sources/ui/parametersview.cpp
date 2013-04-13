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
#include "../../includes/ui/parametersview.h"

#include "../../includes/application.h"
#include "../../includes/mainwindow.h"
#include "../../includes/ui/element/button/buttonelement.h"
#include "../../includes/ui/element/textfield/textfield.h"
#include "../../includes/ui/element/label/label.h"
#include "../../includes/ui/stepper/steppercontroller.h"
#include "../../includes/ui/stepper/stepstutorial.h"
#include "../../includes/common/utils.h"
#include "../../includes/xml/xml.h"

#define LBL_WIDTH 170

ParametersView::ParametersView(QWidget *parent) : QWidget(parent)
{
    this->isFirstLaunch = false;

    QHBoxLayout* layout = new QHBoxLayout(this);
    QWidget* container = new QWidget(this);
    QFormLayout* formLayout = new QFormLayout(container);
    formLayout->setContentsMargins(30,30,30,30);
    formLayout->setSpacing(30);

    Label* labelChangeController = new Label(tr("Change the controller"),container);
    labelChangeController->setFixedWidth(LBL_WIDTH);
    labelChangeController->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ButtonElement* btnChangeController = new ButtonElement(container);
    btnChangeController->setMaximumWidth(150);
    btnChangeController->setText(tr("Change"));
    connect(btnChangeController,SIGNAL(clicked()),this,SLOT(discoverController()));

    Label* labelShowTutorial = new Label(tr("Show the tutorial"),container);
    labelShowTutorial->setFixedWidth(LBL_WIDTH);
    labelShowTutorial->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ButtonElement* btnShowTutorial = new ButtonElement(container);
    btnShowTutorial->setMaximumWidth(150);
    btnShowTutorial->setText(tr("Show"));
    connect(btnShowTutorial, SIGNAL(clicked()), this, SLOT(launchTutorial()));

    Label* labelChangeTCP = new Label(tr("Change TCP Port"),container);
    labelChangeTCP->setFixedWidth(LBL_WIDTH);
    labelChangeTCP->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    labelChangeTCP->hide();
    TextField* tfChangeTCP = new TextField(container);
    tfChangeTCP->setMaximumWidth(150);
    connect(tfChangeTCP, SIGNAL(textChanged(QString)), this, SLOT(changeTCPPort(QString)));
    tfChangeTCP->setValidator(new QIntValidator(1, 65535, tfChangeTCP));
    tfChangeTCP->hide();

    Label* labelChangeUDP = new Label(tr("Change UDP Port"),container);
    labelChangeUDP->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    labelChangeUDP->setFixedWidth(LBL_WIDTH);
    TextField* tfChangeUDP = new TextField(container);
    tfChangeUDP->setMaximumWidth(150);
    connect(tfChangeUDP, SIGNAL(textChanged(QString)), this, SLOT(changeUDPPort(QString)));
    QIntValidator(1, 65535, tfChangeUDP);
    tfChangeUDP->setValidator(new QIntValidator(1, 65535, tfChangeUDP));

    Label* labelChangeUdpBind = new Label(tr("Change UDP bound port"),container);
    labelChangeUdpBind->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    labelChangeUdpBind->setFixedWidth(LBL_WIDTH);
    TextField* tfChangeUdpBind = new TextField(container);
    tfChangeUdpBind->setMaximumWidth(150);
    connect(tfChangeUdpBind, SIGNAL(textChanged(QString)), this, SLOT(changeUDPPortBind(QString)));
    QIntValidator(1, 65535, tfChangeUdpBind);
    tfChangeUdpBind->setValidator(new QIntValidator(1, 65535, tfChangeUdpBind));

    Label* labelChangeLanguage = new Label(tr("Change language"),container);
    labelChangeLanguage->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    labelChangeLanguage->setFixedWidth(LBL_WIDTH);
    ComboBox* comboLanguage = new ComboBox(container);
    comboLanguage->setMaximumWidth(150);
    comboLanguage->addItem("English");
    comboLanguage->addItem(QString::fromUtf8("Français"));
    connect(comboLanguage, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeLanguage(QString)));

    formLayout->addRow(labelChangeController, btnChangeController);
    formLayout->addRow(labelShowTutorial, btnShowTutorial);
    //formLayout->addRow(labelChangeTCP, tfChangeTCP);
    formLayout->addRow(labelChangeUDP, tfChangeUDP);
    formLayout->addRow(labelChangeUdpBind, tfChangeUdpBind);
    formLayout->addRow(labelChangeLanguage, comboLanguage );

    layout->addWidget(container);

    XmlConf* conf = Xml().importConfig(Utils::getConfigLocation());
    if (conf != NULL)
    {
        if(conf->tcpPort != 0)
        {
            tfChangeTCP->setText(QString::number(conf->tcpPort));
        }
        if(conf->udpPort != 0)
        {
            tfChangeUDP->setText(QString::number(conf->udpPort));
        }
        if (conf->udpBindPort != 0)
        {
            tfChangeUdpBind->setText(QString::number(conf->udpBindPort));
        }
        if(!conf->language.isEmpty() && !conf->language.isNull())
        {
            if (conf->language == "fr")
            {
                comboLanguage->setCurrentIndex(comboLanguage->findText(QString::fromUtf8("Français")));
            }
            else if (conf->language == "en")
            {
                comboLanguage->setCurrentIndex(comboLanguage->findText("English"));
            }
        }
    }
}

void ParametersView::checkController()
{
    disconnect(MainWindow::getCommunication(), SIGNAL(tcpConnectionRefused()),0,0);
    disconnect(MainWindow::getCommunication(), SIGNAL(tcpConnectionClosed()),0,0);

    Xml* xml = new Xml();
    XmlConf* conf = xml->importConfig(Utils::getConfigLocation());

    if(conf == NULL)
    {
        qDebug() << "CANNOT OPEN CONF";
        discoverController();
    }
    else
    {
        if (conf->controller != NULL)
        {
            connect(MainWindow::getCommunication(), SIGNAL(tcpConnectionRefused()),this,SLOT(discoverController()));
            connect(MainWindow::getCommunication(), SIGNAL(tcpConnectionClosed()),this,SLOT(discoverController()));
            MainWindow::getCommunication()->initTcpCommunication(conf->controller);
        }
    }
}

void ParametersView::discoverController()
{
    disconnect(MainWindow::getCommunication(), SIGNAL(tcpConnectionRefused()),0,0);
    disconnect(MainWindow::getCommunication(), SIGNAL(tcpConnectionClosed()),0,0);

    MainWindow::getCommunication()->close();
    StepperController* stepper = new StepperController(this);
    connect(MainWindow::getCommunication(), SIGNAL(tcpConnectionEstablished()), stepper, SLOT(next()));
    QWidget* step1 = new QWidget(this);
    step1->setFixedSize(600,400);
    QVBoxLayout* layout = new QVBoxLayout(step1);

    Label* label = new Label(tr("Looking for available Controller"),step1);
    label->changeFontSize(18);
    label->setTextColor(QColor(255,255,255));

    QWidget *loader = new QWidget(step1);
    QLabel* labelLoading = new QLabel(loader);
    QMovie* loading = new QMovie(Utils::getResourcesDirectory() + "loader.gif", QByteArray(), labelLoading);
    labelLoading->resize(128, 128);
    labelLoading->setMovie(loading);
    loading->start();

    layout->addWidget(label);
    layout->addWidget(loader);

    stepper->addStep(tr("Adding Controller"),false,false,false,step1);
    labelLoading->move(loader->width()/2 - 128/2, 0);

    QWidget* step2 = new QWidget(stepper);
    step2->setFixedSize(600,400);

    stepper->addStep(tr("Available Controller"),false,false,true,step2);

    QWidget* step3 = new QWidget();
    step3->setFixedSize(600,400);

    QWidget *loaderStep3 = new QWidget(step3);
    QLabel* labelLoadingStep3 = new QLabel(loaderStep3);
    QMovie* loadingStep3 = new QMovie(Utils::getResourcesDirectory() + "loader.gif", QByteArray(), labelLoadingStep3);
    labelLoadingStep3->resize(128, 128);
    labelLoadingStep3->setMovie(loadingStep3);
    loadingStep3->start();

    stepper->addStep(tr("Connection to Controller"),false,false,false,step3);
    labelLoadingStep3->move(step3->width()/2 - labelLoadingStep3->width()/2, step3->height()/2 - labelLoadingStep3->height()/2);

    int code = stepper->exec();

    if (code == QDialog::Rejected)
    {
        Dialog *d = new Dialog(tr("Controller needed"), this);
        d->addButton(tr("Exit"), Dialog::Accept, DialogButton::Normal, true);
        d->displayNotification(Dialog::Information,tr("Controller needed"), tr("You must have a Controller to use FreeStroke"));
        //        QCoreApplication::quit();
        return;
    }

    Xml* xml = new Xml();
    XmlConf* conf = xml->importConfig(Utils::getConfigLocation());
    if(conf != NULL)
    {
        conf->controller = MainWindow::getCommunication()->getController();
        xml->exportConfig(conf, Utils::getConfigLocation());
    }
    else
    {
        conf = new XmlConf();
        conf->controller = MainWindow::getCommunication()->getController();
        if (xml->exportConfig(conf, Utils::getConfigLocation()) == 1)
        {
            qDebug() << "CANNOT WRITE FILE";
        }
    }

    connect(MainWindow::getCommunication(), SIGNAL(tcpConnectionRefused()),this,SLOT(discoverController()));
    connect(MainWindow::getCommunication(), SIGNAL(tcpConnectionClosed()),this,SLOT(discoverController()));
}

void ParametersView::changeUDPPort(QString pPort)
{
    XmlConf* conf = Xml().importConfig(Utils::getConfigLocation());
    if (conf != NULL)
    {
        conf->udpPort = pPort.toInt();
        Xml().exportConfig(conf, Utils::getConfigLocation());
    }
    if(MainWindow::getCommunication() != NULL)
    {
        MainWindow::getCommunication()->setUdpPort((quint16)pPort.toShort());
    }
}

void ParametersView::changeUDPPortBind(QString pBindPort)
{
    XmlConf* conf = Xml().importConfig(Utils::getConfigLocation());
    if (conf != NULL)
    {
        conf->udpBindPort = pBindPort.toInt();
        Xml().exportConfig(conf, Utils::getConfigLocation());
    }
    if(MainWindow::getCommunication() != NULL)
    {
        MainWindow::getCommunication()->setUdpBindPort((quint16)pBindPort.toShort());
    }
}

void ParametersView::changeTCPPort(QString pPort)
{
    XmlConf* conf = Xml().importConfig(Utils::getConfigLocation());
    if (conf != NULL)
    {
        disconnect(MainWindow::getCommunication(), SIGNAL(tcpConnectionRefused()),0,0);
        disconnect(MainWindow::getCommunication(), SIGNAL(tcpConnectionClosed()),0,0);

        conf->tcpPort = pPort.toInt();
        Xml().exportConfig(conf, Utils::getConfigLocation());

        connect(MainWindow::getCommunication(), SIGNAL(tcpConnectionRefused()),this,SLOT(discoverController()));
        connect(MainWindow::getCommunication(), SIGNAL(tcpConnectionClosed()),this,SLOT(discoverController()));
    }
}

void ParametersView::changeLanguage(QString pLanguage)
{
    bool languageChanged = false;
    XmlConf* conf = Xml().importConfig(Utils::getConfigLocation());
    if (conf != NULL)
    {
        if(pLanguage == QString::fromUtf8("Français"))
        {
            if (conf->language != "fr")
            {
                conf->language="fr";
                languageChanged = true;
            }

        }
        else if (pLanguage == "English")
        {
            if (conf->language != "en")
            {
                conf->language="en";
                languageChanged = true;
            }
        }
        if(languageChanged)
        {
            Xml().exportConfig(conf, Utils::getConfigLocation());
            Dialog *d = new Dialog(tr("Restart needed"), this);
            d->addButton(tr("Close"), Dialog::Reject, DialogButton::Bright);
            d->addButton(tr("Restart"), Dialog::Accept, DialogButton::Normal, true);
            if(Dialog::Accepted == d->displayNotification(Dialog::Information,tr("Restart needed"), tr("You need to restart FreeStroke to change the language")))
            {
                Application::restart();
            }
        }
    }
}

void ParametersView::checkFirstLaunch()
{
    XmlConf* conf = Xml().importConfig(Utils::getConfigLocation());
    if(conf != NULL)
    {
        this->isFirstLaunch = conf->firstLaunch;
        if(this->isFirstLaunch)
        {
            this->launchTutorial();
        }
    }
}

void ParametersView::launchTutorial()
{
    StepsTutorial *stepper = new StepsTutorial(this, this->isFirstLaunch);
    MainWindow::getExecutionManager()->standby();
    int code = stepper->show();
    delete stepper;
    stepper = NULL;
    if(this->isFirstLaunch && code == Dialog::Rejected)
    {
#ifdef QT_NO_DEBUG
        exit(0);
#endif
    }
    if (this->isFirstLaunch && code == Dialog::Accepted)
    {
        XmlConf *conf = Xml().importConfig(Utils::getConfigLocation());
        if (conf != NULL)
        {
            conf->firstLaunch = false;
            Xml().exportConfig(conf, Utils::getConfigLocation());
            this->isFirstLaunch = false;
        }
    }
}

void ParametersView::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(239,239,239));
    p.drawRect(this->rect());
}
