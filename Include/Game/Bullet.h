#pragma once

#include "Core/Physics/CircleCollider2D.h"

#include "Game/AsteroidsGameObject.h"

class Bullet : public AsteroidsGameObject
{
public:

	Bullet();
	virtual ~Bullet();

	virtual void Initialise(LevelBase* Level) override;
	virtual void Update(float DeltaTime) override;

	inline void SetSpeed(float Speed) { this->m_Speed = Speed; }
	inline void SetDirection(sf::Vector2f& Direction) { this->m_Direction = Direction; }

	inline float GetSpeed() { return this->m_Speed; }
	inline const sf::Vector2f& GetDirection() const { return m_Direction; }

	virtual void OnCollision(Collider2D* Collider) override;

private:
	unsigned int m_MeshVertNum;
	float m_BulletShapeRadius;
	float m_Speed;
	sf::Vector2f m_Direction;
};

