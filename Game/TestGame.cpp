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
	Scene& scene = sceneManager->GetCurrentScene();
	Game::Log(scene.name);
}