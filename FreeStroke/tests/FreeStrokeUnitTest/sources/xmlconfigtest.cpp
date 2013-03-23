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
#include <QtCore/QDebug>
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
 * Copyright (C) 2010 Université Paris-Est Marne-la-Vallée 
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
 *
 */

#include "../includes/xmlconfigtest.h"
#include "../../includes/xml/xml.h"
#include "../../includes/xml/xmlconf.h"
#include "../../includes/network/tcpclient.h"
#include "../../includes/network/udpclient.h"

XmlConfigTest::XmlConfigTest(std::string name) : CppUnit::TestCase(name) {}

void XmlConfigTest::runTest()
{
    qDebug()<<"Export";
    exportConfigTest();
    qDebug()<<"Import";
    importConfigTest();
}


void XmlConfigTest::exportConfigTest()
{
    // Test initial export
    XmlConf *conf = new XmlConf();
    CPPUNIT_ASSERT(Xml().exportConfig(conf, "test_conf.xml"));
    CPPUNIT_ASSERT(QFile::exists("test_conf.xml"));

    // Test modified exported config
    XmlConf *conf2 = new XmlConf();
    Controller *cont = new Controller("111.22.33.44", 1234, "testController");
    const QString mIp = QString("111.111.111.111");
    conf2->controller = cont;
    conf2->firstLaunch = false;
    conf2->language = "en";
    conf2->multicastIp = mIp;
    conf2->tcpPort = 2222;
    conf2->udpBindPort = 3333;
    conf2->udpPort = 4444;
    CPPUNIT_ASSERT(Xml().exportConfig(conf2, "test_conf2.xml"));
    CPPUNIT_ASSERT(QFile::exists("test_conf2.xml"));

}

void XmlConfigTest::importConfigTest()
{
    // Test initial config
    XmlConf *conf1 = Xml().importConfig("test_conf.xml");

    CPPUNIT_ASSERT(conf1->firstLaunch == true);
    CPPUNIT_ASSERT(conf1->tcpPort == 65535);
    CPPUNIT_ASSERT(conf1->udpPort == PORT);
    CPPUNIT_ASSERT(conf1->udpBindPort == PORT_RESP);
    CPPUNIT_ASSERT(conf1->multicastIp == MULTICAST_ADDR);
    CPPUNIT_ASSERT(conf1->language == QLocale::system().name().section('_', 0, 0));
    CPPUNIT_ASSERT(conf1->controller == NULL);

    // Test modified config
    XmlConf *conf2 = Xml().importConfig("test_conf2.xml");
    Controller *cont = new Controller("111.22.33.44", 1234, "testController");
    CPPUNIT_ASSERT(conf2->controller->getIpAddr().compare(cont->getIpAddr()) == 0);
    CPPUNIT_ASSERT(conf2->controller->getName().compare(cont->getName()) == 0);
    CPPUNIT_ASSERT(conf2->controller->getPort() == cont->getPort());
    CPPUNIT_ASSERT(conf2->firstLaunch == false);
    CPPUNIT_ASSERT(conf2->language == "en");
    const QString mIp = QString("111.111.111.111");
    CPPUNIT_ASSERT(conf2->multicastIp.compare(mIp) == 0);
    CPPUNIT_ASSERT(conf2->tcpPort == 2222);
    CPPUNIT_ASSERT(conf2->udpBindPort == 3333);
    CPPUNIT_ASSERT(conf2->udpPort == 4444);

    // Test non existant import
    XmlConf *conf3 = Xml().importConfig("no_test.xml");
    CPPUNIT_ASSERT(conf3->firstLaunch == true);
    CPPUNIT_ASSERT(conf3->tcpPort == 65535);
    CPPUNIT_ASSERT(conf3->udpPort == PORT);
    CPPUNIT_ASSERT(conf3->udpBindPort == PORT_RESP);
    CPPUNIT_ASSERT(conf3->multicastIp == MULTICAST_ADDR);
    CPPUNIT_ASSERT(conf3->language == QLocale::system().name().section('_', 0, 0));
    CPPUNIT_ASSERT(conf3->controller == NULL);

    // Remove exported files
    QFile("test_conf.xml").remove();
    QFile("test_conf2.xml").remove();
}
