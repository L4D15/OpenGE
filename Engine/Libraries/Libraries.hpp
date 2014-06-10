#ifndef OPENGE_LIBRARIES_H
#define OPENGE_LIBRARIES_H

#define STUBBED(x) printf("STUBBED: %s\n", x)

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
	#include <anax/anax.hpp>
	#include <json_spirit/json_spirit.h>

	extern "C"
	{
		#include <lua.h>
		#include <lauxlib.h>
		#include <lualib.h>
	}
	#include <luabind/luabind.hpp>

#elif _Win32
	#include <GL/gl.h>
#elif _Win64
	#include <GL/gl.h>
#elif __linux
	#include <GL/gl.h>
#else
	STUBBED("Libraries.hpp : Libraries include are not implemented for this platform.");
#endif

#endif // OPENGE_LIBRARIES_H
