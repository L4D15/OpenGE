#include "Engine/Core/Math/Math.hpp"
#include "Engine/Core/Math/Vector2.hpp"
#include "Engine/Core/Math/Vector3.hpp"
#include "Engine/Core/Color.hpp"
#include <cmath>
#include <iostream>
#include <luabind/scope.hpp>

double Math::PI = atan(1) * 4;

Math::Math()
{

}

Math::~Math()
{

}

/**
 Inverse Square root.
 * @param number    Number to calculate the inverse square root.
 * @return          Inverse square root of the number.
 */
float Math::InverseSquareRoot(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
    //  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
    return y;
}

/**
 Square root.
 @param x   Number to calculate the square root.
 @return    Square root of the number.
 */
float Math::SquareRoot(float x) {
    const float xhalf = 0.5f*x;

    union // get bits for floating value
    {
        float x;
        int i;
    } u;
    u.x = x;
    u.i = 0x5f3759df - (u.i >> 1);  // gives initial guess y0
    return x*u.x*(1.5f - xhalf*u.x*u.x);// Newton step, repeating increases accuracy
}

/**
 * @brief max
 * @param a
 * @param b
 * @return
 */
int Math::Max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

/**
 * @brief min
 * @param a
 * @param b
 * @return
 */
int Math::Min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

/**
 * @brief math::max
 * @param a
 * @param b
 * @return
 */
float Math::Max(float a, float b)
{
    if (a > b) {
        return a;
    }
    return b;
}

/**
 * @brief math::min
 * @param a
 * @param b
 * @return
 */
float Math::Min(float a, float b)
{
    if (a < b) {
        return a;
    }
    return b;
}

/**
 * @brief Math::Normalize
 * @param start
 * @param end
 * @param current
 * @return
 */
float Math::Normalize(float start, float end, float current)
{
    return (current - start) / (end - start);
}

// ===========================================================================
// Interpolation
// ===========================================================================
/**
 * @brief Math::Interpolate
 * @param type
 * @param start
 * @param end
 * @param current   Normalized time (commonly currentTime/finalTime)
 * @return
 */
float Math::Interpolate(InterpolationType type, float start, float end, float time)
{
    if (time > 1.0f)
    {
        time = 1.0f;
    }

    if (time < 0.0f)
    {
        time = 0.0f;
    }

    switch (type) {
    case Linear:
        return (start + (end - start) * LinearFunction(time));
        break;

    case EasyIn:
        return (start + (end - start) * EasyInFunction(time));
        break;

    case EasyOut:
        return (start + (end - start) * EasyOutFunction(time));
        break;

    case EasyInEasyOut:
        return (start + (end - start) * EasyInEasyOutFunction(time));
        break;

    case Boomerang:
        return (start + (end - start) * BoomerangFunction(time));
        break;

    default:
        return 0.0f;
        break;
    }
}

float Math::LinearFunction(float x)
{
    return x;
}

float Math::EasyInFunction(float x)
{
    return x * x;
}

float Math::EasyOutFunction(float x)
{
    return sin(x * Math::PI / 2.0f);
}

float Math::EasyInEasyOutFunction(float x)
{
    return (x * x) / ((x *x) + ((1-x) * (1-x)));
}

float Math::BoomerangFunction(float x)
{
    return (sin(x * Math::PI));
}

/**
 * @brief Math::Interpolate
 * @param type
 * @param start
 * @param end
 * @param time
 * @return
 */
Vector2 Math::Interpolate(InterpolationType type, Vector2 start, Vector2 end, float time)
{
    float x;
    float y;

    x = Interpolate(type, start.x, end.x, time);
    y = Interpolate(type, start.y, end.y, time);

    return Vector2(x, y);
}

/**
 * @brief Math::Interpolate
 * @param type
 * @param start
 * @param end
 * @param time
 * @return
 */
Color Math::Interpolate(InterpolationType type, Color start, Color end, float time)
{
    float red;
    float green;
    float blue;
    float alpha;

    red = Interpolate(type, start.GetRed(), end.GetRed(), time);
    green = Interpolate(type, start.GetGreen(), end.GetGreen(), time);
    blue = Interpolate(type, start.GetBlue(), end.GetBlue(), time);
    alpha = Interpolate(type, start.GetAlpha(), end.GetAlpha(), time);

    return Color(red, green, blue, alpha);
}

using namespace luabind;

luabind::scope Math::RegisterForScripting()
{
    return
            class_<Math>("Math")
                .scope
                [
                    def("SquareRoot", &Math::SquareRoot),
                    def("InverseSquareRoot", &Math::InverseSquareRoot),
                    def("Normalize", &Math::Normalize)
                ];
}
