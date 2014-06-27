#ifndef OPENGE_SYSTEMS_LUASCRIPTING_H
#define OPENGE_SYSTEMS_LUASCRIPTING_H

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Components/LuaScript.hpp"

namespace Systems
{

class LuaScripting : public anax::System<LuaScripting> {
public:
    LuaScripting();
    virtual ~LuaScripting();

    void CreateEnvironment();
    void ProcessEntities();


private:
    void RegisterClass(const std::string scriptPath);
    void RegisterObject(const anax::Entity& object);
    void CreateInstance(const std::string className, const anax::Entity& owner);
    void RunFunction(const std::string function, const std::string className, const anax::Entity& owner);

    void onEntityAdded(anax::Entity& entity);
    void onEntityRemoved(anax::Entity& entity);

    template <class T>
    void SetGlobal(const std::string name, const T& value);


protected:
    lua_State*			luaState;

};

}

#endif // OPENGE_SYSTEMS_LUASCRIPTING_H