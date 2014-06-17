#ifndef OPENGE_SPRITERENDERINGSYSTEM_H
#define OPENGE_SPRITERENDERINGSYSTEM_H

#include "Engine/Libraries/Libraries.hpp"

namespace Systems
{
class SpriteRendering : public anax::System<SpriteRendering>
{
public:
	SpriteRendering();
	virtual ~SpriteRendering();

	void			Render() const;
};	
}


#endif // OPENGE_SPRITERENDERINGSYSTEM_H
