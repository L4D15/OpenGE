#include "Engine/Core/GameObject.hpp"
#include "Engine/Components/Transform.hpp"
#include "Engine/Components/SpriteRenderer.hpp"
#include "Engine/Components/Physics.hpp"
#include "Engine/Components/BoxCollider.hpp"
#include "Engine/Core/Game.hpp"
#include <boost/filesystem.hpp>

using namespace Components;

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
        else if (componentName == "Physics")
        {
            AddComponent<Components::Physics>(jsonArray[compIndex].getObject());
        }
        else if (componentName == "BoxCollider")
        {
            AddComponent<Components::BoxCollider>(jsonArray[compIndex].getObject());
        }
    }
}

void GameObject::AddComponent(const string name)
{
    if (name == "Transform")
    {
        AddComponent<Transform>();
    }
    else if (name == "SpriteRenderer")
    {
        AddComponent<SpriteRenderer>();
    }
    else if (name == "Physics")
    {
        AddComponent<Components::Physics>();
    }
}
