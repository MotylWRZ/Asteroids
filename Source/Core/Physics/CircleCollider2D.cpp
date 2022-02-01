#include <typeinfo>

#include "Core/Physics/CircleCollider2D.h"

CircleCollider2D::CircleCollider2D()
	:m_Center(sf::Vector2f(0.0f, 0.0f))
	,m_Radius(0.0f)
{
}

CircleCollider2D::~CircleCollider2D()
{
}

bool CircleCollider2D::CollidesWith(Collider2D* Collider)
{
	if (!Collider || !this->IsCollisionEnabled())
	{
		return false;
	}

	return Collider->CollidesWith(this);
}

bool CircleCollider2D::CollidesWith(CircleCollider2D* CircleCollider)
{
	if (!CircleCollider || !this->IsCollisionEnabled())
	{
		return false;
	}

	return this->CircleCircleCollision(this->m_Center, this->m_Radius, CircleCollider->GetColliderCenter(), CircleCollider->GetColliderRadius());
}