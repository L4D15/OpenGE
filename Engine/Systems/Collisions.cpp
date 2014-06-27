#include "Engine/Systems/Collisions.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Components/BoxCollider.hpp"
#include "Engine/Components/LuaScript.hpp"
#include "Engine/Systems/LuaScripting.hpp"
#include "Engine/Core/Game.hpp"

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
        Components::Transform& transform = entity.getComponent<Components::Transform>();
        Components::BoxCollider& collider = entity.getComponent<Components::BoxCollider>();
        if (entity.hasComponent<Components::LuaScript>() == true)
        {
            Components::LuaScript& script = entity.getComponent<Components::LuaScript>();
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
                        if (otherCollider.isTrigger)
                        {
                            LuaScripting::RunFunction("OnTrigger", script.GetClass(), entity);
                        }
                        else
                        {
                            LuaScripting::RunFunction("OnCollision", script.GetClass(), entity);
                            Block(entity, other);
                        }
                    }
                }
            }
        }
    }
}

void Collisions::Block(anax::Entity& a, anax::Entity& b)
{
    Vector3 velA, velB;
    
    if (a.hasComponent<Components::Physics>()) {
        velA = a.getComponent<Components::Physics>().velocity;
    }
    
    if (b.hasComponent<Components::Physics>()) {
        velB = a.getComponent<Components::Physics>().velocity;
    }
    
    // TODO: Implement restitution equation
    // http://gamedevelopment.tutsplus.com/tutorials/create-custom-2d-physics-engine-aabb-circle-impulse-resolution--gamedev-6331
    
}
