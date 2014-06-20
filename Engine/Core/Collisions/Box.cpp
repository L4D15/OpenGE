#include "Engine/Core/Collisions/Box.hpp"
#include <sstream>

Box::Box(const float x, const float y, const float width, const float height)
: 	offsetX(x), offsetY(y),
	width(width), height(height)
{

}

Box::~Box()
{

}

bool Box::Collides(const Box& other) const
{

}

std::string Box::ToString()
{
	std::stringstream ss;

	ss << "[ (" << offsetX << "," << offsetY << ") + {" << width << "," << height << "} ]";

	return ss.str();
}