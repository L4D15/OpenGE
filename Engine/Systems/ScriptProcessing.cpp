#include "Engine/Systems/ScriptProcessing.hpp"
#include "Engine/Components/Script.hpp"
#include "Engine/Core/Game.hpp"

using namespace Systems;

ScriptProcessing::ScriptProcessing()
: Base(anax::ComponentFilter().requires<Components::Script>())
{

}

ScriptProcessing::~ScriptProcessing()
{

}

void ScriptProcessing::Update() const
{
	auto entities = getEntities();

	for (auto& entity : entities)
	{
		Components::Script& script = entity.getComponent<Components::Script>();

		// Set the owner of the script as the global 'self' lua variable
		Game::scripting->SetGlobal<GameObject&>("gameObject", *script.owner);
		script.Update();
	}
}

void ScriptProcessing::onEntityAdded(anax::Entity& entity)
{
	Components::Script& script = entity.getComponent<Components::Script>();

    Game::scripting->SetGlobal<GameObject&>("gameObject", *script.owner);
	script.Start();
}