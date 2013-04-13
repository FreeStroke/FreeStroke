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
#include "../../includes/ui/stepper/stepstutorial.h"
#include "../../includes/daolayer/daolayer.h"
#include "../../includes/ui/video/videocomponent.h"
#include "../../includes/ui/element/button/buttonelement.h"
#include "../../includes/common/utils.h"
#include "../../includes/mainwindow.h"
#include "../../includes/ui/stepper/steppercontroller.h"
#include "../../includes/xml/xml.h"
#include "../../includes/xml/xmlconf.h"

StepsTutorial::StepsTutorial(QWidget *pParent, bool isFirstLaunch)
{
    int labelFontSize = 16;
    QColor labelColor = QColor(230,230,230);
    this->stepper = new Stepper(pParent);

    /* Local */
    QString locale = QLocale::system().name().section('_', 0, 0);
    XmlConf* conf = Xml().importConfig(Utils::getConfigLocation());
    if (conf != NULL)
    {
        if (conf->language != NULL)
        {
            locale = conf->language;
        }
    }
    if (locale.compare("en") != 0 && locale.compare("fr") != 0)
    {
        locale = "en";
    }

    /* STEP 1 */
    QWidget* step1 = new QWidget(pParent);
    step1->setFixedSize(600,400);
    QVBoxLayout* vLayoutStep1 = new QVBoxLayout(step1);
    Label* lblStep1Top = new Label(tr("\n\nWelcome on FreeStroke!\n\nThis tutorial will explain you how to use the application.\n\n"),step1);
    lblStep1Top->setTextColor(labelColor);
    lblStep1Top->changeFontSize(labelFontSize);
    lblStep1Top->setAlignment(Qt::AlignCenter);
    lblStep1Top->setPaintShadow(false);
    lblStep1Top->changeFontSize(labelFontSize);
    vLayoutStep1->addWidget(lblStep1Top);
    stepper->addStep(tr("Presentation"),true,false,true,step1);

    if(isFirstLaunch)
    {
        /* STEP 2 */
        QWidget* step2 = new QWidget(pParent);
        step2->setFixedSize(600,400);
        QVBoxLayout* vLayoutStep2 = new QVBoxLayout(step2);
        Label* lblStep2 = new Label(tr("You can search for available Controller now.\nYou must have one to use the application."),step2);
        lblStep2->setTextColor(labelColor);
        lblStep2->changeFontSize(18);
        lblStep2->setPaintShadow(false);
        vLayoutStep2->addWidget(lblStep2);

        DialogButton* btnController = new DialogButton(tr("Search"),DialogButton::Dark,step2);
        btnController->setFixedHeight(35);
        connect(btnController, SIGNAL(clicked()), this, SLOT(discoverController()));
        stepper->addStep(tr("Presentation 2/2"),false,true,true,step2);

        btnController->move(step2->width()/2 - btnController->width()/2, step2->height()/2 - btnController->height() /2 + 75);
    }

    /* STEP 3 */
    QWidget* step4 = new QWidget(pParent);
    step4->setFixedSize(600,400);
    QVBoxLayout* vLayoutStep4 = new QVBoxLayout(step4);
    vLayoutStep4->setSpacing(0);
    vLayoutStep4->setMargin(0);
    QLabel *picRegister = new QLabel(step4);
    picRegister->resize(600, 400);
    picRegister->setPixmap(QPixmap(Utils::getResourcesDirectory() + "/tuto/register_" + locale + ".png"));
    stepper->addStep(tr("Recording mode"),true,true,!isFirstLaunch,step4);

    /* STEP 4 */
    QWidget* step5 = new QWidget(pParent);
    step5->setFixedSize(600,400);
    QVBoxLayout* vLayoutStep5 = new QVBoxLayout(step5);
    vLayoutStep5->setMargin(0);
    Label* lblStep5Top = new Label(tr("\n\nThe recording of a gesture MUST start and end with a neutral stance.\n\n"),step5);
    lblStep5Top->setTextColor(labelColor);
    lblStep5Top->changeFontSize(labelFontSize);
    lblStep5Top->setPaintShadow(false);
    lblStep5Top->setFixedHeight(60);
    QLabel *picNeutral = new QLabel(step5);
    QPixmap pix = QPixmap(Utils::getResourcesDirectory() + "/tuto/neutral_" + locale + ".png");
    picNeutral->setPixmap(pix);
    vLayoutStep5->addWidget(lblStep5Top);
    vLayoutStep5->addWidget(picNeutral);
    stepper->addStep(tr("Neutral Position"),true,true,!isFirstLaunch,step5);

    /* STEP 5 */
    QWidget* step6 = new QWidget(pParent);
    step6->setFixedSize(600,400);
    QLabel *picExecution = new QLabel(step6);
    picExecution->resize(600, 400);
    picExecution->setPixmap(QPixmap(Utils::getResourcesDirectory() + "/tuto/execution_" + locale + ".png"));
    stepper->addStep(tr("Execution mode"),true,true,!isFirstLaunch,step6);

}

void StepsTutorial::discoverController()
{
    MainWindow::getCommunication()->close();
    StepperController* stepperCtrl = new StepperController();
    connect(MainWindow::getCommunication(),SIGNAL(tcpConnectionEstablished()),this->stepper,SLOT(next()));
    connect(MainWindow::getCommunication(),SIGNAL(tcpConnectionEstablished()),stepperCtrl,SLOT(next()));
    stepperCtrl->setAttribute(Qt::WA_DeleteOnClose,false);

    QWidget* step1 = new QWidget();
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

    stepperCtrl->addStep(tr("Adding Controller"),false,false,false,step1);
    labelLoading->move(loader->width()/2 - labelLoading->width()/2, 0);

    QWidget* step2 = new QWidget(stepperCtrl);
    step2->setFixedSize(600,400);

    stepperCtrl->addStep(tr("Available Controller"),false,false,true,step2);

    QWidget* step3 = new QWidget();
    step3->setFixedSize(600,400);

    QWidget *loaderStep3 = new QWidget(step3);
    QLabel* labelLoadingStep3 = new QLabel(loaderStep3);
    QMovie* loadingStep3 = new QMovie(Utils::getResourcesDirectory() + "loader.gif", QByteArray(), labelLoadingStep3);
    labelLoadingStep3->resize(128, 128);
    labelLoadingStep3->setMovie(loadingStep3);
    loadingStep3->start();

    stepperCtrl->addStep(tr("Connection to Controller"),false,false,false,step3);
    labelLoadingStep3->move(step3->width()/2 - labelLoadingStep3->width()/2, step3->height()/2 - labelLoadingStep3->height()/2);

    stepperCtrl->exec();
    disconnect(MainWindow::getCommunication(),SIGNAL(tcpConnectionEstablished()),0,0);

    Xml* xml = new Xml();
    XmlConf* conf = xml->importConfig(Utils::getConfigLocation());
    if(conf != NULL && MainWindow::getCommunication()->getController() != NULL)
    {
        conf->controller = MainWindow::getCommunication()->getController();
        xml->exportConfig(conf, Utils::getConfigLocation());
    }
    else if (MainWindow::getCommunication()->getController() != NULL)
    {
        conf = new XmlConf();
        conf->controller = MainWindow::getCommunication()->getController();
        if (xml->exportConfig(conf, Utils::getConfigLocation()) == 1)
        {
            qDebug() << "CANNOT WRITE FILE";
        }
    }

    if (stepperCtrl != NULL)
    {
        delete stepperCtrl;
        stepperCtrl = NULL;
    }
}

int StepsTutorial::show()
{
    return this->stepper->exec();
}
