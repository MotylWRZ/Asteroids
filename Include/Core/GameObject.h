#pragma once

#include "SFML/Graphics.hpp"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialise();
	virtual void Update(float DeltaTime);
	virtual void Render(sf::RenderWindow& Windo);
};

