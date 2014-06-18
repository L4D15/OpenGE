#include "Engine/Core/Scripting.hpp"
#include "Engine/Core/Game.hpp"
#include "Engine/Core/Color.hpp"
#include "Engine/Core/Math/Vector3.hpp"
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

    module(state)
	[
        Vector3::RegisterForScripting(),
        Game::RegisterForScripting()
	];
}
