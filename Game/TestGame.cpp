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
	//TestScene scene;
	//sceneManager->AddScene("TestScene", scene);
	sceneManager->CreateScene("TestScene", Game::resourceManager->GetPath("Scenes/TestScene.json"));
	sceneManager->ChangeScene("TestScene");
	
	Scene& scene = sceneManager->GetCurrentScene();
	Game::Log(scene.name);
	Game::Log(scene.ToString());
}