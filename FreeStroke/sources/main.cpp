#include <QtGui/QApplication>
#include <QtCore/QTranslator>

#include "../includes/application.h"
#include "../includes/mainwindow.h"
#include "../includes/common/utils.h"
#include "../includes/network/udpclient.h"
#include "../includes/network/communication.h"
#include "../includes/network/aes.h"
#include "../includes/gestures/executionmanager.h"
#include "../includes/xml/xmlconf.h"
#include "../includes/xml/xml.h"


/*! \mainpage FreeStroke documentation
 *
 * \section intro_sec Introduction
 *
 * This page contains all developer documentation needed to take your hand on it.
 */

#ifndef UNITTEST
void test();

int main(int argc, char *argv[])
{
    int result = -1;
    Application a(argc, argv);
    qDebug() << "";
    qDebug() << " ______ _____ ";
    qDebug() << "|  ____/ ____|";
    qDebug() << "| |__ | (___  ";
    qDebug() << "|  __| \\___ \\ ";
    qDebug() << "| |    ____) |";
    qDebug() << "|_|   |_____/ ";
    qDebug() << "  FreeStroke  ";
    qDebug() << "--------------";

    QString locale = QLocale::system().name().section('_', 0, 0);
    qDebug()<<"Detect lang : "<<locale;
    QTranslator translator;

    bool languageSet = false;
    XmlConf* conf = Xml().importConfig(Utils::getConfigLocation());
    if (conf != NULL)
    {
        if (conf->language != NULL)
        {
            if ((translator.load(Utils::getResourcesDirectory() + "tr/tr_" + conf->language) == true))
            {
                a.installTranslator(&translator);
                languageSet = true;
            }
        }
    }
    if (!languageSet && translator.load(Utils::getResourcesDirectory() + "tr/tr_" + locale) == true)
    {
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.show();
    w.raise();
    w.getParameterView()->checkFirstLaunch();
    w.getParameterView()->checkController();

    /*Command *c = new Command("/Applications/AppCleaner.app", SCRIPT);
    c->executeCommand();*/
    result =  a.exec();
    QApplication::exit(result);
    return result;
}

#endif
