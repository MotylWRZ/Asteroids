#include "Game/PlayerSpaceShip.h"

PlayerSpaceship::PlayerSpaceship()
{
}

PlayerSpaceship::~PlayerSpaceship()
{
}

void PlayerSpaceship::Initialise()
{
	this->m_CircleShape = std::make_shared<sf::CircleShape>();
	this->m_CircleShape->setRadius(200.0f);
	this->m_CircleShape->setFillColor(sf::Color::Blue);
	this->m_CircleShape->setPosition(sf::Vector2f(200.0f, 200.0f));
}

void PlayerSpaceship::Update(float DeltaTime)
{
}

void PlayerSpaceship::Render(sf::RenderWindow& RenderWindow)
{
	RenderWindow.draw(*this->m_CircleShape);
}
