#ifndef OPENGE_TESTSCENE_H
#define OPENGE_TESTSCENE_H

#include "Engine/Core/Scene.hpp"
#include "Engine/Core/GameObject.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Assets/Sprite.hpp"
#include "Engine/Core/Game.hpp"

class TestScene : public Scene
{
public:
	TestScene() : Scene("TestScene") { }

	void OnActivation()
	{
		GameObject& object = CreateGameObject("Object");

		object.AddComponent<Transform>(1.0f, 1.0f, 1.0f);
	}

	virtual ~TestScene() { }
	
};

#endif // OPENGE_TESTSCENE_H
