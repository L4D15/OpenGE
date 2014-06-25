#ifndef OPENGE_QUATERNION_H
#define OPENGE_QUATERNION_H

#include "Engine/Core/Math/Vector3.hpp"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float w, const Vector3& v);
	Quaternion(const Quaternion& other);

	Quaternion&				operator=(const Quaternion& other);
	Quaternion 				operator+(const Quaternion& other);
	Quaternion 				operator-(const Quaternion& other);
	Quaternion 				operator*(const Quaternion& other);
	Quaternion 				operator*(const float f);
	Quaternion 				operator/(const float f);

	float					DotProduct(const Quaternion& other);
	float					Length();
	float					LengthQuadratic();
	Quaternion 				Normalized();

	std::string				ToString();

public:
	float w;
	float x;
	float y;
	float z;

};

#endif // OPENGE_QUATERNION_H
