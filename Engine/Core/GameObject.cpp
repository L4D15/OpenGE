#include "Engine/Core/GameObject.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Core/Game.hpp"

/**
@brief		Parses the json list provided and adds the corresponding components to the object.
@jsonString	Json text with a list of components and their values.
*/
void GameObject::AddComponents(json_spirit::Array jsonArray)
{
	for (unsigned int compIndex = 0; compIndex < jsonArray.size(); ++compIndex)
	{
		std::string componentName;
		componentName = jsonArray[compIndex].getObject().at("name").getString();

		if (componentName == "Transform")
		{
			AddComponent<Transform>(jsonArray[compIndex].getObject());
			Game::Log(GetComponent<Transform>().ToString());
		}
	}
}