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
 * \file keylistener.h
 * \brief The KeyListener class represent a TextField which listen to Key press and save only one Key and modifiers (shift,
 * ctrl, meta, alt, altgr)
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef KEYLISTENERELEMENT_H
#define KEYLISTENERELEMENT_H

#include "../element.h"

/*!
 * \brief The Key class represents the visualisation of a key in the KeyListener
 */
class Key : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Key the default Key constructor
     * \param pKey the QString representing the key
     * \param parent the parent of the Key
     */
    Key(QString pKey, QWidget *parent = 0);
    /*!
     * \brief getKey returns the Key in a String representation
     * \return the Key in a String representation
     */
    QString getKey();

protected:
    void paintEvent(QPaintEvent *e);

private:
    /*!
     * \brief the Key in a String representation
     */
    QString key;
};

/*!
 * \brief The KeyListener class represent a TextField which listen to key press and save only one key and modifiers (shift,
 * ctrl, meta, alt, altgr)
 */
class KeyListener : public QWidget, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief KeyListener the default contructor
     * \param parent the parent of the KeyListener
     */
    KeyListener(QWidget *parent = 0);
    /*!
     * \brief getKeys returns the Keys of the KeyListener in a QString representation
     * \return the Keys of the KeyListener in a QString representation
     */
    QString getKeys();
    /*!
     * \brief setKeys set the Keys of the the KeyListener in a QString representation
     * \param pKeys the Keys to set
     */
    void setKeys(QString pKeys);

    void keyPressEvent(QKeyEvent *e);
protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void focusOutEvent(QFocusEvent *e);
    void focusInEvent(QFocusEvent *e);

private:
    /*!
     * \brief keys the QList of Keys in the KeyListener
     */
    QList<Key*> *keys;
    /*!
     * \brief oldKeys the QList of Keys which were in the KeyListener. Used to know if the keys has changed
     */
    QList<Key*> *oldKeys;
    /*!
     * \brief clearKeys clear the Keys of the KeyListener
     */
    void clearKeys();

signals:
    /*!
     * \brief keysChanged is the signal sent when the Keys in the KeyListener have changed
     */
    void keysChanged();
};

#endif // KEYLISTENERELEMENT_H
