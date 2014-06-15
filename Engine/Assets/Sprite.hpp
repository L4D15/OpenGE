#ifndef OPENGE_SPRITE_H
#define OPENGE_SPRITE_H

#include "Engine/Assets/RenderizableAsset.hpp"

class ResourceManager;

class Sprite : public RenderizableAsset
{
protected:
	Sprite(const std::string name, const std::string filePath);
	virtual ~Sprite();

	virtual void Render(const Vector3& pos, const Quaternion& rot, const Vector3& scale) const;

	friend class ResourceManager;
};


#endif // OPENGE_SPRITE_H