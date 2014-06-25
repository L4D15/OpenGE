#ifndef OPENGE_MATH_H
#define OPENGE_MATH_H

#include <cmath>
#include <luabind/luabind.hpp>

class Vector2;
class Vector3;
class Color;

class Math
{
public:
    typedef enum
    {
        Linear,
        EasyIn,
        EasyOut,
        EasyInEasyOut,
        Boomerang
    }InterpolationType;

public:
    Math();
    virtual ~Math();

static double               PI;

static float                InverseSquareRoot(float number);
static float                SquareRoot(float x);
static int                  Max(int a, int b);
static int                  Min(int a, int b);
static float                Max(float a, float b);
static float                Min(float a, float b);
static float                Normalize(float start, float end, float current);

static float                LinearFunction(float x);
static float                EasyInFunction(float x);
static float                EasyOutFunction(float x);
static float                EasyInEasyOutFunction(float x);
static float                BoomerangFunction(float x);


static float Interpolate(InterpolationType type, float start, float end, float time);
static Vector2 Interpolate(InterpolationType type, Vector2 start, Vector2 end, float time);
static Color Interpolate(InterpolationType type, Color start, Color end, float time);

};


#endif  // OPENGE_MATH_H
