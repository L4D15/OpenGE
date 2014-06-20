#ifndef OPENGE_COLLISIONS_BOX_H
#define OPENGE_COLLISIONS_BOX_H

#include "Engine/Core/Math/Vector3.hpp"
#include <luabind/luabind.hpp>

class Box
{
public:
	Box(const float x, const float y, const float width, const float height);
	virtual ~Box();

	bool					Collides(const Box& other) const;

	std::string				ToString();


	static luabind::scope	RegisterForScripting()
	{
		return
			luabind::class_<Box>("Box")
				.def(luabind::constructor<float, float, float, float>())
                .def_readwrite("offsetX", &Box::offsetX)
                .def_readwrite("offsetY", &Box::offsetY)
                .def_readwrite("width", &Box::width)
                .def_readwrite("height", &Box::height)
				.def("Collides", &Box::Collides)
				.def("ToString", &Box::ToString)
			;
	}

public:
	float					offsetX;
	float					offsetY;
	float					width;
	float					height;	
};

#endif // OPENGE_COLLISIONS_BOX_H