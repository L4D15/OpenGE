#include "Game/TestGame.hpp"

TestGame::TestGame()
: Game()
{
	
}

TestGame::~TestGame()
{
	
}

void TestGame::Initialize()
{
	Scene& scene = sceneManager->CreateScene("TestScene", Game::resourceManager->GetPath("Scenes/TestScene.json"));
	sceneManager->ChangeScene("TestScene");
	
	Game::Log(scene.name);
	Game::Log(scene.ToString());
}