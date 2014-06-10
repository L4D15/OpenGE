#include "Engine/Components/Transform.hpp"
#include <sstream>

Transform::Transform()
: position(), rotation(), scale(1.0f, 1.0f, 1.0f)
{

}

Transform::Transform(float x, float y, float z)
: position(x, y, z), scale(1.0f, 1.0f, 1.0f)
{

}

// TODO: Create the rotation quaternion from Euler-angles.
Transform::Transform(float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
: position(posX, posY, posZ), /* HERE */ scale(1.0f, 1.0f, 1.0f)
{

}

Transform::Transform(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float sclX, float sclY, float sclZ)
: position(posX, posY, posZ), /* HERE */ scale(sclX, sclY, sclZ)
{

}

Transform::Transform(json_spirit::Value jsonString)
{
	/*
		JSON TEMPLATE FOR TRANSFORM COMPONENT
		{
			"name": "Transform",
			"position":
			{
				"x": 0.0,
				"y": 0.0,
				"z": 0.0
			},
			"rotation":
			{
				"x": 0.0,
				"y": 0.0,
				"z": 0.0
			},
			"scale":
			{
				"x": 1.0,
				"y": 1.0,
				"z": 1.0
			}
		}
	*/
	float posX, posY, posZ;
	float rotX, rotY, rotZ;
	float sclX, sclY, sclZ;

	// Position
	if (jsonString.contains("position"))
	{
		posX = jsonString.getObject().at("position").getObject().at("x").getReal();
		posY = jsonString.getObject().at("position").getObject().at("y").getReal();
		posZ = jsonString.getObject().at("position").getObject().at("z").getReal();
	}
	else
	{
		posX = 0.0f;
		posY = 0.0f;
		posZ = 0.0f;
	}

	// Rotation
	if (jsonString.contains("rotation"))
	{
		rotX = jsonString.getObject().at("rotation").getObject().at("x").getReal();
		rotY = jsonString.getObject().at("rotation").getObject().at("y").getReal();
		rotZ = jsonString.getObject().at("rotation").getObject().at("z").getReal();
	}
	else
	{
		rotX = 0.0f;
		rotY = 0.0f;
		rotZ = 0.0f;
	}

	// Scale
	if (jsonString.contains("scale"))
	{
		sclX = jsonString.getObject().at("scale").getObject().at("x").getReal();
		sclY = jsonString.getObject().at("scale").getObject().at("y").getReal();
		sclZ = jsonString.getObject().at("scale").getObject().at("z").getReal();
	}
	else
	{
		sclX = 1.0f;
		sclY = 1.0f;
		sclZ = 1.0f;
	}

	position.x = posX;
	position.y = posY;
	position.z = posZ;

	//TODO: Update the quaternion using Euler angles

	scale.x = sclX;
	scale.y = sclY;
	scale.z = sclZ;
}

Transform::~Transform()
{

}

std::string Transform::ToString()
{
	std::stringstream ss;

	ss << "Transform::[" << position.ToString() << "; " << rotation.ToString() << "; " << scale.ToString() << "]";

	return ss.str();
}

