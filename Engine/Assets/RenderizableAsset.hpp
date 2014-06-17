#ifndef OPENGE_RENDERIZABLEASSET_H
#define OPENGE_RENDERIZABLEASSET_H

#include "Engine/Assets/Asset.hpp"
#include "Engine/Core/Math/Vector3.hpp"
#include "Engine/Core/Math/Quaternion.hpp"

class RenderizableAsset : public Asset
{
protected:
	RenderizableAsset(const std::string name, const std::string filePath) : Asset(name, filePath) { }
	virtual ~RenderizableAsset() { }

public:
	virtual void			Render (const Vector3& pos, const Quaternion& rot, const Vector3& scale) const = 0;

};

#endif // OPENGE_RENDERIZABLEASSET_H