#include "../../includes/common/controller.h"

/*!
 * \file controller.cpp
 * \author Adrien Madouasse
 * \brief Description of a controller
 * \date 2013-02-13
 */
#include <QtCore/QString>

Controller::Controller(QString pIpAddr, unsigned short pPort, QString pName)
{
    this->ipAddr = pIpAddr;
    this->port = pPort;
    this->name = pName;
}

QString Controller::getIpAddr()
{
    return this->ipAddr;
}

unsigned short Controller::getPort()
{
    return this->port;
}

QString Controller::getName()
{
    return this->name;
}
