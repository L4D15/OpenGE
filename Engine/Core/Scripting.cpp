#include "Engine/Core/Scripting.hpp"
#include "Engine/Core/Game.hpp"
#include "Engine/Core/Color.hpp"


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
		class_<Color>("Color")
			.def(constructor<int, int, int, int>())
			.def("ToString", &Color::ToString)
	];
}
