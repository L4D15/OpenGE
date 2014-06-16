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
    TestScene* scene;
    scene = new TestScene();
    sceneManager->AddScene("TestScene", *scene);
	
	//sceneManager->CreateScene("TestScene", Game::resourceManager->GetPath("Scenes/TestScene.json"));
	sceneManager->ChangeScene("TestScene");

    Scene& currentScene = sceneManager->GetCurrentScene();
    Game::Log(currentScene.ToString());
}
