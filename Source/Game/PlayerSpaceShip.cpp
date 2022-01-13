
#include "Core/Math/MathHelpers.h"

#include <iostream>

#include "Game/PlayerSpaceShip.h"

PlayerSpaceShip::PlayerSpaceShip()
	:m_Angle(0.0f)
	,m_Position(sf::Vector2f(100.0f, 100.0f))
	,m_Velocity(sf::Vector2f(0.0f, 0.0f))
	,m_ShipRotation(EShipRotation::Rotate_None)
	,m_ThrustStrength(0.0f)
	,m_LinearAcceleration(100.0f)
	,m_AngularAcceleration(3.0f)
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

	// Define the position of the mesh points
	m_ShipMesh.push_back(sf::Vertex(sf::Vector2f(0.0f, -100.0f)));
	m_ShipMesh.push_back(sf::Vertex(sf::Vector2f(-50.0f, 50.0f)));
	m_ShipMesh.push_back(sf::Vertex(sf::Vector2f(50.0f, 50.0f)));
	

	// Define the color of the mesh points
	m_ShipMesh[0].color = sf::Color::Red;
	m_ShipMesh[1].color = sf::Color::Green;
	m_ShipMesh[2].color = sf::Color::Blue;
}

void PlayerSpaceShip::Update(float DeltaTime)
{
	this->m_TransformedMesh = this->m_ShipMesh;

	this->RotateShip(DeltaTime);

	// Acceleration (ThrustStrength)  applied to velocity
	this->m_Velocity.x += sin(this->m_Angle) * this->m_ThrustStrength * DeltaTime;
	this->m_Velocity.y += -cos(this->m_Angle) * this->m_ThrustStrength * DeltaTime;

	// Add velocity to the position
	this->m_Position += this->m_Velocity * DeltaTime;

	//Rotate
	for (unsigned int i = 0; i < this->m_TransformedMesh.size(); i++)
	{
		this->m_TransformedMesh[i].position.x = this->m_ShipMesh[i].position.x * cosf(this->m_Angle) - this->m_ShipMesh[i].position.y * sinf(this->m_Angle);
		this->m_TransformedMesh[i].position.y = this->m_ShipMesh[i].position.x * sinf(this->m_Angle) + this->m_ShipMesh[i].position.y * cosf(this->m_Angle);
	}

	// Translate
	for (unsigned int i = 0; i < this->m_TransformedMesh.size(); i++)
	{
		this->m_TransformedMesh[i].position.x += this->m_Position.x;
		this->m_TransformedMesh[i].position.y += this->m_Position.y;
	}
}

void PlayerSpaceShip::Render(sf::RenderWindow& RenderWindow)
{
	//RenderWindow.draw(*this->m_CircleShape);
	RenderWindow.draw(&this->m_TransformedMesh[0], this->m_TransformedMesh.size(), sf::Triangles);

	this->DrawDebug(RenderWindow);
}

void PlayerSpaceShip::HandleInput(sf::Keyboard::Key Key, bool IsPressed)
{
	switch (Key)
	{
	case sf::Keyboard::Key::Up:
	{
		IsPressed ? this->m_ThrustStrength = this->m_LinearAcceleration : this->m_ThrustStrength = 0.0f;
		
		break;
	}
	case sf::Keyboard::Key::Left:
	{
		IsPressed ? this->m_ShipRotation = EShipRotation::Rotate_Left : this->m_ShipRotation = EShipRotation::Rotate_None;
		break;
	}
	case sf::Keyboard::Key::Right:
	{
		IsPressed ? this->m_ShipRotation = EShipRotation::Rotate_Right : this->m_ShipRotation = EShipRotation::Rotate_None;
		break;
	}
	default:
		this->m_ShipRotation = EShipRotation::Rotate_None;
		break;
	}
}

void PlayerSpaceShip::RotateShip(float DeltaTime)
{
	switch (this->m_ShipRotation)
	{
	case EShipRotation::Rotate_Left:
	{
		this->m_Angle -= this->m_AngularAcceleration * DeltaTime;
		break;
	}
	case EShipRotation::Rotate_Right:
	{
		this->m_Angle += this->m_AngularAcceleration * DeltaTime;
		break;
	}
	case EShipRotation::Rotate_None:
	{
		break;
	}
	}
}

void PlayerSpaceShip::DrawDebug(sf::RenderWindow& RenderWindow)
{
	// Calculate a Velocity vector length
	float tVelocityLength = MathHelpers::GetVectorLength(this->m_Velocity);

	// Cache locally a normalized velocity vector
	sf::Vector2f tVelocityNormalized = MathHelpers::NormalizeVector(this->m_Velocity);

	// Set the DebugLineStart to the current mesh position
	sf::Vector2f tDebugLineStart = this->m_Position;

	// Calculate the DebugLineEnd vector by adding to the current position noormalized velocity vector multiplied by velocity length
	sf::Vector2f tDebugLineEnd = this->m_Position + (tVelocityNormalized * tVelocityLength);

	// Construct a vector of vertices that will be used to draw a line
	std::vector<sf::Vertex> tLinePoints;
	tLinePoints.push_back(tDebugLineStart);
	tLinePoints.push_back(tDebugLineEnd);

	// Draw a line
	RenderWindow.draw(&tLinePoints[0], tLinePoints.size(), sf::Lines);
}
