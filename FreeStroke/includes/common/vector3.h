/*!
 * \file vector3.h
 * \author Camille Darcy
 * \brief Contains Vector3 object (x, y, z) representing a body joint in freestroke context
 * \date 2013-02-14
 */
#ifndef VECTOR3_H
#define VECTOR3_H

/*!
 * \brief Vector3 class (x, y, z) representing a body joint in freestroke context
 */
class Vector3
{

public:
    /*!
     * \brief Main constructor
     * \param pX X axis of the vector
     * \param pY Y axis of the vector
     * \param pZ Z axis of the vector
     */
    Vector3(float pX = 0, float pY  = 0, float pZ = 0);

    /*!
     * \brief Gets the length (magnitude) of the vector
     * \return a float of the vector's magnitude
     */
    float length();

    /*!
     * \brief Gets a component of the vector
     * \param pComp component to get (x=0, y=1, z=else)
     * \return the vector's component specified by the parameter
     */
    float comp(int pComp);

    /*!
     * \brief Scales the Vector3 to approximately unit length
     */
    void normalizeFast();

    /*!
     * \brief Gets an approximation of the vector length (magnitude).
     * \return a float of the vector's magnitude
     */
    float lengthFast();

    /*!
     * \brief Calculate the dot (scalar) product of two vectors.
     * \param pLeft first vector to compute
     * \param pRight second vector to compute
     * \return the scalar product of the two vectors
     */
    static float dot(Vector3 pLeft, Vector3 pRight);

    /*!
     * \brief Adds the two vectors passed in parameter
     * \param pLeft first vector to compute
     * \param pRight second vector to compute
     * \return the addition of the two vectors
     */
    static Vector3 add(Vector3 pLeft, Vector3 pRight);


    /*!
     * \brief Substracts the two vectors passed in parameter
     * \param pLeft first vector to compute
     * \param pRight second vector to compute
     * \return the substraction of the two vectors
     */
    static Vector3 substract(Vector3 pLeft, Vector3 pRight);


    /*!
     * \brief Divides the two vectors passed in parameter
     * \param pLeft first vector to compute
     * \param pRight second vector to compute
     * \return the division of the two vectors
     */
    static Vector3 divide(Vector3 pLeft, float pScale);

    /*!
     * \brief Gets a zero length Vector
     * \return a zero length Vector
     */
    static Vector3 zero()
    {
        return Vector3(0, 0, 0);
    }

    /*!
     * \brief Defines an instance with all components set to 1
     * \return the vector with all components set to 1
     */
    static Vector3 one()
    {
        return Vector3(1, 1, 1);
    }

    /*!
     * \brief Defines a unit-length Vector3 that points towards the X-axis
     * \return the vector created
     */
    static Vector3 unitX()
    {
        return Vector3(1, 0, 0);
    }


    /*!
     * \brief Defines a unit-length Vector3 that points towards the Y-axis
     * \return the vector created
     */
    static Vector3 unitY()
    {
        return Vector3(0, 1, 0);
    }


    /*!
     * \brief Defines a unit-length Vector3 that points towards the Z-axis
     * \return the vector created
     */
    static Vector3 unitZ()
    {
        return Vector3(0, 0, 1);
    }

    float x; /*!< x axis of the vector */
    float y; /*!< y axis of the vector */
    float z; /*!< z axis of the vector */
};

#endif // VECTOR3_H
