#include "SFML/Graphics.hpp"
#include "Game/Asteroid.h"
#include "Core/LevelBase.h"

#include "Game/AsteroidsSpawner.h"

AsteroidsSpawner::AsteroidsSpawner(LevelBase* Level)
	:m_StartingAsteroidsNum(0)
	,m_MaxAsteroidsNum(0)
	,m_SpawningCooldown(0.0f)
	,m_AsteroidLinearAcceleration(0.0f)
	,m_AsteroidsMaxSpeed(0.0f)
	,m_AsteroidsSize(0.0f)
	,m_Timer(0.0f)
	,m_Level(Level)
{
}

void AsteroidsSpawner::Initialise(unsigned int StartingAsteroidsNum, unsigned int MaxAsteroidsNum, float SpawningCooldown, float AsteroidsLinearAcceleration, float AsteroidsMaxSpeed, float AsteroidsSize)
{
	this->m_MaxAsteroidsNum = MaxAsteroidsNum;
	this->m_SpawningCooldown = SpawningCooldown;
	this->m_AsteroidLinearAcceleration = AsteroidsLinearAcceleration;
	this->m_AsteroidsMaxSpeed = AsteroidsMaxSpeed;
	this->m_AsteroidsSize = AsteroidsSize;


	if (!this->m_Level)
	{
		std::cout << "Cannot initialise the AsteroidSpawner if a pointer to the Level object is not valid." << std::endl;

		return;
	}
	this->SpawnAsteroids(StartingAsteroidsNum);
}

void AsteroidsSpawner::Update(float DeltaTime)
{
	this->m_Timer += DeltaTime;

	// Remove invalid Asteroids pointers from the ActiveAsteroids vector
	for (size_t i = this->m_ActiveAsteroids.size(); i-- > 0; )
	{
		if (this->m_ActiveAsteroids[i].expired())
		{
			this->m_ActiveAsteroids.erase(this->m_ActiveAsteroids.begin() + i);
		}
	}

	// Spawn Asteroid
	if (this->m_Timer >= this->m_SpawningCooldown)
	{
		this->SpawnAsteroids(1);

		this->m_Timer = 0.0f;
	}
}


void AsteroidsSpawner::SpawnMaxAsteroids()
{
	if(!this->m_Level)
	{
		std::cout << "Cannot spawn the Asteroids using the AsteroidSpawner if a pointer to the Level object is not valid." << std::endl;

		return;
	}

	sf::Vector2f tAsteroidPos(0.0f, 0.0f);
	for (this->m_ActiveAsteroids.size(); this->m_ActiveAsteroids.size() < this->m_MaxAsteroidsNum;)
	{
		this->SpawnAsteroids(1);
	}
}

void AsteroidsSpawner::SpawnAsteroids(unsigned int AsteroidsToSpawn)
{
	if (!this->m_Level)
	{
		std::cout << "Cannot spawn the Asteroids using the AsteroidSpawner if a pointer to the Level object is not valid." << std::endl;

		return;
	}

	unsigned int tAvailableAsteroidsNum = this->m_MaxAsteroidsNum - this->m_ActiveAsteroids.size();
	unsigned int tAsteroidsToSpawn = 0;
	tAvailableAsteroidsNum <= AsteroidsToSpawn ? tAsteroidsToSpawn = tAvailableAsteroidsNum : tAsteroidsToSpawn = AsteroidsToSpawn;

	sf::Vector2f tAsteroidPos(0.0f, 0.0f);
	for (unsigned int i = 0; i < tAsteroidsToSpawn; i++)
	{
		std::shared_ptr<GameObject> tAsteroid = std::make_shared<Asteroid>(this->m_AsteroidsSize, 3.0f);
		this->m_Level->AddObject(tAsteroid);
		tAsteroid->SetPosition(tAsteroidPos);
		tAsteroidPos.x += 200.0f;
		std::weak_ptr<Asteroid> tAsteroidWeakPtr = std::dynamic_pointer_cast<Asteroid>(tAsteroid);
		tAsteroidWeakPtr.lock().get()->SetCanMultiply(true, 2);
		tAsteroidWeakPtr.lock().get()->SetMaxSpeed(this->m_AsteroidsMaxSpeed);
		tAsteroidWeakPtr.lock().get()->SetLinearAcceleration(this->m_AsteroidLinearAcceleration);

		this->m_ActiveAsteroids.push_back(std::weak_ptr<Asteroid>(tAsteroidWeakPtr));
	}
}
