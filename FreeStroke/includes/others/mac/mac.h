/*!
 * \file mac.h
 * \brief Contains methods for generating key events on MacOSX systems
 * \author Sylvain Fay-Chatelard
 * \date 2013-02-20
 */
#ifndef MAC_H
#define MAC_H

#include <QtCore/QObject>
#include <QtGui/QWidget>

class Mac : public QObject
{
	Q_OBJECT
public:
    Mac(QWidget* w = 0);

    /*!
     * \brief Dislays a notification in MacOSX environment
     * \param pTitle title of the popup
     * \param pMessage message displayed
     */
    void showNotification(char *pTitle, char *pMessage);

    /*!
     * \brief Converts a Qt keycode to MacOSX system keycode
     * \param keyCode QT keycode (Qt::Key)
     * \return the native MacOSX keycode
     */
    static int convertToCGKeyCode(short keyCode);

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

#endif
