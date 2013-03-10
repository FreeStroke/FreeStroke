/*!
 * \file windows.h
 * \brief Contains methods for generating key events on Windows 7 system
 * \author Anthony Fourneau
 * \date 2013-02-20
 */
#ifndef WINDOWS_H
#define WINDOWS_H

#include <QtCore/QObject>
#include <QtGui/QWidget>

class Windows : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief main constructor
     * \param w
     */
    Windows(QWidget* w = 0);

    /*!
     * \brief Simulates a key event and sends it to the system (on linux distributions only)
     * \param keyCode native code of the key to generate
     * \param shiftModifier modifier shift key
     * \param ctrlModifier modifier ctrl key
     * \param optionModifier modifier optn key
     * \param cmdModifier modifier cmd key
     */
    void static generateKeyEvent(unsigned short keyCode, bool shiftModifier, bool ctrlModifier, bool metaModifier, bool altModifier, bool altGrModifier);
};

#endif // WINDOWS_H
