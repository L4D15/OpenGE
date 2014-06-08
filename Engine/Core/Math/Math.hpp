#ifndef OPENGE_MATH_H
#define OPENGE_MATH_H

#include <cmath>

class Vector2;
class Vector3;
class Color;

namespace math
{

static double PI = atan(1) * 4;

float inverseSquareRoot(float number);
float squareRoot(float x);
int max(int a, int b);
int min(int a, int b);
float max(float a, float b);
float min(float a, float b);

float normalize(float start, float end, float current);

// ===========================================================================
// Interpolation
// ===========================================================================
// Interpolation functions
namespace interpolation
{
typedef enum
{
    Linear,
    EasyIn,
    EasyOut,
    EasyInEasyOut,
    Boomerang
}Type;

float linearFunction(float x);
float easyInFunction(float x);
float easyOutFunction(float x);
float easyInEasyOutFunction(float x);
float boomerangFunction(float x);

}

float interpolate(interpolation::Type type, float start, float end, float time);
Vector2 interpolate(interpolation::Type type, Vector2 start, Vector2 end, float time);
Color interpolate(interpolation::Type type, Color start, Color end, float time);

}

#endif  // OPENGE_MATH_H
