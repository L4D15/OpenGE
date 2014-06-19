#ifndef OPENGE_SYSTEMS_SCRIPTPROCESSING_H
#define OPENGE_SYSTEMS_SCRIPTPROCESSING_H

#include "Engine/Libraries/Libraries.hpp"

namespace Systems
{

class ScriptProcessing : public anax::System<ScriptProcessing>
{
public:
	ScriptProcessing();
	virtual ~ScriptProcessing();

	void				Update() const;	
};

}
#endif // OPENGE_SYSTEMS_SCRIPTPROCESSING_H