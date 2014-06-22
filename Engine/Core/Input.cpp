#include "Engine/Core/Input.hpp"
#include "Engine/Core/Game.hpp"

Input::Input()
{
    keyList.push_back(new Key("Arrow Up", SDLK_UP));
    keyList.push_back(new Key("Arrow Down", SDLK_DOWN));
    keyList.push_back(new Key("Arrow Right", SDLK_RIGHT));
    keyList.push_back(new Key("Arrow Left", SDLK_LEFT));
    keyList.push_back(new Key("Space", SDLK_SPACE));
    // TODO: Add more keys
}

Input::Input(const Input& other)
{
    keyList = other.keyList;
    mappings = other.mappings;
}

Input::~Input()
{

}

void Input::MapButton(const std::string button, const std::string keyName)
{
    Key* key;

    for (Key* currentKey : keyList)
    {
        if (currentKey->name == keyName)
        {
            key = currentKey;
        }
    }

    if (key != NULL)
    {
        ButtonMapping* mapping = new ButtonMapping(button, key);

        mappings.push_back(mapping);
    }
}

bool Input::GetButton(const std::string name)
{
    ButtonMapping* mapping;

    mapping = SearchButtonMapping(name);

    if (mapping != NULL)
    {
        if (mapping->key->timeReleased < mapping->key->timePressed)
        {
            return true;
        }
    }

    return false;
}

Uint32 Input::GetButtonPressTime(const std::string name)
{
    return SearchButtonMapping(name)->key->timePressed;
}

Uint32 Input::GetButtonReleaseTime(const std::string name)
{
    return SearchButtonMapping(name)->key->timeReleased;
}

Uint32 Input::GetButtonHoldTime(const std::string name)
{
    return (Time::GetTime() - SearchButtonMapping(name)->key->timePressed);
}

void Input::NotifyKeyPress(const SDL_Keycode key)
{
    for (auto currentKey : keyList)
    {
        if (currentKey->keycode == key)
        {
            currentKey->NotifyPressed();
        }
    }
}

void Input::NotifyKeyRelease(const SDL_Keycode key)
{
    for (auto currentKey : keyList)
    {
        if (currentKey->keycode == key)
        {
            currentKey->NotifyReleased();
        }
    }
}

std::string Input::ToString() const
{
    std::stringstream ss;

    ss << "Button Mapping:" << std::endl;

    for (auto* mapping : mappings)
    {
        ss << " [ " << mapping->buttonName << " -> " << mapping->key->ToString() << " ]" << std::endl;
    }

    return ss.str();
}

ButtonMapping* Input::SearchButtonMapping(const std::string button)
{
    ButtonMapping* buttonFound = NULL;

    for (unsigned int index = 0; index < mappings.size(); ++index)
    {
        if (mappings[index]->buttonName == button)
        {
            return mappings[index];
        }
    }
    return buttonFound;
}
