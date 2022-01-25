
#include "Core/Math/MathHelpers.h"
#include "Core/GeometryGenerator.h"

#include "Game/Bullet.h"

Bullet::Bullet()
	:m_MeshVertNum(20)
	, m_BulletShapeRadius(3.0f)
	, m_Speed(400.0f)
	, m_Direction(sf::Vector2f(0.0f, 0.0f))
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialise(LevelBase* Level)
{
	GameObject::Initialise(Level);

	this->m_ObjectMesh = GeometryGenerator::GenerateCircle(sf::Vector2f(0.0f, 0.0f), this->m_BulletShapeRadius, this->m_MeshVertNum);
}

void Bullet::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);

	sf::Vector2f tVelocity(0.0f, 0.0f);
	tVelocity =  this->m_Direction;
	tVelocity = MathHelpers::NormalizeVector(tVelocity);
	MathHelpers::SetVectorLength(&tVelocity, this->m_Speed);

	this->m_Position += tVelocity * DeltaTime;
}
