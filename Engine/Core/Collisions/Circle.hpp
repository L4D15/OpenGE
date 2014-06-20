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

    static luabind::scope   RegisterForScripting()
    {
        return
            luabind::class_<Circle>("Circle")
                .def(luabind::constructor<float, float, float>())
                .def("Collides", &Circle::Collides)
                .def_readwrite("radius", &Circle::radius)
                .def_readwrite("offsetX", &Circle::offsetX)
                .def_readwrite("offsetY", &Circle::offsetY)
            ;
    }

public:
    float                   radius;
    float                   offsetX;
    float                   offsetY;

};

#endif // OPENGE_COLLISIONS_CIRCLE_H