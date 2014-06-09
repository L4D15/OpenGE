#include "Engine/Core/Scene.hpp"
#include "Engine/Core/Game.hpp"
#include "Engine/Libraries/Libraries.hpp"
#include <fstream>

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
		json_spirit::Array entities;

		entities = root.getObject().at("entities").getArray();

		unsigned int numberOfEntities;

		numberOfEntities = entities.size();

		Entity entity;
		std::string entityName;
		for (unsigned int index = 0; index < numberOfEntities; ++index)
		{
			entityName = entities[index].getObject().at("name").getString();
			CreateEntity(entityName);
		}
	}
	else
	{
		Game::Log("Scene::Scene() - Error, JSON file couldn't be parsed");
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

Entity& Scene::CreateEntity(std::string name)
{
	Entity* entity;

	entity = new Entity(world.createEntity());

	std::pair<std::string, Entity* > mappedEntity(name, entity);

	entityMapper.insert(mappedEntity);

	return *entity;
}

void Scene::RenameEntity(std::string name, std::string newName)
{
	Entity& entity = GetEntity(name);
	DeleteEntity(name);

	std::pair<std::string, Entity* > mappedEntity(newName, &entity);
	entityMapper.insert(mappedEntity);
}

void Scene::DeleteEntity(std::string name)
{
	std::map<std::string, Entity*>::iterator mappedEntity;

	mappedEntity = entityMapper.find(name);

	if (mappedEntity != entityMapper.end())
	{
		Entity* entity = mappedEntity->second;
		entityMapper.erase(mappedEntity);
		delete entity;
	}
}

Entity& Scene::GetEntity(std::string name)
{
	return (*(entityMapper.find(name)->second));
}

std::string Scene::ToString()
{
	stringstream ss;

	ss << name << "[ ";

	std::map<std::string, Entity* >::iterator entity;
	for (entity = entityMapper.begin(); entity != entityMapper.end(); ++entity)
	{
		ss << entity->first << " / ";
	}

	ss << " ]" << std::endl;

	return ss.str().c_str();
}
