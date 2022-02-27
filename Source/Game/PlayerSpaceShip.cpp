#include "Core/Math/MathHelpers.h"
#include "Core/LevelBase.h"
#include "Game/Bullet.h"
#include "Game/Asteroid.h"

#include <iostream>

#include "Game/PlayerSpaceShip.h"

PlayerSpaceShip::PlayerSpaceShip()
	:m_Velocity(sf::Vector2f(0.0f, 0.0f))
	,m_ShipRotation(EShipRotation::Rotate_None)
	,m_ThrustStrength(0.0f)
	,m_ThrustParticleSizeMin(3.0f)
	,m_ThrustParticleSizeMax(10.0f)
	,m_ThrustParticlesNumMax(100)
	,m_LinearAcceleration(170.0f)
	,m_AngularAcceleration(3.0f)
	,m_MaxSpeed(170.0f)
	,m_BulletDirAngleOffset(-90.0f * PI / 180.0f)
	,m_BulletPositionOffset(sf::Vector2f(0.0f, -47.0f))
	,m_Size(47.0f)
{
	this->m_MeshPrimitiveType = sf::LinesStrip;
	this->m_IsInputEnabled = true;
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

	this->SetColliderRadius(27.0f * this->m_Scale);
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

	if (this->m_ThrustStrength > 0.0f && !this->m_CanExplode)
	{
		// Emit thrust particles
		this->Thrust();
	}

	for (int i = this->m_ThrustParticles.size(); i-- > 0; )
	{
		ThrustParticle& tThrustParticle = this->m_ThrustParticles[i];

		float tDist = MathHelpers::GetVectorLength(tThrustParticle.Start - tThrustParticle.End);

		if (tDist <= 1.0f || tDist > this->m_ThrustParticleSizeMax)
		{
			this->m_ThrustParticles.erase(this->m_ThrustParticles.begin() + i);
			continue;
		}

		tDist -= 0.1f;
		sf::Vector2f tDir = tThrustParticle.Start - tThrustParticle.End;
		tDir = MathHelpers::NormalizeVector(tDir);
		tDir *= 0.5f;
		tThrustParticle.Start += tDir;
		tThrustParticle.Size -= 700.0f * DeltaTime;
		tThrustParticle.End = tThrustParticle.Start + (-tThrustParticle.Direction * tThrustParticle.Size);
	}

	AsteroidsGameObject::Update(DeltaTime);
}

void PlayerSpaceShip::Render(sf::RenderWindow& RenderWindow)
{
	AsteroidsGameObject::Render(RenderWindow);

	// Render Thrust Particles
	for (auto& tThrustParticle : this->m_ThrustParticles)
	{
		sf::Vertex tStart = tThrustParticle.Start;
		sf::Vertex tEnd = tThrustParticle.End;

		std::vector<sf::Vertex> tLine = { tStart, tEnd };

		RenderWindow.draw(&tLine[0], tLine.size(), sf::Lines);
	}
}

void PlayerSpaceShip::HandleInput(sf::Keyboard::Key Key, bool IsPressed)
{
	if (!this->IsValid() || !this->IsInputEnabled())
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

void PlayerSpaceShip::DebugDraw(sf::RenderWindow& RenderWindow)
{
	AsteroidsGameObject::DebugDraw(RenderWindow);

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

void PlayerSpaceShip::Thrust()
{
	if (this->m_ThrustParticles.size() >= this->m_ThrustParticlesNumMax)
	{
		return;
	}

	// Construct a thrust particle (line)
	ThrustParticle tThrustParticle;

	float tStartOffsetX = MathHelpers::GenerateRandomFloatInRange(-10.0f, 10.0f);
	sf::Vector2f tThrustParticlePositionOffset = sf::Vector2f(tStartOffsetX, 24.0f);

	// Transform particle position offset using current player ship rotation angle
	sf::Vector2f tOffsetTransformed = tThrustParticlePositionOffset;

	tOffsetTransformed.x = tThrustParticlePositionOffset.x * cosf(this->m_Angle) - tThrustParticlePositionOffset.y * sinf(this->m_Angle);
	tOffsetTransformed.y = tThrustParticlePositionOffset.x * sinf(this->m_Angle) + tThrustParticlePositionOffset.y * cosf(this->m_Angle);

	// Calculate the initial particle position by adding a transformed offset to the player ship position
	//sf::Vector2f tBulletPosition = this->m_Position + tOffsetTransformed;
	tThrustParticle.Start = this->m_Position + tOffsetTransformed;

	// Create a vector to store a bullet direction
	sf::Vector2f tParticleDir(0.0f, 0.0f);

	//float tAngle = this->m_Angle + MathHelpers::GenerateRandomFloatInRange(-1.0f, 1.0f);
	float tAngle;
	if (tStartOffsetX >= 0.0f)
	{
		tAngle = this->m_Angle + MathHelpers::GenerateRandomFloatInRange(tStartOffsetX / 100.0f, tStartOffsetX / 10.0f);
	}
	else
	{
		tAngle = this->m_Angle + MathHelpers::GenerateRandomFloatInRange(tStartOffsetX / 10.0f, tStartOffsetX / 100.0f);
	}

	// Calculate particle direction
	tParticleDir.x = cosf(tAngle + this->m_BulletDirAngleOffset);
	tParticleDir.y = sinf(tAngle + this->m_BulletDirAngleOffset);

	// Set a thrust particle direction
	tThrustParticle.Direction = -tParticleDir;
	// Set particle size (length)
	tThrustParticle.Size = MathHelpers::GenerateRandomFloatInRange(this->m_ThrustParticleSizeMin, this->m_ThrustParticleSizeMax);
	// Set particle end position
	tThrustParticle.End = tThrustParticle.Start + (tThrustParticle.Direction * tThrustParticle.Size);

	this->m_ThrustParticles.push_back(tThrustParticle);
}

void PlayerSpaceShip::OnCollision(Collider2D* Collider)
{
	Asteroid* tAsteroid = dynamic_cast<Asteroid*>(Collider);

	if (!tAsteroid)
	{
		return;
	}

	// Disable Input
	this->m_IsInputEnabled = false;

	// Start Explosion Animation
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