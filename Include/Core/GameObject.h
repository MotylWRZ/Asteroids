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

	inline virtual const sf::Vector2f& GetPosition() const { return this->m_Position; }
	inline virtual void SetPosition(sf::Vector2f NewPosition) { this->m_Position = NewPosition; }

protected:
	sf::Vector2f m_Position;
	float m_Angle;
	std::vector<sf::Vertex> m_ObjectMesh;
	sf::PrimitiveType m_MeshPrimitiveType;

private:
	std::vector<sf::Vertex> m_TransformedMesh;
};

