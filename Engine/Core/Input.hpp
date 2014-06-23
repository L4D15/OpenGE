#ifndef OPENGE_INPUT_H
#define OPENGE_INPUT_H

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Core/Time.hpp"
#include <map>

class EventManager;

class Key
{
public:
    Key(const std::string name, Sint32 keycode) : name(name), keycode(keycode)
    {
        timePressed = 0;
        timeReleased = 0;
    }
	virtual ~Key() { }

	void					NotifyPressed() { timePressed = Time::GetTime(); }
	void					NotifyReleased() { timeReleased = Time::GetTime(); }

    std::string             ToString()
    {
        std::stringstream ss;
        ss << name << " { push: " << timePressed << " relese: " << timeReleased << "}";
        return ss.str();
    }

	static luabind::scope	RegisterForScripting()
	{
		return
				luabind::class_<Key>("Key")
                    .def(luabind::constructor<std::string, SDL_Keycode>())
					.def("NotifyPressed", &Key::NotifyPressed)
					.def("NotifyReleased", &Key::NotifyReleased)
					.def_readwrite("name", &Key::name)
					.def_readwrite("keycode", &Key::keycode)
					.def_readonly("timePressed", &Key::timePressed)
					.def_readonly("timeReleased", &Key::timeReleased)
                ;
	}

public:
    std::string             name;
    SDL_Keycode             keycode;

    Uint32                  timePressed;
    Uint32                  timeReleased;

};

class ButtonMapping
{
public:
    ButtonMapping(const std::string buttonName, Key* key)
    : buttonName(buttonName), key(key)
    {

    }

    ~ButtonMapping() {}

    static luabind::scope   RegisterForScripting()
    {
        return
                luabind::class_<ButtonMapping>("ButtonMapping")
                    .def(luabind::constructor<std::string, Key*>())
                    .def_readwrite("buttonName", &ButtonMapping::buttonName)
                    .def_readonly("key", &ButtonMapping::key)
                ;
    }

    std::string         buttonName;
    Key*                key;
};

class Input
{
public:
	Input();
    Input(const Input& other);
	~Input();

	void					MapButton(const std::string button, const std::string keyName);
    bool                    GetButton(const std::string name);
    Uint32                  GetButtonPressTime(const std::string name);
    Uint32                  GetButtonReleaseTime(const std::string name);
    Uint32                  GetButtonHoldTime(const std::string name);

    std::string             ToString() const;

	static luabind::scope	RegisterForScripting()
	{
        return
                luabind::class_<Input>("Input")
                    .def("MapButton", &Input::MapButton)
                    .def("GetButton", &Input::GetButton)
                    .def("GetButtonPressTime", &Input::GetButtonPressTime)
                    .def("GetButtonReleaseTime", &Input::GetButtonReleaseTime)
                    .def("ToString", &Input::ToString)
                ;
    }

protected:
    void                    NotifyKeyPress(const SDL_Keycode key);
    void                    NotifyKeyRelease(const SDL_Keycode key);

protected:
    std::vector<Key*>		keyList;

    std::vector<ButtonMapping*> mappings;

    ButtonMapping*          SearchButtonMapping(const std::string button);

    friend class EventManager;

};

#endif // OPENGE_INPUT_H
