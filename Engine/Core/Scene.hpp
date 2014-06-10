#ifndef OPENGE_SCENE_H
#define OPENGE_SCENE_H

#include "Engine/Libraries/Libraries.hpp"
#include <string>
#include <map>

using namespace anax;

class Scene
{
public:
	Scene(std::string name);
	Scene(std::string name, std::string filePath);
	~Scene();

	virtual void				OnActivation();
	virtual void				OnDeactivation();

	virtual void				Update();
	virtual void				Render();

	Entity&						CreateEntity(std::string name);
	void						RenameEntity(std::string name, std::string newName);
	void						DeleteEntity(std::string name);
	Entity&						GetEntity(std::string name);

	std::string					ToString();

public:
	std::string					name;
	std::map<
		std::string,
		Entity* >				entityMapper;

private:
	World						world;
	
};

#endif // OPENGE_SCENE_H