#ifndef OPENGE_SCRIPT_H
#define OPENGE_SCRIPT_H

#include "Engine/Libraries/Libraries.hpp"
#include <list>

using namespace anax;

namespace Components
{
class Script : public Component<Script>
{
public:
	Script();
	Script(std::string scriptPath);
	Script(std::list<std::string> scriptsPath);
	~Script();

protected:

};
}

#endif // OPENGE_SCRIPT_H