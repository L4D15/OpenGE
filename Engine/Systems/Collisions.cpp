#include "Engine/Systems/Collisions.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Components/BoxCollider.hpp"
#include "Engine/Components/Script.hpp"

Collisions::Collisions()
: Base(anax::ComponentFilter().requires<Components::Transform, Components::BoxCollider>())
{
    
}

Collisions::~Collisions()
{

}

void Collisions::Update() const
{
    auto entities = getEntities();
    for (auto& entity : entities)
    {
        if (entity.hasComponent<Components::Script>() == true)
        {
            Components::Transform& transform = entity.getComponent<Components::Transform>();
            Components::BoxCollider& collider = entity.getComponent<Components::BoxCollider>();
            Components::Script& script = entity.getComponent<Components::Script>();

            for (auto& other : entities)
            {
                if (other != entity)
                {
                    bool collision;
                    Components::Transform& otherTransform = other.getComponent<Components::Transform>();
                    Components::BoxCollider& otherCollider = other.getComponent<Components::BoxCollider>();

                    collision = collider.box.Collides(transform.position, otherCollider.box, otherTransform.position);
                    
                    if (collision == true)
                    {
                        script.OnCollision(other);
                    }
                }
            }
        }
    }
}
