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
#ifndef FEATURE_H
#define FEATURE_H

#include "../data/inputgesture.h"

#include <QtCore/QList>
#include <QtCore/QString>

class Feature
{
public:
    virtual void train(QList<InputGesture> pStates){Q_UNUSED(pStates);}
    virtual void saveModel(QString pFilename){Q_UNUSED(pFilename);}
    virtual void loadModel(QString pFilename){Q_UNUSED(pFilename);}
};

#endif // FEATURE_H
