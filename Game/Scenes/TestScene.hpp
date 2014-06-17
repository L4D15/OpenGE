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
    TestScene() : Scene("TestScene"), object(CreateGameObject("Object")) { }

	void OnActivation()
	{
        object.AddComponent<Transform>(12.0f, 16.0f, 1.0f);
	}

	virtual ~TestScene() { }

    void Render()
    {
        
    }
    GameObject& object;
	
};

#endif // OPENGE_TESTSCENE_H
