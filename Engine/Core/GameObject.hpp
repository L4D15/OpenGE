#ifndef OPENGE_GAMEOBJECT_H
#define OPENGE_GAMEOBJECT_H

#include "Engine/Libraries/Libraries.hpp"
#include <string>
#include <type_traits>

class GameObject : anax::Entity
{
public:
	GameObject(std::string name) : Entity(), name(name) { }
	GameObject(std::string name, const Entity& entity) : Entity(entity), name(name) { }

	template <typename T, typename... Args>
	T& AttachComponent(Args&&... args)
	{
		return Entity::addComponent<T>(*this, args...);
	}
	
protected:
	std::string name;	
};

#endif // OPENGE_GAMEOBJECT_H