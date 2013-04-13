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

#include "../../includes/xml/xml.h"

bool  Xml::exportConfig(XmlConf * pXmlConf,QString pFilename)
{
    file.setFileName(pFilename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Error while opening export file";
        return false;
    }
    QDomDocument doc;
    QDomElement configuration = doc.createElement("configuration");
    out.flush();
    out.reset ();
    out.setDevice(&file);
    doc.appendChild(configuration);

    QDomElement firstLaunch = doc.createElement("firstLaunch");
    configuration.appendChild(firstLaunch);
    QDomText firstLaunchText = doc.createTextNode(QString::number(pXmlConf->firstLaunch));
    firstLaunch.appendChild(firstLaunchText);

    QDomElement tcpPort = doc.createElement("tcpPort");
    configuration.appendChild(tcpPort);
    QDomText tcpPortText = doc.createTextNode(QString::number(pXmlConf->tcpPort));
    tcpPort.appendChild(tcpPortText);

    QDomElement udpPort = doc.createElement("udpPort");
    configuration.appendChild(udpPort);
    QDomText udpPortText = doc.createTextNode(QString::number(pXmlConf->udpPort));
    udpPort.appendChild(udpPortText);

    QDomElement udpBindPort = doc.createElement("udpBindPort");
    configuration.appendChild(udpBindPort);
    QDomText udpBindPortText = doc.createTextNode(QString::number(pXmlConf->udpBindPort));
    udpBindPort.appendChild(udpBindPortText);

    QDomElement multIp = doc.createElement("multicastIp");
    configuration.appendChild(multIp);
    QDomText multIpText = doc.createTextNode(pXmlConf->multicastIp);
    multIp.appendChild(multIpText);

    QDomElement language = doc.createElement("language");
    configuration.appendChild(language);
    QDomText languageText = doc.createTextNode(pXmlConf->language);
    language.appendChild(languageText);

    if(pXmlConf->controller != NULL)
    {
        QDomElement controller = doc.createElement("controller");
        configuration.appendChild(controller);

        QDomElement name = doc.createElement("name");
        controller.appendChild(name);
        QDomText nameText = doc.createTextNode(pXmlConf->controller->getName());
        name.appendChild(nameText);

        QDomElement port = doc.createElement("port");
        controller.appendChild(port);
        QDomText portText = doc.createTextNode(QString::number(pXmlConf->controller->getPort()));
        port.appendChild(portText);

        QDomElement ip = doc.createElement("ip");
        controller.appendChild(ip);
        QDomText ipText = doc.createTextNode(pXmlConf->controller->getIpAddr());
        ip.appendChild(ipText);
    }

    qDebug() << "createProcessingInstruction";
    QDomNode noeud = doc.createProcessingInstruction("xml","version=\"1.0\"");
    doc.insertBefore(noeud,doc.firstChild());
    doc.save(out,2);
    doc.clear();
    file.close();
    return true;
}

