/*!
 * \file gesture.h
 * \author Guillaume Demurger
 * \brief Represents a basic gesture object
 * \date 2013-02-14
 */
#ifndef GESTURE_H
#define GESTURE_H

#include "skeletondata.h"

#include <QtCore/QString>

/*!
 * \brief Represents a basic gesture object
 * A gesture is composed by some skeleton frames and can be built from a file or a list of frames
 * It is basically a sequence of skeleton states / frames
 */
class Gesture
{
public:
    /*!
     * \brief Main constructor
     * \param pFrames frames representing the gesture
     */
    Gesture(QList<SkeletonData*> *pFrames);

    /*!
     * \brief getter for frames of the gesture
     * \return the frames composing the gesture
     */
    QList<SkeletonData*>* getFrames();

    /*!
     * \brief String representation of the gesture
     */
    QString toString();

    /*!
     * \brief Used to build a gesture from a file content
     * \param filename name of the file containing the sequence of frames
     * \return a pointer on the created gesture object
     */
    static Gesture* fromFile(QString filename);

private:
    QList<SkeletonData*> *frames; /*!< List of frames representing the gesture */
};

#endif // GESTURE_H
