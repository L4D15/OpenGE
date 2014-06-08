#ifndef OPENGE_WINDOW_H
#define OPENGE_WINDOW_H

#include <string>
#include "Engine/Libraries/Libraries.hpp"

using namespace std;

/**
@brief Window in which the game will be rendered.

There can be only one window, so more than one instantiation of the class will be forbidden.
*/
class Window
{
public:
	Window();
	~Window();

	void						Show();
	void						Show(int w, int h, bool fullscreen);
	void						Hide();

	void						Clear();
	void						Draw();

private:
	static bool 				instantiated;

public:
	string						title;
	SDL_Renderer*				renderer;

protected:
	SDL_Window*					window;
	Uint16						width;
	Uint16						height;

};

#endif /* OPENGE_WINDOW_H */