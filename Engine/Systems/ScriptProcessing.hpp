#ifndef OPENGE_SYSTEMS_SCRIPTPROCESSING_H
#define OPENGE_SYSTEMS_SCRIPTPROCESSING_H

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Components/Script.hpp"

namespace Systems
{

class ScriptProcessing : public anax::System<ScriptProcessing>
{
public:
	ScriptProcessing();
	virtual ~ScriptProcessing();

	void				Update() const;
	void				onEntityAdded(anax::Entity& entity);

protected:
	bool				SetContext(Components::Script& script) const;
};

}
#endif // OPENGE_SYSTEMS_SCRIPTPROCESSING_H
