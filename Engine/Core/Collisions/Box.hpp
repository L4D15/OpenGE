#ifndef OPENGE_COLLISIONS_BOX_H
#define OPENGE_COLLISIONS_BOX_H

#include "Engine/Core/Math/Vector3.hpp"
#include <luabind/luabind.hpp>

class Box
{
public:
	Box(const float x, const float y, const float width, const float height);
	virtual ~Box();

	bool					Collides(const Vector3& pos, const Box& other, const Vector3& otherPos) const;

	std::string				ToString();

public:
	float					offsetX;
	float					offsetY;
	float					width;
	float					height;	
};

#endif // OPENGE_COLLISIONS_BOX_H
