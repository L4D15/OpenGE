#ifndef OPENGE_COMPONENT_H
#define OPENGE_COMPONENT_H

#include "Engine/Libraries/Libraries.hpp"

class GameObject;

class Component : public anax::Component
{
public:
	Component(GameObject& owner) : anax::Component(), owner(owner) { }
	virtual ~Component() {}

protected:
	GameObject& owner;
};

#endif // OPENGE_COMPONENT_H