XmlConf*  Xml::importConfig(QString pFilename)
{
    XmlConf * xmlConf = new XmlConf();
    QDomDocument doc;
    file.setFileName(pFilename);
    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Error while opening import file";
        return xmlConf;
    }
    if (!doc.setContent(&file))
    {
        qDebug() << "Error while read file";
        file.close();
        return xmlConf;
    }

    //Root
    QDomElement root = doc.documentElement();
    if(root.tagName() !=  "configuration")
    {
        qDebug() <<  "Error, \"configuration\" tag expected";
        file.close();
        return xmlConf;
    }

    QDomNodeList confs = root.childNodes();
    unsigned int i = 0;



    QDomNode firstLaunchNode = confs.item(i++);
    QDomElement firstLaunchElem = firstLaunchNode.toElement();
    if(firstLaunchElem.tagName() != "firstLaunch")
    {
        qDebug() <<  "Error, \"firstLaunch\" tag expected";
        file.close();
        return xmlConf;
    }


    QString firstLaunchS = firstLaunchElem.text();
    bool res = true;
    int firstLaunch = firstLaunchS.toInt(&res);
    if(res == false)
    {
        qDebug() << "Error, integer expected";
        file.close();
        return xmlConf;
    }
    xmlConf->firstLaunch = firstLaunch;


    QDomNode tcpNode = confs.item(i++);
    QDomElement tcpElem = tcpNode.toElement();
    if(tcpElem.tagName() != "tcpPort")
    {
        qDebug() <<  "Error, \"tcpPort\" tag expected";
        file.close();
        return xmlConf;
    }


    QString tcpPortS = tcpElem.text();
    res = true;
    int tcpPort = tcpPortS.toInt(&res);
    if(res == false)
    {
        qDebug() << "Error, integer expected";
        file.close();
        return xmlConf;
    }
    xmlConf->tcpPort = tcpPort;

    QDomNode udpNode = confs.item(i++);
    QDomElement udpElem = udpNode.toElement();
    if(udpElem.tagName() != "udpPort")
    {
        qDebug() <<  "Error, \"udpPort\" tag expected";
        file.close();
        return xmlConf;
    }

    QString udpPortS = udpElem.text();
    int udpPort = udpPortS.toInt(&res);
    if(res == false)
    {
        qDebug() << "Error, integer expected";
        file.close();
        return xmlConf;
    }
    xmlConf->udpPort = udpPort;

    QDomNode udpBindNode = confs.item(i++);
    QDomElement udpBindElem = udpBindNode.toElement();
    if(udpBindElem.tagName() != "udpBindPort")
    {
        qDebug() <<  "Error, \"udpBindPort\" tag expected";
        file.close();
        return xmlConf;
    }

    QString udpBindPortS = udpBindElem.text();
    int udpBindPort = udpBindPortS.toInt(&res);
    if(res == false)
    {
        qDebug() << "Error, integer expected";
        file.close();
        return xmlConf;
    }
    xmlConf->udpBindPort = udpBindPort;

    QDomNode multicastNode = confs.item(i++);
    QDomElement multicastElem = multicastNode.toElement();
    if(multicastElem.tagName() != "multicastIp")
    {
        qDebug() <<  "Error, \"multicastIp\" tag expected";
        file.close();
        return xmlConf;
    }
    xmlConf->multicastIp = multicastElem.text();

    QDomNode languageNode = confs.item(i++);
    QDomElement languageElem = languageNode.toElement();
    if(languageElem.tagName() != "language")
    {
        qDebug() <<  "Error, \"language\" tag expected";
        file.close();
        return xmlConf;
    }
    xmlConf->language  = languageElem.text();

    QDomNode controllerNode = confs.item(i++);
    QDomElement controllerElem = controllerNode.toElement();
    if(controllerElem.tagName() != "controller")
    {
        qDebug() <<  "Error, \"controller\" tag expected";
        file.close();
        return xmlConf;
    }

    QDomNodeList controllers = controllerElem.childNodes();
    unsigned int j = 0;
    QDomNode nameNode = controllers.item(j++);
    QDomElement nameElem = nameNode.toElement();
    if(nameElem.tagName() != "name")
    {
        qDebug() <<  "Error, \"name\" tag expected";
        file.close();
        return xmlConf;
    }

    QDomNode portNode = controllers.item(j++);
    QDomElement portElem = portNode.toElement();
    if(portElem.tagName() != "port")
    {
        qDebug() <<  "Error, \"port\" tag expected";
        file.close();
        return xmlConf;
    }
    unsigned short controllerPort = portElem.text().toUShort(&res);
    if(res == false)
    {
        qDebug() << "Error, unsigned integer expected";
        file.close();
        return xmlConf;
    }
    QDomNode ipNode = controllers.item(j++);
    QDomElement ipElem = ipNode.toElement();
    if(ipElem.tagName() != "ip")
    {
        qDebug() <<  "Error, \"port\" tag expected";
        file.close();
        return xmlConf;
    }
    xmlConf->controller = new Controller(ipElem.text(),controllerPort,nameElem.text());

    file.close();
    return xmlConf;
}

