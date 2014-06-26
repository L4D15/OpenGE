#ifndef OPENGE_TESTSCENE_H
#define OPENGE_TESTSCENE_H

#include "Engine/Core/Scene.hpp"
#include "Engine/Core/GameObject.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Components/SpriteRenderer.hpp"
#include "Engine/Components/BoxCollider.hpp"
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
        // Map keys
        Game::input->MapButton("Walk Right",    "Arrow Right");
        Game::input->MapButton("Walk Left",     "Arrow Left");
        Game::input->MapButton("Walk Up",       "Arrow Up");
        Game::input->MapButton("Walk Down",     "Arrow Down");

        object.AddComponent<Transform>(12.0f, 16.0f, 1.0f);
        object.AddComponent<SpriteRenderer>("Assets/Sprites/template.png");
        object.AddComponent<BoxCollider>(0.0f, 0.0f, 24.0f, 32.0f);

        object2.AddComponent<Transform>(48.0f, 16.0f, 1.0f);
        object2.AddComponent<SpriteRenderer>("Assets/Sprites/template.png");
        object2.AddComponent<BoxCollider>(0.0f, 0.0f, 24.0f, 32.0f);
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
