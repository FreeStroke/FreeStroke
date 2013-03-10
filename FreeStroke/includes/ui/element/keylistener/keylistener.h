/*!
 * \file keylistener.h
 * \brief The KeyListener class represent a TextField which listen to Key press and save only one Key and modifiers (shift,
 * ctrl, meta, alt, altgr)
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef KEYLISTENERELEMENT_H
#define KEYLISTENERELEMENT_H

#include <QtCore/QString>
#include <QtGui/QLineEdit>

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
