#pragma once

#include "SFML/Graphics.hpp"

#include "Core/GameObject.h"

class PlayerSpaceship : public GameObject
{
public:
	PlayerSpaceship();
	virtual ~PlayerSpaceship();

	virtual void Initialise() override;
	virtual void Update(float DeltaTime) override;
	virtual void Render(sf::RenderWindow& RenderWindow) override;

	std::shared_ptr<sf::CircleShape> m_CircleShape;
};