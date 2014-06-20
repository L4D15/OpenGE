#include "Engine/Components/Script.hpp"
#include "Engine/Core/Game.hpp"
#include <luabind/luabind.hpp>
#include <luabind/function.hpp>

using namespace Components;

Script::Script()
{

}

Script::Script(const std::string scriptPath)
{
    scripts.push_back(Game::resourceManager->GetPath(scriptPath));
    int ini = scriptPath.find_last_of('/') + 1;

    className = scriptPath.substr(ini);
    className = className.erase(className.find_last_of('.')); 	// Delete '.lua'
}

Script::Script(const std::list<std::string>& scriptsPath)
{
    for (auto script : scriptsPath)
    {
        scripts.push_back(Game::resourceManager->GetPath(script));
        // TODO: Store script classes
    }
}

Script::Script(GameObject* owner, const std::string scriptPath)
: owner(owner)
{
	scripts.push_back(Game::resourceManager->GetPath(scriptPath));
    int ini = scriptPath.find_last_of('/') + 1;

    className = scriptPath.substr(ini);
    className = className.erase(className.find_last_of('.')); 	// Delete '.lua'
}

Script::~Script()
{

}


void Script::Start() const
{
    for (auto& script : scripts)
    {
        Game::scripting->CallFunction("Start", className, script);
    }
}

void Script::Update() const
{
    for (auto& script : scripts)
    {
        Game::scripting->CallFunction("Update", className, script);
    }
}

void Script::OnCollision(anax::Entity& collided) const
{
    GameObject& collidedObject = Game::Find(collided);

    for (auto& script : scripts)
    {
        Game::scripting->SetGlobal("collidedObject", collidedObject);
        Game::scripting->CallFunction("OnCollision", className, script);
    }

}


