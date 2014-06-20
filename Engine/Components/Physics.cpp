#include "Engine/Components/Physics.hpp"

using namespace Components;

Physics::Physics()
{

}

Physics::~Physics()
{

}

Physics::Physics(const Vector3& v, const Vector3& a,
        const float mass, const float linD, const float angD,
        const bool kinematic)
: velocity(v), aceleration(a), mass(mass), linearDrag(linD), angularDrag(angD), isKinematic(kinematic)
{

}

Physics::Physics(json_spirit::Value jsonString)
:   velocity(),
    aceleration(),
    mass(1.0f),
    linearDrag(0.0f),
    angularDrag(0.0f),
    isKinematic(false)
{
    /*
     * JSON TEMPLATE FOR PHYSICS COMPONENT
     * {
     *  "name": "Physics",
     *  "velocity":
     *  {
     *      "x": 0,
     *      "y": 0,
     *      "z": 0
     *  },
     *  "aceleration":
     *  {
     *      "x": 0,
     *      "y": 0,
     *      "z": 0
     *  },
     *  "mass": 1.0,
     *  "linear_drag": 1.0,
     *  "angular_drag": 1.0,
     *  "kinematic": false
     *
     * }
     */
     json_spirit::Value v, a;

    if (jsonString.contains("velocity"))
    {
        v = jsonString.getObject().at("velocity");
        velocity.x = v.getObject().at("x").getReal();
        velocity.y = v.getObject().at("y").getReal();
        velocity.z = v.getObject().at("z").getReal();
    }

    if (jsonString.contains("aceleration"))
    {
        a = jsonString.getObject().at("aceleration");

        aceleration.x = v.getObject().at("x").getReal();
        aceleration.y = v.getObject().at("y").getReal();
        aceleration.z = v.getObject().at("z").getReal();
    }

    if (jsonString.contains("mass"))
    {
        mass = jsonString.getObject().at("mass").getReal();
    }

    if (jsonString.contains("linear_drag"))
    {
        linearDrag = jsonString.getObject().at("linear_drag").getReal();
    }

    if (jsonString.contains("angular_drag"))
    {
        angularDrag = jsonString.getObject().at("angular_drag").getReal();
    }

    if (jsonString.contains("kinematic"))
    {
        isKinematic = jsonString.getObject().at("kinematic").getBool();
    }
}
