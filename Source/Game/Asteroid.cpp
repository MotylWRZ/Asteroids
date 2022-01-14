#include "Game/Asteroid.h"

Asteroid::Asteroid()
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Initialise()
{
	// Define the position of the mesh points
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(0.0f, -100.0f)));
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(-50.0f, 50.0f)));
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(50.0f, 50.0f)));
}

void Asteroid::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void Asteroid::Render(sf::RenderWindow& RenderWindow)
{
	GameObject::Render(RenderWindow);
}
