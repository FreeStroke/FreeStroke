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
 * \file glview.h
 * \brief The GlView class represent the view of a gesture in OpenGL
 * \author Aurèle Lenfant
 * \date 2013-02-20
*/
#ifndef GLVIEW_H
#define GLVIEW_H

#include "openglview.h"

#include "../../common/gesture.h"

/*!
 * \brief The GlView class represent the view of a gesture in OpenGL
 */
class GlView : public OpenGlView
{
    Q_OBJECT
    
public:

    /*!
     * \brief The GLViewType enum determined the size of the GlView
     */
    enum GLViewType{
        SMALL,
        BIG
    };

    /*!
     * \brief default GlView constructor
     * \param parent the container QWidget parent
     * \param pType the type of the GlView
     */
    GlView(QWidget *parent = 0, GLViewType pType = BIG);
    /*!
     * \brief start the animation of the GlView
     */
    void startAnimating();
    /*!
     * \brief pause the animation of the GlView
     */
    void pauseAnimating();
    /*!
     * \brief pause the rotation of the GlView
     */
    void pauseRotation();
    /*!
     * \brief stop the animation of the GlView
     */
    void stopAnimating();
    /*!
     * \brief return if the animation of the GlView is currently running
     */
    bool isAnimating();
    /*!
     * \brief defines whether or not the GlView is animated on mouse hover
     * \param pAnimate defines whether or not the GlView is animated on mouse hover
     */
    void animateOnMouseEnter(bool pAnimate);
    /*!
     * \brief set the Gesture to represent in the GlView
     * \param pGesture the Gesture to represent
     */
    void setGesture(Gesture *pGesture);
    /*!
     * \brief set the next skeleton to represent in the GlView
     * \param pSkeleton the next skeleton to represent in the GlView
     */
    void nextSkeleton(SkeletonData *pSkeleton);

protected:
    void initializeGL();
    void resizeGL(int pWidth, int pHeight);
    void paintGL();
    void update();

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    /*!
     * \brief change the timer state
     */
    void changeTimerState();

    /*!
     * \brief the type of the GlView
     */
    GLViewType  type;

    /*!
     * \brief the angle in x
     */
    float       xAngle;
    /*!
     * \brief the last position of the mouse. Used to rotate the GlView
     */
    QPoint      lastPos;
    /*!
     * \brief the index of the gesture to represent.
     */
    int         gestureIndex;
    /*!
     * \brief defines whether or not the GlView is animated
     */
    bool        animated;
    /*!
     * \brief defines whether or not the GlView is animated on mouse hover
     */
    bool        animateOnMouseHover;
    /*!
     * \brief defines whether or not the GlView rotate
     */
    bool        rotatePause;
    /*!
     * \brief defines whether or not the GlView rotate can be activated on mouse press
     */
    bool        lockRotation;

    /*!
     * \brief The Gesture to represent in the GlView
     */
    Gesture     *gesture;
    /*!
     * \brief the SkeletonData to represent in the GlView
     */
    SkeletonData*skeleton;

public slots:
#ifdef Q_OS_MAC // This method is a hack because on Mac the event is not organize
    /*!
     * \brief This method is a hack because on Mac OS the event is not organize
     */
    void hackEnterEvent();
#endif
    void skeletonDataReceived(QString pData);
};

#endif // GLVIEW_H
