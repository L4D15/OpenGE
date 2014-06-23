#include "Engine/Core/Time.hpp"
#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Core/Game.hpp"
#include <sstream>
#include <luabind/operator.hpp>

using namespace std;

// Static variables
float Time::deltaTime = 0.0f;
float Time::time = 0.0f;
// ---

Time::Time()
{
	FPS = 0;
	FPSCounter = 0;
	FPSTimer = 0.0f;
	currentTime = 0.0f;
	Update();
}

Time::~Time()
{
	
}

void Time::Update()
{
	oldTime = currentTime;
	currentTime = SDL_GetTicks();
	time = currentTime;

	deltaTime = (currentTime - oldTime) * 0.001f;

	if (FPSTimer <= 1.0f)
	{
		FPSTimer += deltaTime;
		++FPSCounter;
	}
	else
	{
		FPSTimer = 0.0f;
		FPS = FPSCounter;
		FPSCounter = 0;

		stringstream ss;

		ss << "FPS: " << FPS << "[" << deltaTime << "]";

		Game::Log(ss.str().c_str());
	}
}

int Time::GetFPS()
{
	return FPS;
}

void Time::WaitForNextFrame()
{
	float endTime;

	endTime = SDL_GetTicks();

	float timeToWait;
	float timeElapsed;

	timeElapsed = (endTime - time);

	timeToWait = (1000.0f / Game::settings->maxFPS) - timeElapsed;

	if (timeToWait > 0)
	{
		SDL_Delay(timeToWait);
	}
}
