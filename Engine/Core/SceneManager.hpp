#ifndef OPENGE_SCENEMANAGER_H
#define OPENGE_SCENEMANAGER_H

#include "Engine/Core/Scene.hpp"
#include <map>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void				OnLoop();
	void				OnRender();

	Scene&				ChangeScene(std::string sceneName);
	Scene&				CreateScene(std::string sceneName);
	Scene&				CreateScene(std::string sceneName, std::string filePath);
	Scene&				AddScene(std::string sceneName, Scene& scene);
	void				DeleteScene(std::string name);
	void				DeleteScene(Scene& scene);
	Scene&				GetScene(std::string name);

	inline Scene&		GetCurrentScene() { return *currentScene; }
	void				ChangeName(Scene& scene, std::string newName);
	void				ChangeName(std::string name, std::string newName);

protected:
	Scene*				currentScene;

	std::map<
		std::string,
		Scene* >		sceneMapper;	
};

#endif // OPENGE_SCENEMANAGER_H