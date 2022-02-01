#include "Core/LevelBase.h"
#include "Core/Math/MathHelpers.h"

#include "Game/AsteroidsGameObject.h"

AsteroidsGameObject::AsteroidsGameObject()
	:m_CanExplode(false)
	,m_ExplosionDuration(0.0f)
	,m_ExplosionRate(0.0f)
{
}

AsteroidsGameObject::~AsteroidsGameObject()
{
}

void AsteroidsGameObject::Initialise(LevelBase* Level)
{
	GameObject::Initialise(Level);
}

void AsteroidsGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);

	// Proceed with explosion
	if (this->m_ExplosionDuration > 0.0f && this->m_CanExplode)
	{
		this->m_ExplosionDuration -= DeltaTime;

		if (this->m_ExplosionDuration <= 0.0f)
		{
			this->DestroyObject();
			return;
		}

		for (int i = 0; i < this->m_ObjectMesh.size() - 1; i++)
		{
			// Find a midpoind between the points of the line and move both points in an opposite direction to the object origin
			sf::Vector2f tMidpoint = (this->m_ObjectMesh[i].position + this->m_ObjectMesh[i + 1].position) * 0.5f;
			sf::Vector2f tDir = sf::Vector2f(0.0f, 0.0f) + tMidpoint;
			tDir = MathHelpers::NormalizeVector(tDir);
			tDir *= this->m_ExplosionRate;
			this->m_ObjectMesh[i].position += tDir * DeltaTime;
			this->m_ObjectMesh[i + 1].position += tDir * DeltaTime;

			// Move both vertices that makes a line towards each other to make the line look smaller
			sf::Vector2f tDir2 = this->m_ObjectMesh[i].position - this->m_ObjectMesh[i + 1].position;
			tDir2 = MathHelpers::NormalizeVector(tDir2);
			tDir2 *= this->m_ExplosionRate;
			this->m_ObjectMesh[i].position -= tDir2 * DeltaTime;
			this->m_ObjectMesh[i + 1].position += tDir2 * DeltaTime;

			i++;
		}
	}

	this->WrapObjectCoordinates();

	this->SetColliderCenter(this->GetPosition());
}

void AsteroidsGameObject::WrapObjectCoordinates()
{
	sf::Vector2f tObjectPos = this->GetPosition();
	sf::Vector2f tWorldSize = static_cast<sf::Vector2f>(this->m_Level->GetWorldSize());

	// Wrap the X coordinate
	if (tObjectPos.x < 0.0f)
	{
		tObjectPos.x = tWorldSize.x;
	}
	else if (tObjectPos.x > tWorldSize.x)
	{
		tObjectPos.x = 0.0f;
	}

	// Wrap Y coordinate
	if (tObjectPos.y < 0.0f)
	{
		tObjectPos.y = tWorldSize.y;
	}
	else if (tObjectPos.y > tWorldSize.y)
	{
		tObjectPos.y = 0.0f;
	}

	this->SetPosition(tObjectPos);
}

void AsteroidsGameObject::DestroyWithExplosion(float Duration, float Rate)
{
	this->m_ExplosionDuration = Duration;
	this->m_ExplosionRate = Rate;

	// Change PrimitiveType to sf::Lines. I this form, it will be sent to the shaders
	this->m_MeshPrimitiveType = sf::Lines;

	// Generate a new mesh by duplicating the mesh vertices, wihch will be then assembled in indiviudal lines by the shaders
	std::vector<sf::Vertex> tNewMesh;

	tNewMesh.push_back(this->m_ObjectMesh[0]);
	for (int i = 1; i < this->m_ObjectMesh.size(); i++)
	{
		tNewMesh.push_back(this->m_ObjectMesh[i]);
		tNewMesh.push_back(this->m_ObjectMesh[i]);
	}

	this->m_ObjectMesh = tNewMesh;

	this->SetCollisionEnabled(false);

	this->m_CanExplode = true;
}
