#ifndef OPENGE_GAMEOBJECT_H
#define OPENGE_GAMEOBJECT_H

#include "Engine/Libraries/Libraries.hpp"
#include <string>
#include <type_traits>

class GameObject
{
protected:
	GameObject(std::string name, const anax::Entity& entity) : name(name), entity(entity) { }
	virtual ~GameObject() {}

public:
	template <typename T, typename... Args>
	T&					AddComponent(Args&&... args) { return entity.addComponent<T>(new T{std::forward<Args>(args)...}); }

	template <typename T>
	T&					GetComponent() const { return entity.getComponent<T>(); }

	template <typename T>
	void				RemoveComponent() { entity.removeComponent<T>(); }

	template <typename T>
	bool				HasComponent() const { return entity.hasComponent<T>(); }

	void				AddComponents(json_spirit::Array jsonArray);

protected:
	std::string 		name;
	anax::Entity 		entity;

	friend class Scene;
};

#endif // OPENGE_GAMEOBJECT_H