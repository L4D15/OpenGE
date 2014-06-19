#ifndef OPENGE_PHYSICS_H
#define OPENGE_PHYSICS_H

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Core/Math/Vector3.hpp"

namespace Components
{

class Physics : public anax::Component<Physics>
{
public:
	Physics();
	Physics(const Vector3& v,
			const Vector3& a,
			const float mass,
			const float linD,
			const float angD,
			const bool kinematic);
	Physics(json_spirit::Value jsonString);
	virtual ~Physics();

    void                    AddForce(const Vector3& force) { velocity = velocity + force; }
    void                    AddForce(const float x, const float y, const float z = 0) { velocity = velocity + Vector3(x,y,z); }
    void                    AddTorque(const Vector3& force) { torque = torque + force; }
    void                    AddTorque(const float x, const float y, const float z = 0) { torque = torque + Vector3(x,y,z); }

    static luabind::scope   RegisterForScripting()
    {
        return
                luabind::class_<Physics>("Physics")
                    .def(luabind::constructor<>())
                    .def(luabind::constructor<Vector3, Vector3, float, float, float, bool>())
                    .def("AddForce", (void (Physics::*) (float, float, float)) &Physics::AddForce)
                    .def("AddTorque", (void (Physics::*) (float, float, float)) &Physics::AddTorque)
                    .def_readwrite("velocity", &Physics::velocity)
                    .def_readwrite("aceleration", &Physics::aceleration)
                    .def_readwrite("torque", &Physics::torque)
                    .def_readwrite("mass", &Physics::mass)
                    .def_readwrite("linearDrag", &Physics::linearDrag)
                    .def_readwrite("angularDrag", &Physics::angularDrag)
                    .def_readwrite("isKinematic", &Physics::isKinematic)
                ;
    }

public:
    Vector3                 velocity;
    Vector3                 aceleration;
    Vector3                 torque;
    float                   mass;
    float                   linearDrag;
    float                   angularDrag;
    bool                    isKinematic;

};
}

#endif // OPENGE_PHYSICS_H
