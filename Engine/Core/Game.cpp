#include "Engine/Core/Game.hpp"
#include "Engine/Assets/Sprite.hpp"
#include <assert.h>
#include <luabind/scope.hpp>

using namespace std;

// Static initialization
bool 				Game::instantiated 		= false;
bool 				Game::run 				= false;
Window* 			Game::window 			= NULL;
Time* 				Game::time 				= NULL;
Settings* 			Game::settings 			= NULL;
EventManager* 		Game::eventManager 		= NULL;
SceneManager*		Game::sceneManager 		= NULL;
ResourceManager* 	Game::resourceManager 	= NULL;
Input*				Game::input 			= NULL;
// ---

Game::Game()
{
	// Fail instantiation if there is already an instance
	assert(instantiated == false);
	instantiated = true;

	// Default properties
	name = "Default Game";
}

Game::~Game()
{
	delete time;
	delete settings;
	delete eventManager;
	delete sceneManager;
	delete resourceManager;
	delete input;
    
    // TODO: Find why this throws a EXC_BAC_ACCESS
    
	//delete window;
	TTF_Quit();
    //SDL_Quit();
    
    // ---
}

/**
@brief	Initializes al required libraries (SDL2, OpenGL, Pyhton etc)
*/
void Game::InitializeLibraries()
{
	int errorID;

	// SDL2
	Game::Log("Initializing SDL2...", false);

	errorID = SDL_Init(SDL_INIT_EVERYTHING);

	if (errorID != 0)
	{
		Game::Log("Failed");
		Game::Log(SDL_GetError());
	}
	else
	{
		Game::Log("Ok");
	}

	// SDL_ttf
	Game::Log("Initializing SDL_ttf...", false);
	errorID = TTF_Init();

	if (errorID != 0)
	{
		Game::Log("Failed");
		Game::Log(TTF_GetError());
	}
	else
	{
		Game::Log("Ok");
	}
}

void Game::InitializeWindow()
{
	Game::Log("Initializing Window:");
	window = new Window();
	window->title = "Default Game Window";
	window->Show(1366, 720, false);
	if (window != NULL)
	{
		Game::Log("Ok");
	}
	else
	{
		Game::Log("Fail");
	}
}

void Game::InitializeTime()
{
	Game::Log("Initializing Time...", false);
	time = new Time();
	time->Update();
	if (time != NULL)
	{
		Game::Log("Ok");
	}
	else
	{
		Game::Log("Fail");
	}
}

void Game::InitializeSettings()
{
	Game::Log("Initializing Settings...", false);
	settings = new Settings();
	if (settings != NULL)
	{
		Game::Log("Ok");
	}
	else
	{
		Game::Log("Fail");
	}
}

void Game::InitializeEventManagement()
{
	Game::Log("Initializing Event Manager...", false);
	eventManager = new EventManager();
	if (eventManager != NULL)
	{
		Game::Log("Ok");
	}
	else
	{
		Game::Log("Fail");
	}
}

void Game::InitializeSceneManager()
{
	Game::Log("Initializing Scene Manager...", false);
	sceneManager = new SceneManager();
	if (sceneManager != NULL)
	{
		Game::Log("Ok");
	}
	else
	{
		Game::Log("Fail");
	}
}

void Game::InitializeResourceManager()
{
	Game::Log("Initializing Resource Manager...", false);
	resourceManager = new ResourceManager();
    resourceManager->GetAsset<Sprite>("Assets/Sprites/Missing_Image.png");
    if (resourceManager != NULL)
	{
		Game::Log("Ok");
	}
	else
	{
		Game::Log("Fail");
	}
}

void Game::InitializeInput()
{
	Game::Log("Initializing Input...", false);
	input = new Input();
	if (input != NULL)
	{
		Game::Log("Ok");

		Game::Log(input->ToString());
	}
	else
	{
		Game::Log("Fail");
	}
}

void Game::Initialize()
{

}

void Game::Start()
{
	InitializeLibraries();
	InitializeInput();
	InitializeSettings();
	InitializeWindow();
	InitializeTime();
    InitializeEventManagement();
    InitializeResourceManager();
	InitializeSceneManager();

	Initialize();

	run = true;
	MainLoop();
}

void Game::MainLoop()
{
	while (run == true)
	{
		HandleEvents();
		Update();
		Render();

		time->WaitForNextFrame();
	}
}

void Game::HandleEvents()
{
	eventManager->ProcessEvents();
}

void Game::Update()
{
    time->Update();
	sceneManager->OnLoop();
}

void Game::Render()
{
	window->Clear();

	// Draw stuff
	sceneManager->OnRender();

	window->Draw();
}

void Game::Terminate()
{
	run = false;
}

void Game::Log(string text, bool endLine)
{
	if (endLine == true)
	{
		printf("%s\n", text.c_str());
	}
	else
	{
		printf("%s", text.c_str());
	}
}

GameObject& Game::Find(const anax::Entity& entity)
{
	return sceneManager->GetCurrentScene().Find(entity);
}
