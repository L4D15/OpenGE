#include "Game/TestGame.hpp"
#include "Game/Scenes/TestScene.hpp"

TestGame::TestGame()
: Game()
{
	
}

TestGame::~TestGame()
{
	
}

void TestGame::Initialize()
{
	TestScene scene;
	sceneManager->AddScene("TestScene", scene);
	sceneManager->ChangeScene("TestScene");
	
	Game::Log(scene.name);
	Game::Log(scene.ToString());
}