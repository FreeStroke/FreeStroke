/*!
 * \file playbuttonelement.h
 * \brief The PlayButtonElement class represent a custom play button.
 * \author Aurèle Lenfant
 * \date 2013-02-20
 */
#ifndef PLAYBUTTONELEMENT_H
#define PLAYBUTTONELEMENT_H

#include <QtGui/QAbstractButton>

#include "../element.h"

/*!
 * \brief The PlayButtonElement class represent a custom play button.
 */
class PlayButtonElement : public QAbstractButton, public Element
{
    Q_OBJECT
public:
    /*!
     * \brief the default PlayButtonElement constructor
     * \param parent the container QWidget parent
     */
    PlayButtonElement(QWidget *parent = 0);
private:
    /*!
     * \brief the icon of the PlayButtonElement while not selected
     */
    QPixmap *pixmap;
    /*!
     * \brief the icon of the PlayButtonElement while selected
     */
    QPixmap *pixmapSelected;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // PLAYBUTTONELEMENT_H
