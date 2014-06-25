#ifndef OPENGE_LUASCRIPT_HPP
#define OPENGE_LUASCRIPT_HPP

#include "Engine/Libraries/Libraries.hpp"

namespace Components
{

class LuaScript : public anax::Component<LuaScript>
{
public:
    LuaScript();
    LuaScript(const std::string className, const std::string path);
    virtual ~LuaScript();

protected:
    std::string className;
    std::string scriptPath;
};

}

#endif // LUASCRIPT_HPP
