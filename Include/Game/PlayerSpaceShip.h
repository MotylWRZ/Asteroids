#pragma once

#include "SFML/Graphics.hpp"

#include "Core/GameObject.h"

class PlayerSpaceShip : public GameObject
{
public:
	PlayerSpaceShip();
	virtual ~PlayerSpaceShip();

	virtual void Initialise() override;
	virtual void Update(float DeltaTime) override;
	virtual void Render(sf::RenderWindow& RenderWindow) override;
	virtual void HandleInput(sf::Keyboard::Key Key, bool IsPressed);

	std::shared_ptr<sf::CircleShape> m_CircleShape;
};