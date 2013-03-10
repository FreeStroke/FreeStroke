#include "../../includes/network/tcpclient.h"
#include "../../includes/network/udpclient.h"
#include "../../includes/xml/xmlconf.h"

XmlConf::XmlConf()
{
    this->firstLaunch = true;
    this->tcpPort = 65535; // Never used
    this->udpPort = PORT;
    this->udpBindPort = PORT_RESP;
    this->multicastIp = MULTICAST_ADDR;
    this->language = QLocale::system().name().section('_', 0, 0);
    this->controller = NULL;
}


