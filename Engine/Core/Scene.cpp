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
	}
	else
	{
		std::stringstream ss;

		ss << "[!] -- Scene::Scene() - Error, JSON file " << jsonFilePath << " couldn't be parsed.";
		Game::Log(ss.str());
	}
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

}

void Scene::Render()
{

}

GameObject& Scene::CreateGameObject(std::string name)
{
	GameObject* gameObject;

	Entity entity = world.createEntity();

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
