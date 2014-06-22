#ifndef OPENGE_SCRIPT_H
#define OPENGE_SCRIPT_H

#include "Engine/Libraries/Libraries.hpp"
#include <vector>
#include <list>
#include <luabind/luabind.hpp>

class GameObject;

using namespace anax;

namespace Components
{
class Script : public anax::Component<Script>
{
public:
    Script();
    Script(const std::string scriptPath);
    Script(const std::list<std::string> &scriptsPath);
    Script(GameObject* owner, const std::string scriptPath);
    Script(json_spirit::Value jsonString);
    ~Script();

    void                    Update() const;
    void                    Start() const;
    void                    OnCollision(anax::Entity& collided) const;
    void                    SetOwner(GameObject* object) { owner = object; }

    std::string				ToString();

    static luabind::scope   RegisterForScripting()
    {
        return
                luabind::class_<Script>("Script")
                    .def(luabind::constructor<>())
                    .def(luabind::constructor<std::string>())
                ;
    }

public:
    GameObject*             owner;

protected:
    std::vector
    <std::string>           scripts;

    std::vector
    <std::string>           classNames;
};
}

#endif // OPENGE_SCRIPT_H
