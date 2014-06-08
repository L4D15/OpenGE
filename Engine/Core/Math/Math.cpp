#include "Engine/Core/Math/Math.hpp"
#include "Engine/Core/Math/Vector2.hpp"
#include "Engine/Core/Math/Vector3.hpp"
#include "Engine/Core/Color.hpp"
#include <cmath>
#include <iostream>

/**
 Inverse Square root.
 * @param number    Number to calculate the inverse square root.
 * @return          Inverse square root of the number.
 */
float math::inverseSquareRoot(float number)
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
float math::squareRoot(float x) {
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
int math::max(int a, int b) {
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
int math::min(int a, int b) {
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
float math::max(float a, float b)
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
float math::min(float a, float b)
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
float math::normalize(float start, float end, float current)
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
float math::interpolate(interpolation::Type type, float start, float end, float time)
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
    case interpolation::Linear:
        return (start + (end - start) * interpolation::linearFunction(time));
        break;

    case interpolation::EasyIn:
        return (start + (end - start) * interpolation::easyInFunction(time));
        break;

    case interpolation::EasyOut:
        return (start + (end - start) * interpolation::easyOutFunction(time));
        break;

    case interpolation::EasyInEasyOut:
        return (start + (end - start) * interpolation::easyInEasyOutFunction(time));
        break;

    case interpolation::Boomerang:
        return (start + (end - start) * interpolation::boomerangFunction(time));
        break;

    default:
        return 0.0f;
        break;
    }
}

float math::interpolation::linearFunction(float x)
{
    return x;
}

float math::interpolation::easyInFunction(float x)
{
    return x * x;
}

float math::interpolation::easyOutFunction(float x)
{
    return sin(x * math::PI / 2.0f);
}

float math::interpolation::easyInEasyOutFunction(float x)
{
    return (x * x) / ((x *x) + ((1-x) * (1-x)));
}

float math::interpolation::boomerangFunction(float x)
{
    return (sin(x * math::PI));
}

/**
 * @brief Math::Interpolate
 * @param type
 * @param start
 * @param end
 * @param time
 * @return
 */
Vector2 math::interpolate(interpolation::Type type, Vector2 start, Vector2 end, float time)
{
    float x;
    float y;

    x = interpolate(type, start.x, end.x, time);
    y = interpolate(type, start.y, end.y, time);

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
Color math::interpolate(interpolation::Type type, Color start, Color end, float time)
{
    float red;
    float green;
    float blue;
    float alpha;

    red = interpolate(type, start.GetRed(), end.GetRed(), time);
    green = interpolate(type, start.GetGreen(), end.GetGreen(), time);
    blue = interpolate(type, start.GetBlue(), end.GetBlue(), time);
    alpha = interpolate(type, start.GetAlpha(), end.GetAlpha(), time);

    return Color(red, green, blue, alpha);
}
