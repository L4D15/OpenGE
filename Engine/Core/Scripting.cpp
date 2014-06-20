#include "Engine/Core/Scripting.hpp"
#include "Engine/Core/Game.hpp"
#include "Engine/Core/Color.hpp"
#include "Engine/Core/Math/Vector3.hpp"
#include "Engine/Core/Math/Math.hpp"
#include "Engine/Core/Math/Quaternion.hpp"
#include "Engine/Core/EventManager.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Components/Physics.hpp"
#include "Engine/Components/SpriteRenderer.hpp"
#include "Engine/Components/Script.hpp"
#include "Engine/Assets/Asset.hpp"
#include "Engine/Assets/RenderizableAsset.hpp"
#include "Engine/Assets/Sprite.hpp"
#include "Engine/Core/Collisions/Box.hpp"
#include <luabind/operator.hpp>


Scripting::Scripting()
{
	Game::Log("Initializing lua...", false);
	state = luaL_newstate();

	if (state != NULL)
	{
		Game::Log("Ok");
	}
	else
	{
		Game::Log("Failed");
	}

    luaL_openlibs(state);

	luabind::open(state);
}

Scripting::~Scripting()
{
	lua_close(state);
}

/**
@brief			Executes a lua script.
@param script 	Path to script.
*/
bool Scripting::Execute(std::string script)
{
	int error;

	error = luaL_dofile(state, script.c_str());

	if (error != 0) 
	{
		Game::Log(lua_tostring(state, -1));
		return false;
	}
	return true;
}

void Scripting::CreateEnvironment()
{
	using namespace luabind;

    Game::Log("Creating lua environment...", false);

    module(state)
	[
        Vector3::RegisterForScripting(),
        Quaternion::RegisterForScripting(),
        Math::RegisterForScripting(),
        Color::RegisterForScripting(),
        Time::RegisterForScripting(),
        Scene::RegisterForScripting(),
        GameObject::RegisterForScripting(),
        Components::Transform::RegisterForScripting(),
        Components::Physics::RegisterForScripting(),
        Components::SpriteRenderer::RegisterForScripting(),
        Asset::RegisterForScripting(),
        RenderizableAsset::RegisterForScripting(),
        Sprite::RegisterForScripting(),
        ResourceManager::RegisterForScripting(),
        Game::RegisterForScripting(),
        Input::RegisterForScripting(),
        Key::RegisterForScripting(),
        ButtonMapping::RegisterForScripting(),
        Box::RegisterForScripting()
	];
    
	Game::Log("Ok");
}

void Scripting::CallFunction(const std::string function, const std::string className, const std::string scriptPath) const
{
	try
	{
		int error;

	    error = luaL_dofile(state, scriptPath.c_str());

	    if (error != 0)
	    {
	    	Game::Log(lua_tostring(state, lua_gettop(state)));
	    	lua_pop(state, 1);
	    }
	    else
	    {
		    luabind::object* states = new luabind::object;
		    *states = luabind::globals(state);

		    (*states)[className.c_str()][function.c_str()]();

		    delete states;
	    }
	}catch(...)
	{
		Game::Log(lua_tostring(state, lua_gettop(state)));
    	lua_pop(state, 1);
	}
}

void Scripting::OnCollision(const std::string className, const std::string scriptPath, GameObject& collider) const
{
    std::string functionName;
}
