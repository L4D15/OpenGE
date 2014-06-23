#ifndef OPENGE_TIME_H
#define OPENGE_TIME_H

#include "Engine/Libraries/Libraries.hpp"
#include <luabind/scope.hpp>

class Time
{
public:
	Time();
	~Time();

	void					Update();
	int						GetFPS();
	void					WaitForNextFrame();
    static int              GetTime() { return SDL_GetTicks(); }
    static float            GetDeltaTime() { return deltaTime; }

    static luabind::scope   RegisterForScripting()
    {
    return
            luabind::class_<Time>("Time")
                .scope
                [
                    luabind::def("GetDeltaTime", &Time::GetDeltaTime),
                    luabind::def("GetTime", &Time::GetTime)
                ]
            ;
	}

public:
	static float			deltaTime;
	static float			time;

private:
	float					currentTime;	// Ticks at the start of the frame
	float					oldTime;		// Ticks at start of the last frame

	int						FPS;
	int						FPSCounter;
	float					FPSTimer;
};

#endif // OPENGE_TIME_H
