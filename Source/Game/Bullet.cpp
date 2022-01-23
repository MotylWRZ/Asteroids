
#include "Core/Math/MathHelpers.h"

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

	// Generate a list of vertices placed around the object position
	for (unsigned int i = 0; i < this->m_MeshVertNum; i++)
	{
		float tAngle = (static_cast<float>(i) / static_cast<float>(this->m_MeshVertNum)) * PI * 2;
		sf::Vector2f  tVertexPos(this->m_BulletShapeRadius * sinf(tAngle), this->m_BulletShapeRadius * cosf(tAngle));

		this->m_ObjectMesh.push_back(sf::Vertex(tVertexPos));
	}

	// Add the last vertex at the position of the first vertex added in order to connect the next to last vertex with the last one
	this->m_ObjectMesh.push_back(sf::Vertex(this->m_ObjectMesh[0]));
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