bool Xml::exportRecords(QList<Record *> * pRecords, QString pFilename)
{
    file.setFileName(pFilename);
    if(!file.open(QFile::WriteOnly))
    {
        qDebug() << "Error while opening export file";
        return 1;
    }

    QDomDocument doc;
    QDomElement recordings = doc.createElement("recordings");
    out.flush();
    out.reset();
    out.setDevice(&file);
    doc.appendChild(recordings);

    for(int  i = 0 ; i < pRecords->count() ; i++)
    {
        Record * record = pRecords->at(i);
        if(addRecord(&doc,&recordings, record) == 1)
        {
            file.close();
            return 1;
        }
    }

    QDomNode noeud = doc.createProcessingInstruction("xml","version=\"1.0\"");
    doc.insertBefore(noeud,doc.firstChild());
    doc.save(out,2);
    doc.clear();
    file.close();
    return 0;
}

QList<Record *> * Xml::importRecord(QString pFilename)
{
    QList<Record *> * records = new QList<Record *>();
    QDomDocument doc;
    file.setFileName(pFilename);
    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Error while opening import file";
        return NULL;
    }
    if (!doc.setContent(&file))
    {
        qDebug() << "Error while read file";
        file.close();
        return NULL;
    }

    //Root
    QDomElement root = doc.documentElement();
    if(root.tagName() !=  "recordings")
    {
        qDebug() <<  "Error, \"recordings\" tag expected";
        file.close();
        return NULL;
    }

    QDomNodeList recordList = root.childNodes();
    for(unsigned int i = 0; i < recordList.length() ; i++)
    {
        QDomNode recordNode = recordList.item(i);
        QDomElement recordElem = recordNode.toElement();
        Record * record = this->getRecord(recordElem);
        if(record == NULL)
        {
            file.close();
            return NULL;
        }
        records->append(record);
    }
    file.close();
    return records;
}

Record * Xml::getRecord(QDomElement pRecord)
{
    QString name = pRecord.attribute("name");
    QDomNodeList elemRecordList = pRecord.childNodes();
    QDomNode orderNode = elemRecordList.item(0);
    QDomElement order = orderNode.toElement();
    if(order.tagName() != "order")
    {
        qDebug() <<  "Error, \"order\" tag expected";
        return NULL;
    }
    QString orderType = order.attribute("type");
    QString orderName = order.text();
    Command * command = new Command(orderName, (CommandType)orderType.toInt());

    QList<Gesture * > * gestures = new QList<Gesture * >();
    for(int i = 1; i < elemRecordList.count(); i++)
    {
        QDomNode movementNode = elemRecordList.item(i);
        QDomElement movement = movementNode.toElement();
        if(movement.tagName() != "movement")
        {
            qDebug() <<  "Error, \"movement\" tag expected";
            return NULL;
        }

        Gesture * gesture = getGesture(movement);
        if(gesture == NULL)
        {
            return NULL;
        }
        gestures->append(gesture);
    }
    return new Record(name, gestures, command);
}

bool Xml::addRecord(QDomDocument *doc, QDomElement * recordings, Record * pRecord)
{

    QDomElement recording = doc->createElement("recording");
    recording.setAttribute("name",pRecord->getName());
    recordings->appendChild(recording);
    // order
    Command *command = pRecord->getCommand();
    QDomElement order = doc->createElement("order");
    order.setAttribute("type",command->getType());
    recording.appendChild(order);
    QDomText orderText = doc->createTextNode(command->getDefinition());
    order.appendChild(orderText);

    // gesture
    if(pRecord->getGestures()->count() < 1)
    {
        qDebug() << "One gesture to export needed";
        return 1;
    }
    QDomElement movement = doc->createElement("movement");
    recording.appendChild(movement);
    for(int i = 0 ; i < pRecord->getGestures()->count() ; i++)
    {
        Gesture * gesture = pRecord->getGestures()->at(i);
        for(int i = 0 ; i < gesture->getFrames()->count() ; i++ )
        {
            SkeletonData *skeleton = gesture->getFrames()->at(i);
            this->addSkeleton(doc, &movement, skeleton);
        }
    }
    return 0;
}

Gesture * Xml::getGesture(QDomElement movement)
{
    QDomNodeList skeletonList = movement.childNodes();
    QList<SkeletonData *> *frames = new QList<SkeletonData *>();
    for(unsigned int i = 0; i < skeletonList.length() ; i++)
    {
        QDomNode skeletonNode = skeletonList.item(i);
        QDomElement skeleton = skeletonNode.toElement();
        unsigned long long timestamp = skeleton.attribute("timestamp").toLongLong();
        QList<Vector3> * joints = getJoint(skeleton);
        if(joints == NULL)
        {
            return NULL;
        }
        SkeletonData * skeletonData = new SkeletonData(joints, timestamp);
        frames->append(skeletonData);
    }

    Gesture * gesture = new Gesture(frames);
    return gesture;
}

