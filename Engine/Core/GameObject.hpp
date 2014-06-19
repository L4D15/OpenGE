#ifndef OPENGE_GAMEOBJECT_H
#define OPENGE_GAMEOBJECT_H

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Components/Transform.hpp"
#include <string>
#include <type_traits>

class GameObject
{
protected:
	GameObject(std::string name, const anax::Entity& entity) : name(name), entity(entity) { }

public:
    virtual ~GameObject() {}
	
    template <typename T, typename... Args>
    T&                      AddComponent(Args&&... args) { return entity.addComponent<T>(new T{std::forward<Args>(args)...}); }

	template <typename T>
    T&                      GetComponent() const { return entity.getComponent<T>(); }

	template <typename T>
    void                    RemoveComponent() { entity.removeComponent<T>(); }

	template <typename T>
    bool                    HasComponent() const { return entity.hasComponent<T>(); }

    void                    AddComponents(json_spirit::Array jsonArray);
    void                    AddComponent(const std::string name);

    Components::Transform&  GetTransform() { return GetComponent<Components::Transform>(); }

    inline void             Activate() { entity.activate(); }
    inline void             Deactivate() { entity.deactivate(); }

    static luabind::scope   RegisterForScripting();

    const std::string       GetName() const { return name; }
    void                    SetName(std::string name) { this->name = name; }

public:
    std::string             name;

protected:
    anax::Entity            entity;

	friend class Scene;
};

#endif // OPENGE_GAMEOBJECT_H
