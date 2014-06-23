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
        if (SetContext(script) == true)
        {
            script.Update();
        }
    }
}

void ScriptProcessing::onEntityAdded(anax::Entity& entity)
{
    Components::Script& script = entity.getComponent<Components::Script>();

    GameObject* owner;
    owner = script.owner;

    if (SetContext(script) == true)
    {
        script.Start();
    }


}

bool ScriptProcessing::SetContext(Components::Script& script) const
{
    GameObject* owner;
    owner = script.owner;

    if (owner != NULL)
    {
        Game::scripting->SetGlobal<GameObject&>("gameObject", *owner);
        return true;
    }
    else
    {
        Game::Log("-- [!] Script don't have an owner. It will certainly fail");
        return false;
    }
}
