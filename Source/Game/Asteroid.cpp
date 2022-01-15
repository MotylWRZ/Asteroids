#include "Game/Asteroid.h"

Asteroid::Asteroid()
	:m_AsteroidShapeRadius(100.0f)
	,m_MeshVertNum(30)
{
	this->m_MeshPrimitiveType = sf::LineStrip;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Initialise()
{
	const float PI = 3.14159f;

	// Generate a list of vertices placed around the object position
	for (unsigned int i = 0; i < this->m_MeshVertNum; i++)
	{
		float tAngle = (static_cast<float>(i) / static_cast<float>(this->m_MeshVertNum)) * PI * 2;
		sf::Vector2f  tVertexPos(this->m_AsteroidShapeRadius * sinf(tAngle), this->m_AsteroidShapeRadius * cosf(tAngle));
		this->m_ObjectMesh.push_back(sf::Vertex(tVertexPos));
	}

	// Add the last vertex at the position of the first vertex added in order to connect the next to last vertex with the last one
	this->m_ObjectMesh.push_back(sf::Vertex(this->m_ObjectMesh[0]));
}

void Asteroid::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void Asteroid::Render(sf::RenderWindow& RenderWindow)
{
	GameObject::Render(RenderWindow);
}
