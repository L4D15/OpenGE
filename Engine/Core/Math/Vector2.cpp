#include "Engine/Core/Math/Vector2.hpp"
#include <sstream>
#include "Engine/Core/Math/Math.hpp"
#include "Engine/Core/Math/Vector3.hpp"

/**
 Default constructor. Coordinates are set to 0.
 */
Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

/**

 @param x     X coordinate.
 @param y     Y coordinate.
 */
Vector2::Vector2(float x, float y)
: x(x), y(y)
{

}

/**
 Copy constructor.
 @param orig  Vector to copy.
 */
Vector2::Vector2(const Vector2& orig)
{
    x = orig.x;
    y = orig.y;
}

/**
 Destructor.
 */
Vector2::~Vector2()
{

}

/**
 Assignment operator.
 @param vector  Vector to copy values from.
 @return        Final vector.
 */
Vector2& Vector2::operator =(const Vector2& vector)
{
    x = vector.x;
    y = vector.y;
    return *this;
}

/**
 Sum operator.
 @param vector  Vector to sum with this one.
 @return        Final vector.
 */
Vector2 Vector2::operator +(const Vector2& vector)
{
    return Vector2(x + vector.x, y + vector.y);
}

/**
 Resizes vector by a factor.
 @param f   Resize factor.
 @return    Vector resized.
 */
Vector2 Vector2::operator *(float f)
{
    return Vector2(x * f,y * f);
}

/**
 Subtraction operator.
 @param vector  Vector to subtrate from.
 @return        Final vector.
 */
Vector2 Vector2::operator -(const Vector2& vector)
{
    return Vector2(x - vector.x, y - vector.y);
}

/**
 Comparison operator.
 @param vector  Vector to compare with.
 @return        true if the vector aren't equal, false otherwise.
 */
bool Vector2::operator !=(const Vector2 &vector)
{
    return x - vector.x != 0.0f || y - vector.y != 0.0f;
}

/**
 Comparison operator.
 @param vector  Vector to compare with.
 @return        true if they are equal, false otherwise.
 */
bool Vector2::operator ==(const Vector2 &vector)
{
    return x - vector.x == 0.0f && y - vector.y == 0.0f;
}

/**
 Perform the dot product of two vectors.
 @param vector  The other vector to operate with.
 @return        Value resulting of the operation.
 */
float Vector2::DotProduct(const Vector2 &vector)
{
    float result = 0.0;

    result += this->x * vector.x;
    result += this->y * vector.y;

    return result;
}

Vector2 Vector2::operator *(const Vector2& vector)
{
    return Vector2(this->x + vector.x, this->y + vector.y);
}

/**
 Length of the vector (without applying the square root to the result).
 @return    Quadratic length.
 */
float Vector2::LengthQuadratic()
{
    return (x * x + y * y);
}

/**
 Length fo the vector.
 @return    Length.
 */

float Vector2::Length()
{
    return math::squareRoot(x * x + y * y);
}

/**
 Quadratic distance to other vector.
 @param vector    The other vector.
 @return          Quadratic distance.
 */
float Vector2::DistanceQuadratic(const Vector2& vector)
{
    float Ax,Ay;

    Ax = x - vector.x;
    Ay = y - vector.y;

    return (Ax*Ax + Ay*Ay);
}

/**
 Distance to other vector.
 @param vector      The other vector.
 @return            Distante to the other vector.
 */
float Vector2::Distance(const Vector2& vector)
{
    float Ax,Ay;

    Ax = x - vector.x;
    Ay = y - vector.y;

    return math::squareRoot(Ax*Ax + Ay*Ay);
}

/**
 Normalizes the vector to values between 0 and 1.
 */
Vector2 Vector2::Normalized()
{
    Vector2 normalized;
    float lengthsq = (x * x + y * y);

    if(lengthsq == 0)
    {
        normalized.x = 0.0f;
        normalized.y = 0.0f;
        return normalized;
    }

    float recip = math::inverseSquareRoot(lengthsq);
    normalized.x *= recip;
    normalized.y *= recip;

    return normalized;
}

Vector3 Vector2::ToVector3D()
{
    return Vector3(this->x, this->y, 0.0f);
}

/**
 Format the values of the vector to represent it as a string.
 @return    String with the forma (x,y).
 */
std::string Vector2::ToString()
{
    std::stringstream str;

    str << "(" << x << "," << y << ")";

    return str.str();
}
