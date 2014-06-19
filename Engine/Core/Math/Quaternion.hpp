#ifndef OPENGE_QUATERNION_H
#define OPENGE_QUATERNION_H

#include "Engine/Core/Math/Vector3.hpp"
#include <luabind/scope.hpp>
#include <luabind/operator.hpp>

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

    static luabind::scope   RegisterForScripting()
    {
        return
                luabind::class_<Quaternion>("Quaternion")
                    .def(luabind::constructor<>())
                    .def(luabind::constructor<float, float, float, float>())
                    .def(luabind::constructor<float, Vector3&>())
                    .def(luabind::constructor<Quaternion&>())
                    .def(luabind::self + Quaternion())
                    .def(luabind::self - Quaternion())
                    .def(luabind::self * Quaternion())
                    .def(luabind::self * float())
                    .def("DotProduct", &Quaternion::DotProduct)
                    .def("Length", &Quaternion::Length)
                    .def("LengthQuadratic", &Quaternion::LengthQuadratic)
                    .def("Normalized", &Quaternion::Normalized)
                    .def("ToString", &Quaternion::ToString)
                ;
    }

public:
	float w;
	float x;
	float y;
	float z;

};

#endif // OPENGE_QUATERNION_H
