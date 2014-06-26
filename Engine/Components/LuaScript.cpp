#include "Engine/Components/LuaScript.hpp"
#include "Engine/Core/Game.hpp"

using namespace Components;

LuaScript::LuaScript()
{
}

/**
 * @brief
 * @param className Name of the class defined in the script. The two name must be identical.
 * @param path      Path of the Lua script where the class is defined.
 */
LuaScript::LuaScript(const std::string className, const std::string path)
:   className(className),
    scriptPath(Game::resourceManager->GetPath(path))
{

}

LuaScript::LuaScript(json_spirit::Value jsonString)
{
    className = jsonString.getObject().at("class").getString();
    scriptPath = Game::resourceManager->GetPath(jsonString.getObject().at("path").getString());
}

LuaScript::~LuaScript()
{

}
