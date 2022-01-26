#include "Core/GameObject.h"
#include "Core/Physics/Collider2D.h"

#include <memory>
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

void LevelBase::Initialise()
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

void LevelBase::UpdateObjectCollision(GameObject* Object)
{
	// Try to find if this game object is a collider
	auto tColliderPtr = this->m_Colliders.find(Object)->second.lock();
	Collider2D* tCollider = tColliderPtr.get();

	if (tCollider)
	{
		for (auto& tOtherCollider : this->m_Colliders)
		{
			if (tCollider == tOtherCollider.second.lock().get());
			{
				if (tCollider->CollidesWith(tOtherCollider.second.lock().get()))
				{
					tCollider->OnCollision(tOtherCollider.second.lock().get());
				}
			}
		}
	}
}

void LevelBase::AddObject(std::shared_ptr<GameObject> Object)
{
	this->m_GameObjects.push_back(Object);
	Object->Initialise(this);

	std::weak_ptr<Collider2D> tCollider = std::dynamic_pointer_cast<Collider2D>(Object);

	if (tCollider.expired())
	{
		return;
	}

	std::pair<const GameObject*, std::weak_ptr<Collider2D>> tMapElem(Object.get(), tCollider);
	this->m_Colliders.insert(tMapElem);
}

void LevelBase::RemoveObject(std::shared_ptr<GameObject> Object)
{

}

void LevelBase::ClearInactiveObjects()
{
	if (this->m_ObjectsToClear.size() == 0)
	{
		return;
	}

	for (unsigned int tIndex : this->m_ObjectsToClear)
	{

		// Delete a collider pointer if this game object is a collider
		auto tCollider = this->m_Colliders.find(this->m_GameObjects[tIndex].get())->second;

		if (!tCollider.expired())
		{
			this->m_Colliders.erase(this->m_GameObjects[tIndex].get());
		}

		this->m_GameObjects[tIndex].reset();
		this->m_GameObjects[tIndex] = nullptr;
		this->m_GameObjects.erase(this->m_GameObjects.begin() + tIndex);
	}

	this->m_ObjectsToClear.clear();
}
