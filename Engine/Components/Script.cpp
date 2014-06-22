#include "Engine/Components/Script.hpp"
#include "Engine/Core/Game.hpp"
#include <luabind/luabind.hpp>
#include <luabind/function.hpp>
#include "Engine/Libraries/Libraries.hpp"

using namespace Components;

Script::Script()
: owner(NULL)
{

}

Script::Script(const std::string scriptPath)
: owner(NULL)
{
    scripts.push_back(Game::resourceManager->GetPath(scriptPath));
    int ini = scriptPath.find_last_of('/') + 1;

    std::string str;

    str = scriptPath.substr(ini);
    str = str.erase(str.find_last_of('.')); 	// Delete '.lua'
    classNames.push_back(str);
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

    std::string str;

    str = scriptPath.substr(ini);
    str = str.erase(str.find_last_of('.')); 	// Delete '.lua'
    classNames.push_back(str);
}

Script::Script(json_spirit::Value jsonString)
: owner(NULL)
{
    /*
        JSON TEMPLATE FOR SCRIPT COMPONENT
        {
            "name": "Script"
            "scripts":
            [
                "Assets/Scripts/script1.lua",
                "Assets/Scripts/script2.lua"
            ]
        }
    */
    std::string scriptPath;
    std::string className;

    json_spirit::Array scriptsArray;
    scriptsArray = jsonString.getObject().at("scripts").getArray();

    for (unsigned int index = 0; index < scriptsArray.size(); ++index)
    {
        scriptPath = Game::resourceManager->GetPath(scriptsArray[index].getString());

        className = scriptPath.substr(scriptPath.find_last_of('/') + 1);
        className = className.erase(className.find_last_of('.'));

        scripts.push_back(scriptPath);
        classNames.push_back(className);
    }
}

Script::~Script()
{

}


void Script::Start() const
{
    for (unsigned int index = 0; index < scripts.size(); ++index)
    {
        Game::scripting->CallFunction("Start", classNames[index], scripts[index]);
    }
}

void Script::Update() const
{
    for (unsigned int index = 0; index < scripts.size(); ++index)
    {
        Game::scripting->CallFunction("Update", classNames[index], scripts[index]);
    }
}

void Script::OnCollision(anax::Entity& collided) const
{
    GameObject& collidedObject = Game::Find(collided);

    for (unsigned int index = 0; index < scripts.size(); ++index)
    {
        Game::scripting->SetGlobal("collidedObject", collidedObject);
        Game::scripting->CallFunction("OnCollision", classNames[index], scripts[index]);
    }

}

std::string Script::ToString()
{
    std::stringstream ss;

    ss << "[ ";

    for (unsigned int index = 0; index < scripts.size(); ++index)
    {
        ss << classNames[index] << " -> " << scripts[index] << "\t";
    }

    ss << "]";

    return ss.str();
}
