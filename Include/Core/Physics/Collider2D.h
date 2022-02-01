#pragma once

#include "SFML/Graphics.hpp"

//Forward Declarations
class CircleCollider2D;

class Collider2D
{
public:
	Collider2D();
	virtual ~Collider2D();

	virtual void OnCollision(Collider2D* Collider) = 0;
	inline void SetCollisionEnabled(bool CollisionEnabled) { this->m_CollisionEnabled = CollisionEnabled; }
	inline bool IsCollisionEnabled() { return this->m_CollisionEnabled;
	}
	////////////////////////////////////////////////////////////
	// Functions to be implemented by derived collision classes
	////////////////////////////////////////////////////////////
	virtual bool CollidesWith(Collider2D* Collider) = 0;
	virtual bool CollidesWith(CircleCollider2D* CircleCollider) = 0;

	virtual bool CircleCircleCollision(const sf::Vector2f& CircleACenter, float CircleARadius
									 , const sf::Vector2f& CircleBCenter, float CircleBRadius);

private:
	bool m_CollisionEnabled;
};

