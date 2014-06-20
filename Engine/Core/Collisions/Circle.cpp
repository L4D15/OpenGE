#include "Engine/Core/Collisions/Circle.hpp"
#include "Engine/Libraries/Libraries.hpp"
#include "Engine/Core/Math/Vector2.hpp"

bool Circle::Collides(const Vector3& pos, const Circle& other, const Vector3& otherPos)
{
    Vector2 pointA(pos.x + offsetX, pos.y + offsetY);
    Vector2 pointB(otherPos.x + other.offsetX, otherPos.y + other.offsetY);

    float distance;

    distance = pointA.Distance(pointB);

    if (distance < (radius + other.radius))
    {
        return true;
    }
    return false;
}