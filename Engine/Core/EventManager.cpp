#include "Engine/Core/EventManager.hpp"
#include "Engine/Core/Game.hpp"
#include <assert.h>

// Static variables
bool EventManager::instanciated = false;
// ---

EventManager::EventManager()
{
	assert(instanciated == false);
	instanciated = true;	
}

EventManager::~EventManager()
{
	
}

void EventManager::ProcessEvents()
{
	SDL_Event currentEvent;

	while (SDL_PollEvent(&currentEvent))
	{
		ProcessEvent(&currentEvent);
	}
}

void EventManager::ProcessEvent(SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_WINDOWEVENT:
            switch (event->window.type)
            {
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    OnInputFocus();
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    OnInputBlur();
                    break;
                case SDL_WINDOWEVENT_ENTER:
                    OnMouseFocus();
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    OnMouseBlur();
                    break;
            }

        case SDL_KEYDOWN:
            OnKeyDown(event->key.keysym.sym, event->key.keysym.mod);
            break;

        case SDL_KEYUP:
            OnKeyUp(event->key.keysym.sym, event->key.keysym.mod);
            break;

        case SDL_MOUSEMOTION:
            OnMouseMove(event->motion.x,
                    event->motion.y,
                    event->motion.xrel,
                    event->motion.yrel,
                    (event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
                    (event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
                    (event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch (event->button.button)
            {
                case SDL_BUTTON_LEFT:
                    OnLeftButtonDown(event->button.x, event->button.y);
                    break;

                case SDL_BUTTON_RIGHT:
                    OnRightButtonDown(event->button.x, event->button.y);
                    break;

                case SDL_BUTTON_MIDDLE:
                    OnMiddleButtonDown(event->button.x, event->button.y);
                    break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            switch (event->button.button)
            {
                case SDL_BUTTON_LEFT:
                    OnLeftButtonUp(event->button.x, event->button.y);
                    break;

                case SDL_BUTTON_RIGHT:
                    OnRightButtonUp(event->button.x, event->button.y);
                    break;

                case SDL_BUTTON_MIDDLE:
                    OnMiddleButtonUp(event->button.x, event->button.y);
                    break;
            }

        case SDL_JOYAXISMOTION:
            OnJoyAxis(event->jaxis.which, event->jaxis.axis, event->jaxis.value);
            break;

        case SDL_JOYBALLMOTION:
            OnJoyBall(event->jball.which, event->jball.ball, event->jball.xrel, event->jball.yrel);
            break;

        case SDL_JOYHATMOTION:
            OnJoyHat(event->jhat.which, event->jhat.hat, event->jhat.value);
            break;

        case SDL_JOYBUTTONDOWN:
            OnJoyButtonDown(event->jbutton.which, event->jbutton.button);
            break;

        case SDL_JOYBUTTONUP:
            OnJoyButtonUp(event->jbutton.which, event->jbutton.button);
            break;

        case SDL_QUIT:
            OnExit();
            break;

        case SDL_SYSWMEVENT:
            // Ignore
            break;

        case SDL_WINDOWEVENT_RESIZED:
            OnResize(event->window.data1, event->window.data2); // TODO: Check this is right
            break;

        case SDL_WINDOWEVENT_EXPOSED:
            OnExpose();
            break;

        default:
            OnUser(event->user.type, event->user.code, event->user.data1, event->user.data2);
            break;
    }
}

void EventManager::OnInputBlur()
{
    // Pure virtual
}

void EventManager::OnInputFocus()
{
    // Pure Virtual
}

void EventManager::OnKeyDown(SDL_Keycode key, Uint16 mod)
{
    Game::input->NotifyKeyPress(key);
}

void EventManager::OnKeyUp(SDL_Keycode key, Uint16 mod)
{
    Game::input->NotifyKeyRelease(key);
}

void EventManager::OnMouseFocus()
{
    // Pure virtual
}

void EventManager::OnMouseBlur()
{
    // Pure virtual
}

void EventManager::OnMouseMove(int mouseX, int mouseY, int relX, int relY, bool left, bool right, bool middle)
{
    // Pure virtual
}

void EventManager::OnMouseWheel(bool up, bool down)
{
    // Pure virtual
}

void EventManager::OnLeftButtonDown(int mouseX, int mouseY)
{
    // Pure virtual
}

void EventManager::OnLeftButtonUp(int mouseX, int mouseY)
{
    // Pure virtual
}

void EventManager::OnRightButtonDown(int mouseX, int mouseY)
{
    // Pure virtual
}

void EventManager::OnRightButtonUp(int mouseX, int mouseY)
{
    // Pure virtual
}

void EventManager::OnMiddleButtonDown(int mouseX, int mouseY)
{
    // Pure virtual
}

void EventManager::OnMiddleButtonUp(int mouseX, int mouseY)
{
    // Pure virtual
}

void EventManager::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{
    // Pure virtual
}

void EventManager::OnJoyButtonDown(Uint8 which, Uint8 button)
{
    // Pure virtual
}

void EventManager::OnJoyButtonUp(Uint8 which, Uint8 button)
{
    // Pure virtual
}

void EventManager::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value)
{
    // Pure virtual
}

void EventManager::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel)
{
    // Pure virtual
}

void EventManager::OnMinimize()
{
    // Pure virtual
}

void EventManager::OnRestore()
{
    // Pure virtual
}

void EventManager::OnResize(int w, int h)
{
    // Pure virtual
}

void EventManager::OnExpose()
{
    // Pure virtual
}

void EventManager::OnExit()
{
    Game::Terminate();
}

void EventManager::OnUser(Uint8 type, int code, void* data1, void* data2)
{
    // Pure virtual
}
