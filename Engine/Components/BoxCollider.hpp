#ifndef OPENGE_COMPONENTS_COLLIDER_H
#define OPENGE_COMPONENTS_COLLIDER_H

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Core/Collisions/Box.hpp"

namespace Components
{

class BoxCollider : public anax::Component<BoxCollider>
{
public:
    BoxCollider()
    : box(0.0, 0.0, 0.0, 0.0)
    {

    }

    BoxCollider(float x, float y, float width, float height)
    : box(x, y, width, height)
    {

    }

    BoxCollider(json_spirit::Value jsonString);

    virtual ~BoxCollider()
    {

    }

public:
    Box                 box;

};

}

#endif // OPENGE_COMPONENTS_COLLIDER_H
