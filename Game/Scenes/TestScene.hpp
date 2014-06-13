#ifndef OPENGE_TESTSCENE_H
#define OPENGE_TESTSCENE_H

#include "Engine/Core/Scene.hpp"
#include "Engine/Core/GameObject.hpp"
#include "Engine/Components/Transform.hpp"

class TestScene : public Scene
{
public:
	TestScene() : Scene("TestScene") { }

	void OnActivation()
	{
		Entity entity = CreateEntity("Object");
		GameObject object("Object", entity);
		object.AttachComponent<Transform>(1.0, 1.0, 1.0);
	}

	virtual ~TestScene() { }
	
};

#endif // OPENGE_TESTSCENE_H