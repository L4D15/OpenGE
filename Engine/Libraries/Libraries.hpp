#ifndef OPENGE_LIBRARIES_H
#define OPENGE_LIBRARIES_H

#define STUBBED(x) printf("STUBBED: %s\n", x)

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
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