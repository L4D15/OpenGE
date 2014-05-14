#ifndef OPENGE_EVENTMANAGER_H
#define OPENGE_EVENTMANAGER_H

#include "Engine/Libraries/Libraries.hpp"

class EventManager
{
public:
	EventManager();
	~EventManager();

	void				ProcessEvents();

protected:
	void				ProcessEvent(SDL_Event* event);
    void        		OnInputFocus();
    void        		OnInputBlur();
    void        		OnKeyDown(SDL_Keycode key, Uint16 mod);
    void        		OnKeyUp(SDL_Keycode key, Uint16 mod);
    void        		OnMouseFocus();
    void        		OnMouseBlur();
    void        		OnMouseMove(int mouseX, int mouseY, int relX, int relY, bool left, bool right, bool middle);
    void        		OnMouseWheel(bool up, bool down);
    void        		OnLeftButtonDown(int mouseX, int mouseY);
    void        		OnLeftButtonUp(int mouseX, int mouseY);
    void        		OnRightButtonDown(int mouseX, int mouseY);
    void        		OnRightButtonUp(int mouseX, int mouseY);
    void        		OnMiddleButtonDown(int mouseX, int mouseY);
    void        		OnMiddleButtonUp(int mouseX, int mouseY);
    void        		OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
    void        		OnJoyButtonDown(Uint8 which, Uint8 button);
    void        		OnJoyButtonUp(Uint8 which, Uint8 button);
    void        		OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);
    void        		OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
    void        		OnMinimize();
    void        		OnRestore();
    void        		OnResize(int w, int h);
    void        		OnExpose();
    void        		OnExit();
    void        		OnUser(Uint8 type, int code, void * data1, void * data2);

private:
	static bool			instanciated;
};

#endif // OPENGE_EVENTMANAGER_H