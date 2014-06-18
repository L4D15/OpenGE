#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Core/Math/Vector3.hpp"

namespace Systems
{

class Physics : public anax::System<Physics>
{
public:
    Physics();
    virtual ~Physics();

    void            Update() const;

    inline void     SetGravity(const Vector3 gravity) { this->gravity = gravity; }

protected:
    Vector3         gravity;
};
}

#endif // PHYSICS_HPP
