#include "Core/Math/MathHelpers.h"

#include "Core/Physics/Collider2D.h"

Collider2D::Collider2D()
    :m_CollisionEnabled(true)
{
}

Collider2D::~Collider2D()
{
}

bool Collider2D::CircleCircleCollision(const sf::Vector2f& CircleACenter, float CircleARadius
    , const sf::Vector2f& CircleBCenter, float CircleBRadius)
{
    sf::Vector2f tDifference = CircleBCenter - CircleACenter;

    float tDistanceSquared = fabs(MathHelpers::GetVectorLength(tDifference));
    tDistanceSquared *= tDistanceSquared;

    float tRadiusSquared = CircleARadius + CircleBRadius;
    tRadiusSquared *= tRadiusSquared;

    if (tDistanceSquared < tRadiusSquared)
    {
        return true;
    }

    return false;
}
