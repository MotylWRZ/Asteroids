#pragma once

#include "SFML/Graphics.hpp"

class Collider2D
{
public:
	Collider2D();
	virtual ~Collider2D();

	virtual void OnCollision(Collider2D* Collider) = 0;

	////////////////////////////////////////////////////////////
	// Functions to be implemented by derived collision classes
	////////////////////////////////////////////////////////////
	virtual bool CollidesWith(Collider2D* Collider) = 0;

	virtual bool CircleCircleCollision(const sf::Vector2f& CircleACenter, float CircleARadius
									 , const sf::Vector2f& CircleBCenter, float CircleBRadius);
};

