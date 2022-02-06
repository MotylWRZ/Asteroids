#include "Core/Math/MathHelpers.h"
#include "Core/LevelBase.h"
#include "Game/Bullet.h"
#include "Game/Asteroid.h"

#include <iostream>

#include "Game/PlayerSpaceShip.h"

PlayerSpaceShip::PlayerSpaceShip()
	:m_Velocity(sf::Vector2f(0.0f, 0.0f))
	, m_ShipRotation(EShipRotation::Rotate_None)
	, m_ThrustStrength(0.0f)
	, m_LinearAcceleration(100.0f)
	, m_AngularAcceleration(3.0f)
	, m_MaxSpeed(100.0f)
	, m_BulletDirAngleOffset(-90.0f * PI / 180.0f)
	, m_BulletPositionOffset(sf::Vector2f(0.0f, -100.0f))
	, m_Size(47.0f)
	, m_Lives(3)
{
	this->m_MeshPrimitiveType = sf::LinesStrip;
}

PlayerSpaceShip::~PlayerSpaceShip()
{
}

void PlayerSpaceShip::Initialise(LevelBase* Level)
{
	AsteroidsGameObject::Initialise(Level);

	if (!this->IsValid())
	{
		return;
	}

	// Define the position of the mesh points
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(0.0f, -this->m_Size)));
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(-this->m_Size / 2.0f, this->m_Size / 2.0f)));
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(0.0f, this->m_Size / 4.0f)));
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(this->m_Size / 2.0f, this->m_Size / 2.0f)));
	this->m_ObjectMesh.push_back(sf::Vertex(sf::Vector2f(0.0f, -this->m_Size)));

	// Check if geometry shaders are supported
	if (!sf::Shader::isGeometryAvailable())
	{
		std::cout << "Geometry Shaders are not supported." << std::endl;
		return;
	}

	this->SetShader("Assets/Shaders/BasicVertexShader.vert", "Assets/Shaders/CoordWrappingShader.geom", "Assets/Shaders/BasicFragmentShader.frag");

	this->SetColliderRadius(47.0f * this->m_Scale);
}

void PlayerSpaceShip::Update(float DeltaTime)
{
	if (!this->IsValid())
	{
		return;
	}

	this->SetColliderCenter(this->GetPosition());

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

	AsteroidsGameObject::Update(DeltaTime);
}

void PlayerSpaceShip::Render(sf::RenderWindow& RenderWindow)
{
	AsteroidsGameObject::Render(RenderWindow);

	//RenderWindow.draw(*this->m_CircleShape, &this->GetShader());
	this->DrawDebug(RenderWindow);
}

void PlayerSpaceShip::HandleInput(sf::Keyboard::Key Key, bool IsPressed)
{
	if (!this->IsValid())
	{
		return;
	}

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
	case sf::Keyboard::Key::Space:
	{
		!IsPressed ? this->Shoot() : 0;
		break;
	}
	default:
		this->m_ShipRotation = EShipRotation::Rotate_None;
		break;
	}
}

void PlayerSpaceShip::Shoot()
{
	if (!this->IsValid() || !this->m_Level)
	{
		return;
	}

	std::shared_ptr<Bullet> tBullet = std::make_shared <Bullet>();
	this->m_Level->AddObject(tBullet);

	// Transform Bullet position offset using current player ship rotation angle
	sf::Vector2f tOffsetTransformed = this->m_BulletPositionOffset;

	tOffsetTransformed.x = this->m_BulletPositionOffset.x * cosf(this->m_Angle) - this->m_BulletPositionOffset.y * sinf(this->m_Angle);
	tOffsetTransformed.y = this->m_BulletPositionOffset.x * sinf(this->m_Angle) + this->m_BulletPositionOffset.y * cosf(this->m_Angle);

	// Calculate the initial bullet position by adding a transformed offset to the player ship position
	sf::Vector2f tBulletPosition = this->m_Position + tOffsetTransformed;

	tBullet->SetPosition(tBulletPosition);

	// Create a vector to store a bullet direction
	sf::Vector2f tBulletDir(0.0f, 0.0f);

	// Calculate bullet direction
	tBulletDir.x = cosf(this->m_Angle + this->m_BulletDirAngleOffset);
	tBulletDir.y = sinf(this->m_Angle + this->m_BulletDirAngleOffset);

	// Set a new bullet direction
	tBullet->SetDirection(tBulletDir);
}

void PlayerSpaceShip::OnCollision(Collider2D* Collider)
{
	Asteroid* tAsteroid = dynamic_cast<Asteroid*>(Collider);

	if (!tAsteroid)
	{
		return;
	}

	this->m_Lives--;
	this->DestroyWithExplosion(2.0f, 10.0f);
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


	std::vector<sf::Vertex> tCollisionGeometry;

	// Generate a list of vertices placed around the object position
	for (unsigned int i = 0; i < 20; i++)
	{
		float tAngle = (static_cast<float>(i) / static_cast<float>(20)) * PI * 2;
		sf::Vector2f  tVertexPos(this->GetColliderRadius() * sinf(tAngle), this->GetColliderRadius() * cosf(tAngle));
		tVertexPos += this->GetColliderCenter();

		tCollisionGeometry.push_back(sf::Vertex(tVertexPos));
	}

	// Add the last vertex at the position of the first vertex added in order to connect the next to last vertex with the last one
	tCollisionGeometry.push_back(sf::Vertex(tCollisionGeometry[0]));

	RenderWindow.draw(&tCollisionGeometry[0], tCollisionGeometry.size(), sf::LinesStrip);
}
