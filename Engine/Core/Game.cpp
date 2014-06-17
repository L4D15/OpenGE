#include "Engine/Core/Game.hpp"
#include "Engine/Assets/Sprite.hpp"
#include <assert.h>

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
Scripting*			Game::scripting 		= NULL;
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
	delete scripting;
	delete window;
	SDL_Quit();
	TTF_Quit();
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
	window = new Window();
	window->title = "Default Game Window";
	window->Show(1366, 720, false);
}

void Game::InitializeTime()
{
	time = new Time();
	time->Update();
}

void Game::InitializeSettings()
{
	settings = new Settings();
}

void Game::InitializeEventManagement()
{
	eventManager = new EventManager();
	input = new Input();
}

void Game::InitializeSceneManager()
{
	sceneManager = new SceneManager();
	sceneManager->CreateScene("DefaultScene");
	sceneManager->ChangeScene("DefaultScene");
}

void Game::InitializeResourceManager()
{
	resourceManager = new ResourceManager();
    resourceManager->GetAsset<Sprite>("Assets/Sprites/Missing_Image.png");
}

void Game::InitializeScripting()
{
	scripting = new Scripting();
	scripting->CreateEnvironment();
}

void Game::Initialize()
{

}

void Game::Start()
{
	InitializeLibraries();
	InitializeSettings();
	InitializeWindow();
	InitializeTime();
	InitializeSceneManager();
	InitializeEventManagement();
	InitializeScripting();
    InitializeResourceManager();

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
