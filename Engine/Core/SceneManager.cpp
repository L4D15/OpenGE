#include "Engine/Core/SceneManager.hpp"
#include "Engine/Core/Game.hpp"

SceneManager::SceneManager()
{
	currentScene = NULL;
}

SceneManager::~SceneManager()
{

}

void SceneManager::OnLoop()
{
	// TODO: Set delta time
	currentScene->Update();
}

void SceneManager::OnRender()
{
	currentScene->Render();
}

Scene& SceneManager::CreateScene(std::string name)
{
	Scene* scene;

	scene = new Scene(name);

	std::pair<std::string, Scene* > mappedScene(name, scene);
	sceneMapper.insert(mappedScene);

	return *scene;
}

Scene& SceneManager::CreateScene(std::string name, std::string filePath)
{
	Scene* scene;

	scene = new Scene(name, filePath);

	std::pair<std::string, Scene* > mappedScene(name, scene);
	sceneMapper.insert(mappedScene);

	return *scene;
}

Scene& SceneManager::AddScene(std::string sceneName, Scene& scene)
{
	std::pair<std::string, Scene* > mappedScene(sceneName, &scene);
	sceneMapper.insert(mappedScene);

	return scene;
}

/**
@brief	Changes the current scene.

@return The current scene.
*/
Scene& SceneManager::ChangeScene(std::string sceneName)
{
	std::map<std::string, Scene* >::iterator mappedScene;

	mappedScene = sceneMapper.find(sceneName);

	if (mappedScene != sceneMapper.end())
	{
		if (currentScene != NULL)
		{
			currentScene->OnDeactivation();
		}

		currentScene = mappedScene->second;
		currentScene->OnActivation();
	}
	else
	{
		Game::Log("SceneManager - Error, the scene does not exist.");
	}

	return *currentScene;
}

void SceneManager::DeleteScene(std::string sceneName)
{
	std::map<std::string, Scene* >::iterator mappedScene;

	mappedScene = sceneMapper.find(sceneName);

	if (mappedScene != sceneMapper.end())
	{
		Scene* scene = mappedScene->second;
		sceneMapper.erase(mappedScene);
		delete scene;
	}
}

void SceneManager::DeleteScene(Scene& scene)
{
	DeleteScene(scene.name);
}

void SceneManager::ChangeName(std::string name, std::string newName)
{
	Scene& scene = GetScene(name);
	DeleteScene(name);

	std::pair<std::string, Scene* > mappedScene(newName, &scene);

	sceneMapper.insert(mappedScene);
}

void SceneManager::ChangeName(Scene& scene, std::string newName)
{
	ChangeName(scene.name, newName);
}

Scene& SceneManager::GetScene(std::string name)
{
	return (*(sceneMapper.find(name)->second));
}

