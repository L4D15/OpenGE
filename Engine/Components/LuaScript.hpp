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
    LuaScript(json_spirit::Value jsonString);
    virtual ~LuaScript();

    inline std::string             GetClass() const { return className; }
    inline std::string             GetPath() const { return scriptPath; }

protected:
    std::string                     className;
    std::string                     scriptPath;
};

}

#endif // LUASCRIPT_HPP
