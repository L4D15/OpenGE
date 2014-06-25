#ifndef OPENGE_SCENE_H
#define OPENGE_SCENE_H

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Core/GameObject.hpp"
#include "Engine/Systems/SpriteRendering.hpp"
#include "Engine/Systems/Physics.hpp"
#include "Engine/Systems/Collisions.hpp"
#include <string>
#include <map>

using namespace anax;
using namespace Systems;

class Scene
{
public:
	Scene(std::string name);
	Scene(std::string name, std::string filePath);
    Scene(const Scene& other);
    virtual ~Scene();

	virtual void				OnActivation();
	virtual void				OnDeactivation();

	virtual void				Update();
	virtual void				Render();

	GameObject&					CreateGameObject(std::string name);
	void						RenameGameObject(std::string name, std::string newName);
	void						DeleteGameObject(std::string name);
	GameObject&					Find(std::string name);
    GameObject&                 Find(const anax::Entity& entity) const;

	std::string					ToString();

public:
	std::string					name;
	std::map<
		std::string,
		GameObject* >			objectMapper;

private:
	World						world;

    // Basic Systems
    SpriteRendering             spriteRendering;
    Physics                     physics;
    Collisions                  collisions;
	
};

#endif // OPENGE_SCENE_H
