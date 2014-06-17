#include "Engine/Core/GameObject.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Components/SpriteRenderer.hpp"
#include "Engine/Core/Game.hpp"
#include <boost/filesystem.hpp>

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
		}
        else if (componentName == "SpriteRenderer")
        {
            std::string spritePath;

            spritePath = jsonArray[compIndex].getObject().at("sprite_path").getString();

            if (boost::filesystem::exists(Game::resourceManager->GetPath(spritePath)) == false)
            {
                std::stringstream ss;

                ss << "-- [!] GameObject::AddComponents() - File " << spritePath << " does not exists.";
                Game::Log(ss.str());
                AddComponent<SpriteRenderer>();
            }
            else
            {
                AddComponent<SpriteRenderer>(spritePath);
            }

        }
	}
}
