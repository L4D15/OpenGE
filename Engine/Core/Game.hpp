#ifndef OPENGE_GAME_H
#define OPENGE_GAME_H

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Core/Window.hpp"
#include "Engine/Core/Time.hpp"
#include "Engine/Core/Settings.hpp"
#include "Engine/Core/EventManager.hpp"
#include "Engine/Core/SceneManager.hpp"
#include "Engine/Core/Input.hpp"
#include <string>

using namespace std;

class Game
{
public:
	Game();
	~Game();

	void					Start();
	void					MainLoop();
	void					HandleEvents();
	void					Update();
	void					Render();

	static void				Terminate();
	static void				Log(string text, bool endLine = true);

private:
	void					InitializeLibraries();
	void					InitializeWindow();
	void					InitializeTime();
	void					InitializeSettings();
	void					InitializeEventManagement();
	void					InitializeSceneManager();

protected:
	string					name;

// Static variables

protected:
	static bool				instantiated;
	static bool				run;

public:
	static Window*			window;
	static Time*			time;
	static Settings*		settings;
	static EventManager* 	eventManager;
	static SceneManager*	sceneManager;
	static Input*			input;
	
};

#endif // OPENGE_GAME_H