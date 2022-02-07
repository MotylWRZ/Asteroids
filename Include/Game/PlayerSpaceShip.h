#pragma once

#include "SFML/Graphics.hpp"

#include "Core/Physics/CircleCollider2D.h"

#include "Game/AsteroidsGameObject.h"

enum class EShipRotation
{
	Rotate_Left,
	Rotate_Right,
	Rotate_None
};

class PlayerSpaceShip : public AsteroidsGameObject
{
public:
	PlayerSpaceShip();
	virtual ~PlayerSpaceShip();

	virtual void Initialise(LevelBase* Level) override;
	virtual void Update(float DeltaTime) override;
	virtual void Render(sf::RenderWindow& RenderWindow) override;
	virtual void HandleInput(sf::Keyboard::Key Key, bool IsPressed) override;

	void Shoot();

	virtual void OnCollision(Collider2D* Collider);

private:
	void RotateShip(float DeltaTime);
	void DrawDebug(sf::RenderWindow& RenderWindow);

private:
	sf::Vector2f m_Velocity;
	float m_ThrustStrength;
	float m_MaxSpeed;

	float m_LinearAcceleration;
	float m_AngularAcceleration;

	float m_BulletDirAngleOffset;
	sf::Vector2f m_BulletPositionOffset;
	float m_ExplosionDuration = 1.0f;
	float m_ExplosionRate = 0.1f;

	std::shared_ptr<sf::CircleShape> m_CircleShape;
	EShipRotation m_ShipRotation;
	float m_Size;
};