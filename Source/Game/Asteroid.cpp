#include "Core/Math/MathHelpers.h"

#include <iostream>

#include "Game/Asteroid.h"

Asteroid::Asteroid()
	:m_AsteroidShapeRadius(100.0f)
	,m_MeshVertNum(20)
	,m_Velocity(sf::Vector2f(0.0f, 0.0f))
	,m_LinearAcceleration(20.0f)
	,m_AngularAcceleration(1.0f)
	,m_MaxSpeed(20.0f)
{
	this->m_MeshPrimitiveType = sf::LineStrip;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Initialise(LevelBase* Level)
{
	GameObject::Initialise(Level);

	if (!this->IsActive())
	{
		return;
	}

	this->m_Angle = MathHelpers::GenerateRandomFloatInRange(-100.0f, 100.0f);

	// Generate a list of vertices placed around the object position
	for (unsigned int i = 0; i < this->m_MeshVertNum; i++)
	{
		float tAngle = (static_cast<float>(i) / static_cast<float>(this->m_MeshVertNum)) * PI * 2;
		sf::Vector2f  tVertexPos(this->m_AsteroidShapeRadius * sinf(tAngle), this->m_AsteroidShapeRadius * cosf(tAngle));

		// Offset vertex position by random vector
		sf::Vector2f tRandomPosOffset;
		tRandomPosOffset.x = MathHelpers::GenerateRandomFloatInRange(-10.0f, 10.0f);
		tRandomPosOffset.y = MathHelpers::GenerateRandomFloatInRange(-10.0f, 10.0f);
		tVertexPos += tRandomPosOffset;

		this->m_ObjectMesh.push_back(sf::Vertex(tVertexPos));
	}

	// Add the last vertex at the position of the first vertex added in order to connect the next to last vertex with the last one
	this->m_ObjectMesh.push_back(sf::Vertex(this->m_ObjectMesh[0]));


	// Check if geometry shaders are supported
	if (!sf::Shader::isGeometryAvailable())
	{
		std::cout << "Geometry Shaders are not supported." << std::endl;
		return;
	}

	this->SetShader("Assets/Shaders/BasicVertexShader.vert", "Assets/Shaders/CoordWrappingShader.geom", "Assets/Shaders/BasicFragmentShader.frag");
}

void Asteroid::Update(float DeltaTime)
{
	// Acceleration (ThrustStrength)  applied to velocity
	this->m_Velocity.x += sin(this->m_Angle) * this->m_LinearAcceleration * DeltaTime;
	this->m_Velocity.y += -cos(this->m_Angle) * this->m_LinearAcceleration * DeltaTime;

	// Check if the current velocity length is greater than the maximum allowed speed
	if (MathHelpers::GetVectorLength(this->m_Velocity) > this->m_MaxSpeed)
	{
		MathHelpers::SetVectorLength(&this->m_Velocity, this->m_MaxSpeed);
	}

	// Add velocity to the position
	this->m_Position += this->m_Velocity * DeltaTime;

	GameObject::Update(DeltaTime);
}

void Asteroid::Render(sf::RenderWindow& RenderWindow)
{
	GameObject::Render(RenderWindow);
}

void Asteroid::OnCollision(Collider2D* Collider)
{
}
