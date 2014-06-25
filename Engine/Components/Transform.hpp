#ifndef OPENGE_TRANSFORM_H
#define OPENGE_TRANSFORM_H

#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Core/Math/Vector3.hpp"
#include "Engine/Core/Math/Quaternion.hpp"

namespace Components
{

class Transform : public anax::Component<Transform>
{
public:
	Transform();
	Transform(float x, float y, float z);
	Transform(float posX, float posY, float posZ, float rotX, float rotY, float rotZ);
	Transform(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float sclX, float sclY, float sclZ);
	Transform(json_spirit::Value jsonString);

	virtual ~Transform();

    std::string             ToString();

public:
    Vector3                 position;
    Quaternion              rotation;
    Vector3                 scale;
};
}

#endif // OPENGE_TRANSFORM_H
