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
/*!
 * \file parameters.h
 * \brief The ParametersView class hold all the component of the parameters view of the application. It display the
 * settings of FreeStroke.
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */
#ifndef PARAMETERSVIEW_H
#define PARAMETERSVIEW_H

#include <QtGui/QWidget>

/*!
 * \brief The ParametersView class hold all the component of the parameters view of the application. It display the
 * settings of FreeStroke.
 */
class ParametersView : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief default ParametersView constructor
     * \param parent the container QWidget parent
     */
    ParametersView(QWidget *parent = 0);
    /*!
     * \brief checkController check if a Controller is present in the XMLConfiguration try to connect to it if so, else
     * show a Stepper to add a Controller.
     */
    void checkController();
    /*!
     * \brief checkFirstLaunch check in the XMLConfiguration if this is the first launch of the application and show the
     * tutorial if so
     */
    void checkFirstLaunch();

protected:
    void paintEvent(QPaintEvent *);

private:
    /*!
     * \brief isFirstLaunch boolean defining if this is the first launch or not.
     */
    bool isFirstLaunch;

private slots:
    /*!
     * \brief launchTutorial slot is called if this is the first launch of the application and launch the tutorial Stepper.
     */
    void launchTutorial();
    /*!
     * \brief discoverController slot is called when there are no Controller to connect to, it discover available Controller
     * in a Stepper and allow to connect to one.
     */
    void discoverController();
    /*!
     * \brief changeUDPPort slot is called when the UDP port is changed. It changes the UDP port in the XMLConf and in the
     * Communication
     * \param pPort the desired port
     */
    void changeUDPPort(QString pPort);
    /*!
     * \brief changeUDPPortBind slot is called when the UDP bind port is changed. It changes the UDP bind port in the XMLConf
     * and in the Communication
     * \param pBindPort the desired port
     */
    void changeUDPPortBind(QString pBindPort);
    /*!
     * \brief changeTCPPort slot is called when the TCP port is changed. It changes the TCP port in the XMLConf and in the
     * Communication
     * \param pPort the desired port
     */
    void changeTCPPort(QString pPort);
    /*!
     * \brief changeLanguage slot is called when the language is changed. It changes the language in the XMLConf and ask to restart
     * the application.
     * \param pLanguage the desired language
     */
    void changeLanguage(QString pLanguage);
};

#endif // PARAMETERSVIEW_H
