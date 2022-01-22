#include "Core/GameObject.h"

#include <iostream>

#include "Core/LevelBase.h"

LevelBase::LevelBase()
	:m_WorldSize(sf::Vector2u(0, 0))
{
}

LevelBase::LevelBase(sf::Vector2u WorldSize)
	:m_WorldSize(WorldSize)
{
}

LevelBase::~LevelBase()
{
}

void LevelBase::Initialize()
{
}

void LevelBase::Update(float DeltaTime)
{
	for (unsigned int i = 0; i < this->m_GameObjects.size(); i++)
	{
		std::shared_ptr<GameObject> tGameObject = this->m_GameObjects[i];

		if (!tGameObject || !tGameObject->IsActive())
		{
			this->m_ObjectsToClear.push_back(i);
			continue;
		}

		tGameObject->Update(DeltaTime);

	}

	this->ClearInactiveObjects();

	/*for (auto& tGameObject : this->m_GameObjects)
	{
		if (!tGameObject || !tGameObject->IsActive())
		{
			this->m_ObjectsToClear.push_back()
			continue;
		}

		tGameObject->Update(DeltaTime);
	}*/
}

void LevelBase::HandleEvent(const sf::Event& Event)
{
	sf::Event tEvent = Event;

	switch (tEvent.type)
	{
	case sf::Event::KeyPressed:
	{
		this->HandleInput(tEvent.key.code, true);
		break;
	}
	case sf::Event::KeyReleased:
	{
		this->HandleInput(tEvent.key.code, false);
		break;
	}
	default:
		break;
	}
}

void LevelBase::HandleInput(sf::Keyboard::Key Key, bool IsPressed)
{
}

void LevelBase::Render(sf::RenderWindow& RenderWindow)
{
	for (auto& tGameObject : this->m_GameObjects)
	{
		tGameObject->Render(RenderWindow);
	}
}

void LevelBase::AddObject(std::shared_ptr<GameObject> Object)
{
	this->m_GameObjects.push_back(Object);
	Object->Initialise(this);
}

void LevelBase::RemoveObject(std::shared_ptr<GameObject> Object)
{

}

void LevelBase::ClearInactiveObjects()
{
	for (unsigned int tIndex : this->m_ObjectsToClear)
	{
		this->m_GameObjects.erase(this->m_GameObjects.begin() + tIndex);
	}

	this->m_ObjectsToClear.clear();
}
