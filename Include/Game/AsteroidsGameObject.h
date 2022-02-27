#pragma once
#include "Core/Physics/CircleCollider2D.h"

#include "Core/GameObject.h"

class AsteroidsGameObject : public GameObject, public CircleCollider2D
{
public:

	AsteroidsGameObject();
	virtual ~AsteroidsGameObject();

	virtual void Initialise(LevelBase* Level) override;
	virtual void Update(float DeltaTime) override;
	virtual void Render(sf::RenderWindow& RenderWindow) override;
	virtual void HandleInput(sf::Keyboard::Key Key, bool IsPressed);
	virtual void DebugDraw(sf::RenderWindow& RenderWindow);

	virtual void OnCollision(Collider2D* Collider) override = 0;
	virtual bool CollidesWith(CircleCollider2D* CircleCollider) override;

	virtual void WrapObjectCoordinates();
	virtual void WrapColliderCoordinates();

	virtual void DestroyWithExplosion(float Duration, float Rate);

	inline void SetInputEnabled(bool IsInputEnabled) { this->m_IsInputEnabled = IsInputEnabled; }
	inline void SetDebugDrawEnabled(bool IsDebugDrawEnabled) { this->m_IsDebugDrawEnabled = IsDebugDrawEnabled; }
	inline const bool IsInputEnabled() { return this->m_IsInputEnabled; }
	inline const bool IsDebugDrawEnabled() const { return this->m_IsDebugDrawEnabled; }

protected:
	float m_ExplosionRate;
	float m_ExplosionDuration;
	bool m_CanExplode;

	sf::Vector2f m_ExtendColliderPosition;

	bool m_IsInputEnabled;
	bool m_IsDebugDrawEnabled;
};

