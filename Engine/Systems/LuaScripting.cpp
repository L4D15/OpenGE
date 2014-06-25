#include "Engine/Systems/LuaScripting.hpp"
#include "Engine/Components/LuaScript.hpp"
#include "Engine/Core/Game.hpp"
#include <sstream>

using namespace Systems;

LuaScripting::LuaScripting()
    : Base(anax::ComponentFilter().requires<Components::LuaScript>())
{
    // Initialize Lua
    Game::Log("Initializing Lua...", false);

    luaState = luaL_newstate();

    if (luaState == NULL)
    {
        Game::Log("Failed");
    }
    else
    {
        Game::Log("Ok");
        luaL_openlibs(luaState);
        luabind::open(luaState);
    }
}

LuaScripting::~LuaScripting()
{
    lua_close(luaState);
}

void LuaScripting::RegisterClass(const std::string scriptPath)
{
    int error;

    error = luaL_dofile(luaState, scriptPath.c_str());

    if (error != 0)
    {
        Game::Log("-- [!] Failed to register class in ", false);
        Game::Log(scriptPath);
        Game::Log(lua_tostring(luaState, lua_gettop(luaState)));
        lua_pop(luaState, 1);
    }
}

/**
 * @brief Register the object in Lua so we can add class instances to it.
 * @param object    Object to be registered in Lua.
 */
void LuaScripting::RegisterObject(const anax::Entity &object)
{
    GameObject& gameObject = Game::Find(object);

    std::stringstream ss;

    ss << gameObject.name << " = {}" << std::endl;

    luaL_dostring(luaState, ss.str().c_str());
}

void LuaScripting::CreateInstance(const std::string className, const anax::Entity &owner)
{
    GameObject& object = Game::Find(owner);

    std::stringstream ss;

    ss << object.name << "['" << className << "'] = " << className << "()" << std::endl;

    std::string luaString = ss.str();
    Game::Log("Executing the following Lua code: ");
    Game::Log(luaString);
    Game::Log("--- END ---");

    luaL_dostring(luaState, luaString.c_str());
}

void LuaScripting::RunFunction(const string function, const string className, const anax::Entity &owner)
{
    GameObject& object = Game::Find(owner);

    std::stringstream ss;

    ss << object.name << "['" << className << "']." << function << "()";

    luaL_dostring(luaState, ss.str().c_str());
}

void LuaScripting::onEntityAdded(anax::Entity& entity)
{
    RegisterObject(entity);
    CreateInstance(entity.getComponent<Components::LuaScript>().GetClass(), entity);
    RunFunction("Start", entity.getComponent<Components::LuaScript>().GetClass(), entity);
}

void LuaScripting::onEntityRemoved(anax::Entity& entity)
{
    // TODO: Free data from lua. How?!
}

void LuaScripting::ProcessEntities()
{
    auto entities = getEntities();

    for (auto& entity : entities)
    {
        RunFunction("Update", entity.getComponent<Components::LuaScript>().GetClass(), entity);
    }
}
