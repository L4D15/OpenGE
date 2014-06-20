#ifndef OPENGE_SCRIPTING_H
#define OPENGE_SCRIPTING_H

#include <string>
#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Core/GameObject.hpp"

class Scripting
{
public:
	Scripting();
	~Scripting();

    bool                Execute(std::string script);

    void                CreateEnvironment();

    template<class T>
    void                SetGlobal(const std::string name, const T& value)
    {
        luabind::globals(state)[name.c_str()] = value;
    }

    void                CallFunction(const std::string function, const std::string className, const std::string scriptPath) const;
    void                OnCollision(const std::string className, const std::string scriptPath, GameObject& collided) const;

    lua_State*          GetState() const { return state; }

private:
    lua_State*          state;
};

#endif // OPENGE_SCRIPTING_H
