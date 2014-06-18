#include "Engine/Systems/Physics.hpp"
#include "Engine/Components/Physics.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Core/Game.hpp"

using namespace Systems;

Physics::Physics()
    : Base(anax::ComponentFilter().requires<Components::Transform, Components::Physics>())
{

}

Physics::~Physics()
{

}

void Physics::Update() const
{
    auto entities = getEntities();
    for (auto& entity : entities)
    {
        Components::Transform& transform = entity.getComponent<Components::Transform>();
        Components::Physics& physics = entity.getComponent<Components::Physics>();

        transform.position = transform.position + (physics.velocity * Game::time->deltaTime);
    }
}
