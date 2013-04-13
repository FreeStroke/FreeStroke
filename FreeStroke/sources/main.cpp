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

#include <QtCore>
#include <QtWidgets>

#include "../includes/application.h"
#include "../includes/mainwindow.h"
#include "../includes/common/utils.h"
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

    result =  a.exec();
    QApplication::exit(result);
    return result;
}

#endif
