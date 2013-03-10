/*!
 * \file math.h
 * \author Camille Darcy and Sylvain Fay-Chatelard
 * \brief Utility class containing mathematic formulas
 * \date 2013-02-14
 */
#ifndef MATH_H
#define MATH_H

#include "vector3.h"

/*!
 * \brief Utility class containing mathematic formulas
 */
class Math
{
public:

    /*!
     * \brief Sigmoid computation of a float
     * \param pInput the float to compute
     * \return the position of the float on the sigmoid curve
     */
    static float sigmoid(float pInput);

    /*!
     * \brief Computation of an angle between two Vectors
     * \param pFirst the first vector
     * \param pSecond the second vector
     * \return the value of the angle
     */
    static float calculateAngle (Vector3 pFirst, Vector3 pSecond);

    /*!
     * \brief Fast computation of a square root
     * \param x the number to compute the square root
     * \return the value of the parameters square root
     */
    static float inverseSqrtFast(float x);

    /*!
     * \brief Absolute value computation fo a float
     * \param pValue a number to compute absolute value
     * \return the absolute float value
     */
    static float abs(float pValue);


    /*!
     * \brief Sigmoid computation of a double
     * \param pInput the double to compute
     * \return the position of the double on the sigmoid curve
     */
    static double sigmoidD(double pInput);


    /*!
     * \brief Absolute value computation fo a double
     * \param pValue a number to compute absolute value
     * \return the absolute double value
     */
    static double absD(double pValue);

    /*!
     * \brief Returns the maximum value between two ints
     * \param pFirst first int
     * \param pSecond second int
     * \return the maximum of the two parameters, or the first if equality
     */
    static int max(int pFirst, int pSecond);
};

#endif // MATH_H
