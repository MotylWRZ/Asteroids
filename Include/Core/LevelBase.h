#pragma once

#include "Core/GameObject.h"

#include "SFML/Graphics.hpp"

#include <vector>
#include <map>

class Collider2D;

class LevelBase
{
public:
	LevelBase();
	LevelBase(sf::Vector2u WorldSize);
	virtual ~LevelBase();

	virtual void Initialise();
	virtual void Reinitialise();
	virtual void Update(float DeltaTime);
	virtual void HandleEvent(const sf::Event& Event);
	virtual void HandleInput(sf::Keyboard::Key Key, bool IsPressed);
	virtual void Render(sf::RenderWindow& RenderWindow);

	virtual void UpdateObjectCollision(GameObject* Object);

	void AddObject(std::shared_ptr<GameObject> Object);
	void RemoveObject(std::shared_ptr<GameObject> Object);

	inline const GameObject& GetObject(unsigned int Index) { return *this->m_GameObjects[Index]; }
	inline std::vector<std::shared_ptr<GameObject>>& GetObjectsRef() { return this->m_GameObjects; }
	inline const sf::Vector2u GetWorldSize() const { return this->m_WorldSize; }
	inline void DestroyLevel() { this->m_IsValid = false; }
	inline const bool IsLevelValid() const { return this->m_IsValid; }


protected:
	void ClearInactiveObjects();

protected:
	std::vector<std::shared_ptr<GameObject>> m_GameObjects;
	std::vector<std::shared_ptr<GameObject>> m_ObjectsToAdd;
	std::vector<unsigned int> m_ObjectsToClear;

	std::map<const GameObject*, std::weak_ptr<Collider2D>> m_Colliders;

	sf::Vector2u m_WorldSize;
	bool m_IsValid;
};

