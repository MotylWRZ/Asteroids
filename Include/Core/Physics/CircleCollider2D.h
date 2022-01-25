#pragma once
#include "Collider2D.h"
class CircleCollider2D : public Collider2D
{
public:

	CircleCollider2D();
	virtual ~CircleCollider2D();

	virtual bool CollidesWith(Collider2D* Collider) override;
	virtual void OnCollision(Collider2D* Collider) override = 0;

	bool CollidesWith(CircleCollider2D* CircleCollider);

	inline void SetCenter(const sf::Vector2f& Center) { this->m_Center = Center; }
	inline void SetRadius(float Radius) { this->m_Radius = Radius; }

	inline const sf::Vector2f& GetCenter() const { return this->m_Center; }
	inline float GetRadius() { return this->m_Radius; }

private:
	sf::Vector2f m_Center;
	float m_Radius;
};
