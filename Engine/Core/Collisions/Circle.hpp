#ifndef OPENGE_COLLISIONS_CIRCLE_H
#define OPENGE_COLLISIONS_CIRCLE_H

#include <luabind/luabind.hpp>
#include "Engine/Core/Math/Vector3.hpp"

class Circle
{
public:
    Circle(float x, float y, float radius) : offsetX(x), offsetY(y), radius(radius) {}
    virtual ~Circle() {}

    bool                    Collides(const Vector3& pos, const Circle& other, const Vector3& otherPos);

public:
    float                   radius;
    float                   offsetX;
    float                   offsetY;

};

#endif // OPENGE_COLLISIONS_CIRCLE_H
