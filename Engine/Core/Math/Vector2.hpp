#ifndef OPENGE_VECTOR2D_H
#define	OPENGE_VECTOR2D_H

#include <string>

class Vector3;

class Vector2 {
public:
    Vector2();
    Vector2(float getX, float getY);
    Vector2(const Vector2& orig);
    ~Vector2();

    Vector2&            operator=(const Vector2& vector);
    Vector2             operator+(const Vector2& vector);
    Vector2             operator*(float f);
    Vector2             operator-(const Vector2& vector);
    bool                operator!=(const Vector2& vector);
    bool                operator==(const Vector2& vector);
    float               DotProduct(const Vector2& vector);
    Vector2             operator*(const Vector2& vector);

    inline float        GetX() { return x; }
    inline float        GetY() { return y; }

    inline void         SetX(float x) { this->x = x; }
    inline void         SetY(float y) { this->y = y; }

    float               LengthQuadratic();
    float               Length();
    float               DistanceQuadratic(const Vector2& vector);
    float               Distance(const Vector2& vector);

    Vector2             Normalized();

    Vector3             ToVector3D();

    std::string         ToString();

public:
    float               x;
    float               y;

};

#endif	/* OPENGE_VECTOR2D_H */

