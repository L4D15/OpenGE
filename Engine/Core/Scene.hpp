#ifndef OPENGE_SCENE_H
#define OPENGE_SCENE_H

#include "Engine/Libraries/Libraries.hpp"
#include <string>
#include <list>

class Scene
{
public:
	Scene(std::string name);
	~Scene();

	virtual void				OnActivation();
	virtual void				OnDeactivation();

	void						Update();
	void						Render();

public:
	std::string					name;
	
};

#endif // OPENGE_SCENE_H