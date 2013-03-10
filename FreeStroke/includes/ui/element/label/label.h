/*!
 * \file label.h
 * \brief The Label class is a QLabel with a custom skin
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef LABEL_H
#define LABEL_H

#include <QtGui/QLabel>

#include "../element.h"

/*!
 * \brief The Label class is a QLabel with a custom skin
 */
class Label : public QLabel, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief default Label constructor
     * \param pText the desired text of the Label
     * \param parent the container QWidget parent
     */
    Label(QString pText, QWidget *parent = 0);
    /*!
     * \brief a Label constructor
     * \param pText the desired text of the Label
     * \param pBackground the desired background color of the Label
     * \param parent the container QWidget parent
     */
    Label(QString pText, QColor pBackground, QWidget *parent = 0);
    /*!
     * \brief set the text color of the Label
     * \param pColor the desired color
     */
    void setTextColor(QColor pColor);

    /*!
     * \brief change the size of the font of this Label
     * \param pSize the desired size
     */
    void changeFontSize(int pSize);
    /*!
     * \brief setPaintShadow defines if the shadow of the Label should be painted or not
     * \param pPaintShadow boolean defining if the shadow of the Label should be painted or not
     */
    void setPaintShadow(bool pPaintShadow);
private:
    /*!
     * \brief the background color of the Label
     */
    QColor  backgroundColor;
    /*!
     * \brief the text color of the Label
     */
    QColor  textColor;

    /*!
     * \brief the color of the shadow
     */
    QColor shadowColor;

    /*!
     * \brief paintShadow defines if the shadow of the Label should be painted or not
     */
    bool paintShadow;

protected:
    void paintEvent(QPaintEvent *);
    
};

#endif // LABEL_H
