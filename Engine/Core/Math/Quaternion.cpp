#include "Engine/Core/Math/Quaternion.hpp"
#include "Engine/Core/Math/Math.hpp"
#include <sstream>

Quaternion::Quaternion()
: w(0.0), x(0.0), y(0.0), z(0.0)
{

}

Quaternion::Quaternion(float w, float x, float y, float z)
: w(w), x(x), y(y), z(z)
{

}

Quaternion::Quaternion(float w, const Vector3& v)
: w(w), x(v.x), y(v.y), z(v.z)
{

}

Quaternion::Quaternion(const Quaternion& other)
: w(other.w), x(other.x), y(other.y), z(other.z)
{

}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
	w = other.w;
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Quaternion Quaternion::operator+(const Quaternion& other)
{
	return Quaternion(w + other.w, x + other.x,	y + other.y, z + other.z);
}

Quaternion Quaternion::operator-(const Quaternion& other)
{
	return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
}

Quaternion Quaternion::operator*(const Quaternion& other)
{
	return Quaternion(w * other.w, x * other.x, y * other.y, z * other.z);
}

Quaternion Quaternion::operator*(const float f)
{
	return Quaternion(w * f, x * f, y * f, z * f);
}

Quaternion Quaternion::operator/(const float f)
{
	return Quaternion(w / f, x / f, y / f, z / f);
}

float Quaternion::DotProduct(const Quaternion& other)
{
	return (w * other.w + x * other.x + y * other.y + z * other.z);
}

float Quaternion::Length()
{
	return math::squareRoot(w * w + x * x + y * y + z * z);
}

float Quaternion::LengthQuadratic()
{
	return (w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::Normalized()
{
	Quaternion normalized;
	float length;

	length = LengthQuadratic();

	if (length == 0)
	{
		normalized.w = 0.0f;
		normalized.x = 0.0f;
		normalized.y = 0.0f;
		normalized.z = 0.0f;
	}
	else
	{
		float recip = math::inverseSquareRoot(length);

		normalized = normalized * recip;
	}

	return normalized;
}

std::string Quaternion::ToString()
{
	std::stringstream ss;

	ss << w << " * " << "(" << x << "," << y << "," << z << ")";

	return ss.str();
}
