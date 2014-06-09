#include "Engine/Core/Scene.hpp"

using namespace anax;

Scene::Scene(std::string name)
: name(name)
{
	
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
