#ifndef OPENGE_VECTOR3D_H
#define OPENGE_VECTOR3D_H

#include <string>
#include <luabind/luabind.hpp>

class Vector2;

class Vector3
{
public:
    Vector3();
    Vector3(float x, float y);
    Vector3(float x, float y, float z);
    Vector3(const Vector3& other);
    ~Vector3();

    Vector3&            operator=(const Vector3& other);
    Vector3             operator+(const Vector3& other);
    Vector3             operator-(const Vector3& other);
    Vector3             operator*(const Vector3& other);
    Vector3             operator*(const float f);
    bool                operator!=(const Vector3& other);
    bool                operator==(const Vector3& other);
    float               DotProduct(const Vector3& other);

    float               LengthQuadratic();
    float               Length();
    float               DistanceQuadratic(const Vector3& other);
    float               Distance(const Vector3& other);

    Vector3             Normalized();

    Vector2             ToVector2D();

    std::string         ToString();

    static
    luabind::scope      RegisterForScripting();

public:
    float               x;
    float               y;
    float               z;
};

#endif // VECTOR3D_H
