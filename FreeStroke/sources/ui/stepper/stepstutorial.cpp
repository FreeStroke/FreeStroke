#include "../../includes/ui/stepper/stepstutorial.h"
#include "../../includes/daolayer/daolayer.h"
#include "../../includes/ui/video/videocomponent.h"
#include "../../includes/ui/element/button/buttonelement.h"
#include "../../includes/common/utils.h"
#include "../../includes/mainwindow.h"
#include "../../includes/ui/stepper/steppercontroller.h"
#include "../../includes/xml/xml.h"
#include "../../includes/xml/xmlconf.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>

StepsTutorial::StepsTutorial(QWidget *pParent, bool isFirstLaunch)
{
    bool showCancel = !isFirstLaunch;
    int labelFontSize = 16;
    QColor labelColor = QColor(230,230,230);
    this->stepper = new Stepper(pParent);

    /* STEP 1 */
    QWidget* step1 = new QWidget(pParent);
    step1->setFixedSize(600,400);
    QVBoxLayout* vLayoutStep1 = new QVBoxLayout(step1);
    Label* lblStep1Top = new Label(tr("\n\nWelcome on FreeStroke!\n\nThe purpose of FreeStroke is to allow you to configure actions on your computer \ntriggered by gestures you make face to the Kinect.\nThis tutorial will show you the basic features of the FreeStroke application and how \nto use it.\n\nThere is 3 main views in Freestroke:\n\n - Execution view: Display the real time stand of your body and list the last \nrecognized gestures.\n\n - Gestures list view: Display the list of the registered gestures on the left. Clicking \non a gesture display its representation in the center view\n\n - Parameters view: Here are the settings of FreeStroke.\n\n"),step1);
    lblStep1Top->setTextColor(labelColor);
    lblStep1Top->changeFontSize(labelFontSize);
    lblStep1Top->setAlignment(Qt::AlignLeft);

    vLayoutStep1->addWidget(lblStep1Top);
    stepper->addStep(tr("Presentation"),true,false,showCancel,step1);

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

        DialogButton* btnController = new DialogButton("Search",DialogButton::Dark,step2);
        btnController->setFixedHeight(35);
        connect(btnController, SIGNAL(clicked()), this, SLOT(discoverController()));
        stepper->addStep(tr("Presentation 2/2"),false,true,showCancel,step2);

        btnController->move(step2->width()/2 - btnController->width()/2, step2->height()/2 - btnController->height() /2 + 75);
    }
    /*else
    {
        /* STEP 2 bis */
        /*QWidget* step2 = new QWidget(pParent);
        step2->setFixedSize(600,400);
        QVBoxLayout* vLayoutStep2 = new QVBoxLayout(step2);
        VideoComponent *vp = new VideoComponent("/Users/guillaumedemurger/Documents/LastProject/FreeStroke/essai.gif", step2);
        vLayoutStep2->addWidget(vp);
        stepper->addStep(tr("How to change the KController"), true, true, showCancel, step2);
    }*/

    /* STEP 4 */
    QWidget* step4 = new QWidget(pParent);
    step4->setFixedSize(600,400);
    QVBoxLayout* vLayoutStep4 = new QVBoxLayout(step4);
    VideoComponent *vp = new VideoComponent("/Users/guillaumedemurger/Documents/LastProject/FreeStroke/essai.gif", step4);
    vLayoutStep4->addWidget(vp);
    stepper->addStep(tr("How to Register and Configure a Gesture"),true,true,showCancel,step4);

    /* STEP 5 */
    QWidget* step5 = new QWidget(pParent);
    step5->setFixedSize(600,400);
    QVBoxLayout* vLayoutStep5 = new QVBoxLayout(step5);
    Label* lblStep5Top = new Label(tr("\n\nYou finished the tutorial.\n\nWe hope you will have a good experience with FreeStroke.\n\n"),step5);
    lblStep5Top->setTextColor(labelColor);
    lblStep5Top->changeFontSize(labelFontSize);
    vLayoutStep5->addWidget(lblStep5Top);
    stepper->addStep(tr("Tutoriel finished"),true,true,showCancel,step5);
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
