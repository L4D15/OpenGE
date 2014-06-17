#include "Engine/Systems/SpriteRendering.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Components/SpriteRenderer.hpp"

using namespace Systems;

SpriteRendering::SpriteRendering()
: Base(anax::ComponentFilter().requires<Transform, SpriteRenderer>())
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
		Transform& transform = entity.getComponent<Transform>();
		SpriteRenderer& sprite = entity.getComponent<SpriteRenderer>();

		sprite.Render(	transform.position,
						transform.rotation,
						transform.scale);
		sprite.Update();
	}
}
