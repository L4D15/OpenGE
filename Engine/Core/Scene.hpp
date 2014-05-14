#ifndef OPENGE_SCENE_H
#define OPENGE_SCENE_H

#include "Engine/Libraries/Libraries.hpp"
#include <list>

class Scene
{
public:
	Scene();
	~Scene();

	virtual void				OnActivation();
	virtual void				OnDeactivation();

	void						Update();
	void						Render();

protected:

	
};

#endif // OPENGE_SCENE_H