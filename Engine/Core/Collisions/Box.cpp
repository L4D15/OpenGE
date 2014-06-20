#include "Engine/Core/Collisions/Box.hpp"
#include "Engine/Libraries/Libraries.hpp"
#include <sstream>

Box::Box(const float x, const float y, const float width, const float height)
: 	offsetX(x), offsetY(y),
	width(width), height(height)
{

}

Box::~Box()
{

}

bool Box::Collides(const Vector3& pos, const Box& other, const Vector3& otherPos) const
{
    SDL_Rect a;

    a.x = pos.x + offsetX;
    a.y = pos.y + offsetY;
    a.w = width;
    a.h = height;

    SDL_Rect b;

    b.x = otherPos.x + other.offsetX;
    b.y = otherPos.y + other.offsetY;
    b.w = width;
    b.h = height;

    if ((a.x + a.w) < b.x || a.x > (b.x + b.w))
    {
        return false;
    }

    if ((a.y + a.h) < b.y || a.y > (b.y + b.h))
    {
        return false;
    }

    return true;
}

std::string Box::ToString()
{
	std::stringstream ss;

	ss << "[ (" << offsetX << "," << offsetY << ") + {" << width << "," << height << "} ]";

	return ss.str();
}