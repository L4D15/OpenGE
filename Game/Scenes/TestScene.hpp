#ifndef OPENGE_TESTSCENE_H
#define OPENGE_TESTSCENE_H

#include "Engine/Core/Scene.hpp"
#include "Engine/Core/GameObject.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Components/SpriteRenderer.hpp"
#include "Engine/Components/Script.hpp"
#include "Engine/Assets/Sprite.hpp"
#include "Engine/Core/Game.hpp"

using namespace Components;

class TestScene : public Scene
{
public:
    TestScene()
    : Scene("TestScene"),
      object(CreateGameObject("Object")),
      object2(CreateGameObject("Object2"))
    { }

	void OnActivation()
	{
        object.AddComponent<Transform>(12.0f, 16.0f, 1.0f);
        object.AddComponent<SpriteRenderer>("Assets/Sprites/template.png");
        Script& script = object.AddComponent<Script>(&object, "Assets/Scripts/FixedMovement.lua");
        
        object2.AddComponent<Transform>(36.0f, 36.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 2.0f, 2.0f);
        object2.AddComponent<SpriteRenderer>("Assets/Sprites/template.png");
        Script& script2 = object2.AddComponent<Script>(&object2, "Assets/Scripts/Test.lua");
	}

    void Update()
    {
        Scene::Update();
    }

	virtual ~TestScene() { }

    GameObject& object;
    GameObject& object2;
	
};

#endif // OPENGE_TESTSCENE_H
