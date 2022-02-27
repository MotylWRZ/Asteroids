
#include "Core/Math/MathHelpers.h"
#include "Core/GeometryGenerator.h"
#include "Core/LevelBase.h"
#include "Game/Asteroid.h"

#include "Game/Bullet.h"

Bullet::Bullet()
	:m_MeshVertNum(20)
	,m_BulletShapeRadius(3.0f)
	,m_Speed(430.0f)
	,m_Direction(sf::Vector2f(0.0f, 0.0f))
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialise(LevelBase* Level)
{
	AsteroidsGameObject::Initialise(Level);

	this->m_ObjectMesh = GeometryGenerator::GenerateCircle(sf::Vector2f(0.0f, 0.0f), this->m_BulletShapeRadius, this->m_MeshVertNum);

	this->SetColliderCenter(this->GetPosition());
	this->SetColliderRadius(this->m_BulletShapeRadius);

}

void Bullet::Update(float DeltaTime)
{
	sf::Vector2f tPosition = this->GetPosition();
	sf::Vector2f tWorldSize = static_cast<sf::Vector2f>(this->m_Level->GetWorldSize());

	// Destroy the Bullet if it's out of the screen bounds
	if (tPosition.x > this->m_Level->GetWorldSize().x || tPosition.x < 0.0f
		|| tPosition.y > this->m_Level->GetWorldSize().y || tPosition.y < 0.0f)
	{
		this->m_IsValid = false;
	}

	AsteroidsGameObject::Update(DeltaTime);

	sf::Vector2f tVelocity(0.0f, 0.0f);
	tVelocity =  this->m_Direction;
	tVelocity = MathHelpers::NormalizeVector(tVelocity);
	MathHelpers::SetVectorLength(&tVelocity, this->m_Speed);

	this->m_Position += tVelocity * DeltaTime;

	this->SetColliderCenter(this->GetPosition());
}

void Bullet::OnCollision(Collider2D* Collider)
{
	Asteroid* tAsteroid = dynamic_cast<Asteroid*>(Collider);

	if (!tAsteroid)
	{
		return;
	}

	tAsteroid->DestroyWithExplosion(1.0f, 20.0f);

	this->m_IsValid = false;
	this->SetCollisionEnabled(false);
}
