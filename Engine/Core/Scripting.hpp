#ifndef OPENGE_SCRIPTING_H
#define OPENGE_SCRIPTING_H

#include <string>
#include "Engine/Libraries/Libraries.hpp"

class Scripting
{
public:
	Scripting();
	~Scripting();

	bool Execute(std::string script);

	void CreateEnvironment();

private:
	lua_State* state;
};

#endif // OPENGE_SCRIPTING_H
