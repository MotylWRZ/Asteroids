#include "Core/GameObject.h"

#include <iostream>

#include "Core/LevelBase.h"

LevelBase::LevelBase()
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
	for (auto& tGameObject : this->m_GameObjects)
	{
		tGameObject->Update(DeltaTime);
	}
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
}

void LevelBase::RemoveObject(std::shared_ptr<GameObject> Object)
{
	
}
