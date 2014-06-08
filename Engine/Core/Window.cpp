#include "Engine/Core/Window.hpp"
#include "Engine/Core/Game.hpp"
#include <assert.h>
#include <sstream>

// Static variables
bool Window::instantiated = false;
// ---

Window::Window()
{
	// Fail the instantiation if there is already an instance
	assert(instantiated == false);
	instantiated = true;

	title = "Default Window";
}

Window::~Window()
{
	
}

void Window::Show()
{
	SDL_DisplayMode displayMode;
	int errorID;

	// Check all displays

	for (unsigned int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
	{
		errorID = SDL_GetCurrentDisplayMode(0, &displayMode);

		if (errorID != 0)
		{
			Game::Log(SDL_GetError());
		}
		else
		{
			stringstream str;
			str << "Display " << i << " [" << displayMode.w << "x" << displayMode.h << "]";
			Game::Log(str.str());
		}
	}

	int width;
	int height;

	width = displayMode.w;
	height = displayMode.h;

	stringstream str;
	str << "Selected resolution [" << width << "x" << height << "]";

	Game::Log(str.str());

	Show(width, height, true);
}

void Window::Show(int w, int h, bool fullscreen)
{
	int flags;

	if (fullscreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
	}
	else
	{
		flags = SDL_WINDOW_OPENGL;
	}

	width = w;
	height = h;

	stringstream str;
	str << "Creating Window [" << width << "x" << height << "]";

	Game::Log(str.str());

	window = SDL_CreateWindow(title.c_str(),
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								width,
								height,
								flags);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Activate the blend mode
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void Window::Clear()
{
	SDL_RenderClear(renderer);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Draw()
{
	SDL_RenderPresent(renderer);
}