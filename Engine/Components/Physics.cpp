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

     v = jsonString.getObject().at("velocity");
     a = jsonString.getObject().at("aceleration");

     velocity.x = v.getObject().at("x").getReal();
     velocity.y = v.getObject().at("y").getReal();
     velocity.z = v.getObject().at("z").getReal();
     aceleration.x = v.getObject().at("x").getReal();
     aceleration.y = v.getObject().at("y").getReal();
     aceleration.z = v.getObject().at("z").getReal();

     mass = jsonString.getObject().at("mass").getReal();
     linearDrag = jsonString.getObject().at("linear_drag").getReal();
     angularDrag = jsonString.getObject().at("angular_drag").getReal();
     isKinematic = jsonString.getObject().at("kinematic").getBool();
}
