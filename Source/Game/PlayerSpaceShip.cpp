
#include <iostream>

#include "Game/PlayerSpaceShip.h"

PlayerSpaceShip::PlayerSpaceShip()
{
}

PlayerSpaceShip::~PlayerSpaceShip()
{
}

void PlayerSpaceShip::Initialise()
{
	this->m_CircleShape = std::make_shared<sf::CircleShape>();
	this->m_CircleShape->setRadius(200.0f);
	this->m_CircleShape->setFillColor(sf::Color::Blue);
	this->m_CircleShape->setPosition(sf::Vector2f(200.0f, 200.0f));
}

void PlayerSpaceShip::Update(float DeltaTime)
{
}

void PlayerSpaceShip::Render(sf::RenderWindow& RenderWindow)
{
	RenderWindow.draw(*this->m_CircleShape);
}

void PlayerSpaceShip::HandleInput(sf::Keyboard::Key Key, bool IsPressed)
{
	if (!IsPressed)
	{
		return;
	}

	switch (Key)
	{
	case sf::Keyboard::Key::A:
	{
		break;
	}
	case sf::Keyboard::Key::D:
	{
		break;
	}
	case sf::Keyboard::Key::S:
	{
		break;
	}
	case sf::Keyboard::Key::W:
	{
		break;
	}
	default:
		break;
	}
}
