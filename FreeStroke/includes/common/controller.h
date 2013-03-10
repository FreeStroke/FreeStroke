/*!
 * \file controller.h
 * \author Adrien Madouasse
 * \brief Describe a controller
 * \date 2013-02-14
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtCore/QDebug>
#include <QtCore/QObject>

/*!
 * \class Controller
 * \brief The Controller class contains information of a controller
 */
class Controller : public QObject
{
    Q_OBJECT

public :
    /*!
     * \brief The constructor, initialize attributes
     * \param pIpAddr The IP address of the controller
     * \param pPort The TCP port of the controller
     * \param pName The name of the controller
     */
    Controller(QString pIpAddr, unsigned short pPort, QString pName);

    /*!
     * \brief Retrieve the IP address of the controller
     * \return The IP addres
     */
    QString getIpAddr();

    /*!
     * \brief Retrieve the TCP port of the controller
     * \return The TCP port
     */
    unsigned short getPort();

    /*!
     * \brief Retrieve the name of the controller
     * \return The name
     */
    QString getName();

private :
    /*!< The IP address of the controller */
    QString ipAddr;
    /*!< The TCP port of the controller */
    unsigned short port;
    /*!< The name of the controller */
    QString name;
};

#endif // CONTROLLER_H
