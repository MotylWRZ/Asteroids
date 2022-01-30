#include "Core/LevelBase.h"

#include "Game/AsteroidsGameObject.h"

AsteroidsGameObject::AsteroidsGameObject()
{
}

AsteroidsGameObject::~AsteroidsGameObject()
{
}

void AsteroidsGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);

	this->WrapObjectCoordinates();
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
