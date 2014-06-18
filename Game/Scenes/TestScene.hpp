#ifndef OPENGE_TESTSCENE_H
#define OPENGE_TESTSCENE_H

#include "Engine/Core/Scene.hpp"
#include "Engine/Core/GameObject.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Components/SpriteRenderer.hpp"
#include "Engine/Assets/Sprite.hpp"
#include "Engine/Core/Game.hpp"

using namespace Components;

class TestScene : public Scene
{
public:
    TestScene() : Scene("TestScene"), object(CreateGameObject("Object")) { }

	void OnActivation()
	{
        object.AddComponent<Transform>(12.0f, 16.0f, 1.0f);
        object.AddComponent<SpriteRenderer>("Assets/Sprites/template.png");
	}

	virtual ~TestScene() { }

    GameObject& object;
	
};

#endif // OPENGE_TESTSCENE_H
