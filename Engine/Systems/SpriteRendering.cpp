#include "Engine/Systems/SpriteRendering.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Components/SpriteRenderer.hpp"

using namespace Systems;

SpriteRendering::SpriteRendering()
    : Base(anax::ComponentFilter().requires<Components::Transform, Components::SpriteRenderer>())
{
	
}

SpriteRendering::~SpriteRendering()
{

}

void SpriteRendering::Render() const
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
        Components::Transform& transform = entity.getComponent<Components::Transform>();
        Components::SpriteRenderer& sprite = entity.getComponent<Components::SpriteRenderer>();

		sprite.Render(	transform.position,
						transform.rotation,
						transform.scale);
		sprite.Update();
	}
}
