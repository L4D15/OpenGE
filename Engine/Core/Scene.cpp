#include "Engine/Core/Scene.hpp"
#include "Engine/Core/Game.hpp"
#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Components/Transform.hpp"
#include <fstream>
#include <sstream>

using namespace anax;

Scene::Scene(std::string name)
: name(name)
{
    world.addSystem(spriteRendering);
    world.addSystem(physics);
    world.addSystem(scriptProcessing);
    world.addSystem(collisions);
}

/**
@brief	Loads the Scene from a JSON file
*/
Scene::Scene(std::string name, std::string filePath)
: name(name)
{
	std::fstream file;
	std::string jsonFilePath;
	json_spirit::Value root;

	jsonFilePath = filePath;

	bool bParsed;

	file.open(jsonFilePath.c_str());

	bParsed = json_spirit::read(file, root);

	if (bParsed == true)
	{
		json_spirit::Array objectList;

		objectList = root.getObject().at("objects").getArray();

		unsigned int numberOfObjects;

		numberOfObjects = objectList.size();

		std::string objectName;
		json_spirit::Array components;

		for (unsigned int index = 0; index < numberOfObjects; ++index)
		{
			objectName = objectList[index].getObject().at("name").getString();
			GameObject& object = CreateGameObject(objectName);
			components = objectList[index].getObject().at("components").getArray();

			object.AddComponents(components);
		}

        // Parse Key bidings
        json_spirit::Array keyBindingArray;
        keyBindingArray = root.getObject().at("key_bindings").getArray();

        std::string buttonName;
        std::string keyName;
        for (unsigned int index = 0; index < keyBindingArray.size(); ++index)
        {
            buttonName = keyBindingArray[index].getObject().at("button").getString();
            keyName = keyBindingArray[index].getObject().at("key").getString();

            Game::input->MapButton(buttonName, keyName);
        }
	}
	else
	{
		std::stringstream ss;

		ss << "[!] -- Scene::Scene() - Error, JSON file " << jsonFilePath << " couldn't be parsed.";
		Game::Log(ss.str());
	}
    file.close();

    // Add systems to world
    world.addSystem(spriteRendering);
    world.addSystem(physics);
    world.addSystem(scriptProcessing);
    world.addSystem(collisions);
}

Scene::Scene(const Scene &other)
{
    name = other.name;
    objectMapper = other.objectMapper;
}

Scene::~Scene()
{

}

void Scene::OnActivation()
{

}

void Scene::OnDeactivation()
{

}

void Scene::Update()
{
    world.refresh();
    physics.Update();
    scriptProcessing.Update();
    collisions.Update();
}

void Scene::Render()
{
    spriteRendering.Render();
}

GameObject& Scene::CreateGameObject(std::string name)
{
	GameObject* gameObject;

	Entity entity = world.createEntity();

    entity.activate();

	gameObject = new GameObject(name, entity);

	std::pair<std::string, GameObject* > mappedObject(name, gameObject);

	objectMapper.insert(mappedObject);

	return *gameObject;
}

void Scene::RenameGameObject(std::string name, std::string newName)
{
	GameObject& object = Find(name);
	DeleteGameObject(name);

	std::pair<std::string, GameObject* > mappedObject(newName, &object);
	objectMapper.insert(mappedObject);
}

void Scene::DeleteGameObject(std::string name)
{
	std::map<std::string, GameObject*>::iterator mappedObject;

	mappedObject = objectMapper.find(name);

	if (mappedObject != objectMapper.end())
	{
		GameObject* object = mappedObject->second;
		objectMapper.erase(mappedObject);
		delete object;
	}
}

GameObject& Scene::Find(std::string name)
{
	return (*(objectMapper.find(name)->second));
}

std::string Scene::ToString()
{
	stringstream ss;

	ss << name << "[ ";

	std::map<std::string, GameObject* >::iterator object;
	for (object = objectMapper.begin(); object != objectMapper.end(); ++object)
	{
		ss << object->first << " / ";
	}

	ss << " ]" << std::endl;

	return ss.str().c_str();
}

GameObject& Scene::Find(anax::Entity& entity) const
{
    for (auto& object : objectMapper)
    {
        if (object.second->entity == entity)
        {
            return *object.second;
        }
    }
}

using namespace luabind;

scope Scene::RegisterForScripting()
{
    return
            class_<Scene>("Scene")
                .def("CreateGameObject", &Scene::CreateGameObject)
            ;
}
