
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
	this->m_CircleShape = std::make_shared<sf::CircleShape>(80, 3);
	this->m_CircleShape->setRadius(200.0f);
	this->m_CircleShape->setFillColor(sf::Color::Black);
	this->m_CircleShape->setPosition(sf::Vector2f(200.0f, 100.0f));
	this->m_CircleShape->setOutlineThickness(10.0f);
	this->m_CircleShape->setOutlineColor(sf::Color(250, 150, 100));

	// define the position of the triangle's points
	m_ShipMesh.push_back(sf::Vertex(sf::Vector2f(0.0f, 100.0f)));
	m_ShipMesh.push_back(sf::Vertex(sf::Vector2f(50.0f, 0.0f)));
	m_ShipMesh.push_back(sf::Vertex(sf::Vector2f(100.0f, 100.0f)));
	

	// define the color of the triangle's points
	m_ShipMesh[0].color = sf::Color::Red;
	m_ShipMesh[1].color = sf::Color::Blue;
	m_ShipMesh[2].color = sf::Color::Green;
}

void PlayerSpaceShip::Update(float DeltaTime)
{
}

void PlayerSpaceShip::Render(sf::RenderWindow& RenderWindow)
{
	//RenderWindow.draw(*this->m_CircleShape);
	RenderWindow.draw(&this->m_ShipMesh[0], this->m_ShipMesh.size(), sf::Triangles);
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
