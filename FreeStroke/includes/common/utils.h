/*!
 * \file utils.h
 * \author Sylvain Fay-Chatelard
 * \brief Utiliy class for freestroke application
 * \date 2013-02-12
 */
#ifndef UTILS_H
#define UTILS_H

#include <QtCore/QObject>
#include <QtGui/QFont>

/*!
 * \brief Utiliy class for freestroke application
 */
class Utils : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Gets the default font for freestroke
     * \return the default QFont object
     */
    static QFont getFont();

    /*!
     * \brief Gets the resources directory of freestroke
     * \return a path to the resources directory
     */
    static QString getResourcesDirectory();

    /*!
     * \brief Gets the database directory of freestroke
     * \return a path to the database directory
     */
    static QString getDatabaseDirectoryLocation();

    /*!
     * \brief Gets the location of freestroke database
     * \return a path to the freestroke database
     */
    static QString getDatabaseLocation();

    /*!
     * \brief Gets the configuration file path
     * \return a path to the configuration file
     */
    static QString getConfigLocation();


    /*!
     * \brief Gets the application root path of freestroke
     * \return a path to the application root directory of freestroke
     */
    static QString getApplicationDirectoryRoot();

    /*!
     * \brief This function does a malloc and check the result, if the malloc failed, the application
     * is killed with abort() because there is not enough memory.
     * \param size The size to allocate
     * \return The created pointer, the application can be killed
     */
    static void* secureMalloc(int size);

    /*!
     * \brief This function free a pointer
     * \param ptr The pointer to free
     */
    static void secureFree(void *ptr);
    
signals:
    
public slots:
    
};

#endif // UTILS_H
