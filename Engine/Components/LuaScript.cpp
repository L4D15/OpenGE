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

LuaScript::~LuaScript()
{

}
