#include "Core/GameObject.h"

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

void LevelBase::HandleEvent(sf::Event Event)
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
