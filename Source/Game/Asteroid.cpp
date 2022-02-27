#include "Core/Math/MathHelpers.h"
#include "Core/GeometryGenerator.h"
#include "Game/Bullet.h"
#include "Core/LevelBase.h"
#include "Game/LevelMain.h"

#include <iostream>

#include "Game/Asteroid.h"

Asteroid::Asteroid(float Size, float DeformationScale, int VerticesNum)
	:m_AsteroidShapeRadius(Size)
	,m_MeshVertNum(VerticesNum)
	,m_Velocity(sf::Vector2f(0.0f, 0.0f))
	,m_LinearAcceleration(1000.0f)
	,m_AngularAcceleration(1.0f)
	,m_MaxSpeed(100.0f)
	,m_DeformationScale(DeformationScale)
	,m_CanMultiply(false)
	,m_ChunksNum(2)
	,m_AngularMovementDirection(1)
	,m_ScoreValue(1)
	,m_MovementAngle(0.0f)
{
	this->m_MeshPrimitiveType = sf::LinesStrip;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Initialise(LevelBase* Level)
{
	AsteroidsGameObject::Initialise(Level);

	if (!this->IsValid())
	{
		return;
	}

	this->m_Angle = MathHelpers::GenerateRandomFloatInRange(-100.0f, 100.0f);
	this->m_MovementAngle = this->m_Angle;

	// Generate a list of vertices placed around the object position
	for (unsigned int i = 0; i < this->m_MeshVertNum; i++)
	{
		float tAngle = (static_cast<float>(i) / static_cast<float>(this->m_MeshVertNum)) * PI * 2;
		sf::Vector2f  tVertexPos(this->m_AsteroidShapeRadius * sinf(tAngle), this->m_AsteroidShapeRadius * cosf(tAngle));

		// Offset vertex position by random vector
		sf::Vector2f tRandomPosOffset;
		tRandomPosOffset.x = MathHelpers::GenerateRandomFloatInRange(-this->m_DeformationScale, this->m_DeformationScale);
		tRandomPosOffset.y = MathHelpers::GenerateRandomFloatInRange(-this->m_DeformationScale, this->m_DeformationScale);
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

	this->SetColliderCenter(this->GetPosition());
	this->SetColliderRadius(this->m_AsteroidShapeRadius * this->m_Scale);

	// Set a random angular movement direction
	this->m_AngularMovementDirection = MathHelpers::GenerateRandomIntegerInRange(0, 1);

	if (this->m_AngularMovementDirection == 0)
	{
		this->m_AngularMovementDirection = -1;
	}

	this->SetShader("Assets/Shaders/BasicVertexShader.vert", "Assets/Shaders/CoordWrappingShader.geom", "Assets/Shaders/BasicFragmentShader.frag");
}

void Asteroid::Update(float DeltaTime)
{
	// Apply angular acceleration to the current object angle
	this->m_Angle += this->m_AngularAcceleration * this->m_AngularMovementDirection * DeltaTime;

	// Acceleration applied to velocity
	this->m_Velocity.x += sin(this->m_MovementAngle) * this->m_LinearAcceleration * DeltaTime;
	this->m_Velocity.y += -cos(this->m_MovementAngle) * this->m_LinearAcceleration * DeltaTime;

	// Check if the current velocity length is greater than the maximum allowed speed
	if (MathHelpers::GetVectorLength(this->m_Velocity) > this->m_MaxSpeed)
	{
		MathHelpers::SetVectorLength(&this->m_Velocity, this->m_MaxSpeed);
	}

	// Add velocity to the position
	this->m_Position += this->m_Velocity * DeltaTime;

	this->SetColliderCenter(this->GetPosition());

	AsteroidsGameObject::Update(DeltaTime);
}

void Asteroid::Render(sf::RenderWindow& RenderWindow)
{
	AsteroidsGameObject::Render(RenderWindow);
}

void Asteroid::OnCollision(Collider2D* Collider)
{
	Bullet* tBullet = dynamic_cast<Bullet*>(Collider);

	if (!tBullet)
	{
		return;
	}
}

void Asteroid::SetSize(float Size, float DeformationScale, int VerticesNum)
{
	this->m_AsteroidShapeRadius = Size;
	this->m_DeformationScale = DeformationScale;
	this->m_MeshVertNum = VerticesNum;

	if (this->m_ObjectMesh.size() != 0)
	{
		this->Initialise(this->m_Level);
	}
}

void Asteroid::SetCanMultiply(bool CanMultiply, unsigned int ChunksNum)
{
	this->m_CanMultiply = CanMultiply;
	this->m_ChunksNum = ChunksNum;
}

void Asteroid::DestroyWithExplosion(float Duration, float Rate)
{
	AsteroidsGameObject::DestroyWithExplosion(Duration, Rate);

	LevelMain* tLevel = dynamic_cast<LevelMain*>(this->m_Level);

	if (tLevel)
	{
		tLevel->SetPlayerScore(tLevel->GetPlayerScore() + this->m_ScoreValue);
	}

	// Multiply the Asteroid
	if (this->m_CanMultiply)
	{
		for (unsigned int i = 0; i < this->m_ChunksNum; i++)
		{
			std::shared_ptr<GameObject> tAsteroid = std::make_shared<Asteroid>();
			tAsteroid->SetPosition(this->GetPosition());
			tAsteroid->SetScale(0.5f);
			Asteroid* tAsteroidPtr = dynamic_cast<Asteroid*>(tAsteroid.get());
			tAsteroidPtr->SetLinearAcceleration(this->m_LinearAcceleration);
			tAsteroidPtr->SetMaxSpeed(this->m_MaxSpeed);

			this->m_Level->AddObject(tAsteroid);
		}
	}
}
