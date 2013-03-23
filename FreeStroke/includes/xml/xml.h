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
#ifndef XML_H
#define XML_H

/*!
 * \file xml.h
 * \author Anthony Fourneau
 * \brief Export and import in file
 * \date 2013-02-12
 */

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtXml/QtXml>

#include "../../includes/common/gesture.h"
#include "../../includes/daolayer/record.h"
#include "xmlconf.h"

/*!
 * \class Xml
 * \brief The class manages operations of import export in file
 *
 */
class Xml
{
public :

    /*!
     * \brief export configuration in XMl file
     * \param XmlConf * the configuration of the application
     * \param filename
     * \return 0 in case of success or 1 in case of error
     */
    bool exportConfig(XmlConf *, QString);

    /*!
     * \brief import configuration of a XMl file
     * \param filename
     * \return XmlConf* corresponding to the file or NULL in case of error
     */
    XmlConf* importConfig(QString);

    /*!
     * \brief export list of records in XMl file
     * \param QList<Record *> * the list of records to export
     * \param filename
     * \return 0 in case of success or 1 in case of error
     */
    bool exportRecords(QList<Record *> *, QString);

    /*!
     * \brief import list of record of a XMl file
     * \param filename
     * \return QList<Record *>* corresponding to the list of record present on file or NULL in case of error
     */
    QList<Record *> * importRecord(QString);

private :

    /*!
     * \brief add a record on a DomDocument
     * \param the dom document
     * \param the root tag where the record will be added
     * \param the record to add
     * \return 0 in case of success or 1 in case of error
     *
     */
    bool addRecord(QDomDocument*, QDomElement *, Record *);

    /*!
     * \brief add a skeletonData on a DomDocument
     * \param the dom document
     * \param the root tag where the skeleton data will be added
     * \param the skeletonData to add
     */
    void addSkeleton(QDomDocument*, QDomElement *, SkeletonData *);

    /*!
     * \brief add a Vector3 on a DomDocument
     * \param the dom document
     * \param the root tag where the record will be added
     * \param the Vector3 to add
     * \param the number of the joint
     */
    void addJoint(QDomDocument*,QDomElement *, Vector3 *, int);

    /*!
     * \brief get a record from a QDomElement
     * \param a QDomElement to read
     * \return a Record on success or NULL on onther case
     */
    Record * getRecord(QDomElement);

    /*!
     * \brief get a Gesture from a QDomElement
     * \param a QDomElement to read
     * \return a Gesture on success or NULL on onther case
     */
    Gesture * getGesture(QDomElement);

    /*!
     * \brief get a list of Vector3 from a QDomElement
     * \param a QDomElement to read
     * \return a QList<Vector3> on success or NULL on onther case
     */
    QList<Vector3> * getJoint(QDomElement);

    QFile file; /*!< a instance of QFile for open and read/write, it must be close at the end*/
    QTextStream out; /*!< a stream for write on the document, it must be clear after used */
};
#endif // XML_H
