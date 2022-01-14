#pragma once

#include "Core/GameObject.h"

#include "SFML/Graphics.hpp"

#include <vector>

class LevelBase
{
public:
	LevelBase();
	LevelBase(sf::Vector2u WorldSize);
	virtual ~LevelBase();

	virtual void Initialize();
	virtual void Update(float DeltaTime);
	virtual void HandleEvent(const sf::Event& Event);
	virtual void HandleInput(sf::Keyboard::Key Key, bool IsPressed);
	virtual void Render(sf::RenderWindow& RenderWindow);

	void AddObject(std::shared_ptr<GameObject> Object);
	void RemoveObject(std::shared_ptr<GameObject> Object);
	const GameObject& GetObject(unsigned int Index) { return *this->m_GameObjects[Index]; }
	std::vector<std::shared_ptr<GameObject>>& GetObjectsRef() { return this->m_GameObjects; }

protected:
	std::vector<std::shared_ptr<GameObject>> m_GameObjects;
	sf::Vector2u m_WorldSize;
};

