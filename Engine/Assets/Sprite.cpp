#include "Engine/Assets/Sprite.hpp"
#include <sstream>

Sprite::Sprite(const std::string name, const std::string filePath)
: RenderizableAsset(name, filePath)
{

}

Sprite::~Sprite()
{

}

void Sprite::Render(const Vector3& pos, const Quaternion& rot, const Vector3& scale) const
{

}

std::string Sprite::ToString() const
{
	std::stringstream ss;

	ss << "-- [#] " << name << " @ " << filePath;

	return ss.str();
}