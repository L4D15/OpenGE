#ifndef OPENGE_SYSTEMS_COLLISIONS_H
#define OPENGE_SYSTEMS_COLLISIONS_H

#include "Engine/Libraries/Libraries.hpp"

class Collisions : public anax::System<Collisions>
{
public:
    Collisions();
    virtual ~Collisions();

    void                    Update() const;

};

#endif // OPENGE_SYSTEMS_COLLISIONS_H