void Xml::addSkeleton(QDomDocument *doc, QDomElement * pMovement, SkeletonData * pSkeleton)
{
    QDomElement skeleton = doc->createElement("skeleton");
    skeleton.setAttribute("timestamp",pSkeleton->getTimestamp());
    pMovement->appendChild(skeleton);
    QList<Vector3> *joints = pSkeleton->getJointures();

    for(int i = 0 ; i < joints->count(); i++)
    {
        Vector3 joint = joints->at(i);
        this->addJoint(doc, &skeleton, &joint, i);
    }
}

QList<Vector3> * Xml::getJoint(QDomElement pSkeleton)
{
    QList<Vector3> * joints = new QList<Vector3>();
    QMap<int,Vector3> * jointsMap = new QMap<int,Vector3>();
    QDomNodeList jointList = pSkeleton.childNodes();
    for(unsigned int i = 0; i < jointList.length() ; i++)
    {
        QDomNode jointNode = jointList.item(i);
        QDomElement joint = jointNode.toElement();
        if(joint.tagName() != "joint")
        {
            qDebug() <<  "Error, \"joint\" tag expected";
        }
        int nameJoint = joint.attribute("name").toInt();
        QDomNode coordinatesNode = joint.firstChild();
        QDomElement coordinates = coordinatesNode.toElement();
        if( coordinates.tagName() != "coordinates" )
        {
            qDebug() << "Error, \"coordinates\" tag expected";
            return NULL;
        }

        QDomNode xNode = coordinates.firstChild();
        QDomElement x = xNode.toElement();
        if(x.tagName() != "x")
        {
            qDebug()  << "Error, \"x\" tag expected" ;
            return NULL;
        }
        QDomNode yNode = x.nextSibling();
        QDomElement y = yNode.toElement();
        if(y.tagName() != "y")
        {
            qDebug()  << "Error, \"y\" tag expected" ;
            return NULL;
        }
        QDomNode zNode = y.nextSibling();
        QDomElement z = zNode.toElement();
        if(z.tagName() != "z")
        {
            qDebug()  << "Error, \"z\" tag expected";
            return NULL;
        }
        bool res = true;
        float xFloat = x.text().toFloat(&res);
        if(res == false)
        {
            return NULL;
        }
        float yFloat = y.text().toFloat(&res);
        if(res == false)
        {
            return NULL;
        }
        float zFloat = z.text().toFloat(&res);
        if(res == false)
        {
            return NULL;
        }
        Vector3 *vector3 = new Vector3(xFloat,yFloat,zFloat);
        jointsMap->insert(nameJoint, *vector3);

    }
    QList<int> keys = jointsMap->keys();
    qSort(keys);
    foreach(int key, keys)
    {
        joints->append(jointsMap->value(key));
    }

    return joints;
}

void Xml::addJoint(QDomDocument *doc,QDomElement *pSkeleton, Vector3 * pJoint, int position)
{
    QDomElement joint = doc->createElement("joint");
    joint.setAttribute("name",position);
    pSkeleton->appendChild(joint);
    QDomElement coordinates = doc->createElement("coordinates");
    joint.appendChild(coordinates);
    // x
    QString xString;
    xString.setNum(pJoint->x,'g',8);
    QDomElement x = doc->createElement("x");
    coordinates.appendChild(x);
    QDomText xText = doc->createTextNode(xString);
    x.appendChild(xText);
    // y
    QString yString;
    yString.setNum(pJoint->y,'g',8);
    QDomElement y = doc->createElement("y");
    coordinates.appendChild(y);
    QDomText yText = doc->createTextNode(yString);
    y.appendChild(yText);
    // z
    QString zString;
    zString.setNum(pJoint->z,'g',8);
    QDomElement z = doc->createElement("z");
    coordinates.appendChild(z);
    QDomText zText = doc->createTextNode(zString);
    z.appendChild(zText);
}
