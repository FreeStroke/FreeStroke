#ifndef COMMAND_H
#define COMMAND_H

/*!
 * \file command.h
 * \author Anthony Fourneau
 * \brief Representation of a command
 * \date 2013-02-12
 */

#include "commandtype.h"
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QHash>

/*!
 * \class Command
 * \brief The class is the representation of a command
 *
 */
class Command
{
public:
    /*!
     * \brief constructor of Command
     * \param The definition of the command : it can be keys combinaison or a script with arguments
     * \param The type of the command \see CommandType
     */
    Command(QString, CommandType);

    /*!
     * \brief get the definition of the command
     * \return the definition of the command :  it can be keys combinaison or a script with arguments
     */
    QString getDefinition();

    /*!
     * \brief get the type of the command
     * \return the type of the command \see CommandType
     */
    CommandType getType();

    /*!
     * \brief execute the command declare in the definition
     */
    void executeCommand();

    /*!
     * \brief This method construct a map corresponding to a special key and his value according to the system
     * \return a map corresponding to a special key and his value according to the system
     */
    static QHash<QString, int> specialKeysMap();
private:
    QString definition; /*!< The definition of the command */
    CommandType type; /*!< The type of the command */
};

#endif // COMMAND_H
