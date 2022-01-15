
#include "Core/Math/MathHelpers.h"

#include <iostream>

#include "Game/PlayerSpaceShip.h"

PlayerSpaceShip::PlayerSpaceShip()
	:m_Velocity(sf::Vector2f(0.0f, 0.0f))
	,m_ShipRotation(EShipRotation::Rotate_None)
	,m_ThrustStrength(0.0f)
	,m_LinearAcceleration(100.0f)
	,m_AngularAcceleration(3.0f)
	,m_MaxSpeed(100.0f)
{
	this->m_MeshPrimitiveType = sf::LineStrip;
}

PlayerSpaceShip::~PlayerSpaceShip()
{
}

void PlayerSpaceShip::Initialise()
{
	// Define the position of the mesh points
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(0.0f, -100.0f)));
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(-50.0f, 50.0f)));
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(0.0f, 25.0f)));
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(50.0f, 50.0f)));
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(0.0f, -100.0f)));

	// Define the color of the mesh points
	this->m_ObjectMesh[0].color = sf::Color::Red;
	this->m_ObjectMesh[1].color = sf::Color::Green;
	this->m_ObjectMesh[2].color = sf::Color::Blue;
}

void PlayerSpaceShip::Update(float DeltaTime)
{
	this->RotateShip(DeltaTime);

	// Acceleration (ThrustStrength)  applied to velocity
	this->m_Velocity.x += sin(this->m_Angle) * this->m_ThrustStrength * DeltaTime;
	this->m_Velocity.y += -cos(this->m_Angle) * this->m_ThrustStrength * DeltaTime;

	// Check if the current velocity length is greater than the maximum allowed speed
	if (MathHelpers::GetVectorLength(this->m_Velocity) > this->m_MaxSpeed)
	{
		MathHelpers::SetVectorLength(&this->m_Velocity, this->m_MaxSpeed);
	}

	// Add velocity to the position
	this->m_Position += this->m_Velocity * DeltaTime;

	GameObject::Update(DeltaTime);
}

void PlayerSpaceShip::Render(sf::RenderWindow& RenderWindow)
{
	GameObject::Render(RenderWindow);

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
